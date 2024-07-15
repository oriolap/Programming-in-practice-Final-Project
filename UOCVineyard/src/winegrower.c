#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "error.h"
#include <ctype.h>
#include <stdbool.h>
#include "winegrower.h"
#include "vineyardplot.h"

// Initialize the winegrowers data
tApiError winegrower_init(tWinegrower* winegrower,const char * id, const char * document, tDate registrationDate) {
    
     // Verify pre conditions
    assert(id != NULL);
    assert(document != NULL);
    
    // Allocate the memory for the string fields, using the length of the provided text plus 1 space
    //for the "end of string" char '\0'. To allocate memory we use the malloc command.
    winegrower->id = (char*)malloc((strlen(id) + 1) * sizeof(char));

    winegrower->document = (char*)malloc((strlen(document) + 1) * sizeof(char));

    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if (winegrower->id == NULL || winegrower->document == NULL) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        return E_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data.
    
     // Set the data
    strcpy(winegrower->id, id);
    strcpy(winegrower->document, document);
    winegrower->registrationDate.day = registrationDate.day;
    winegrower->registrationDate.month = registrationDate.month;
    winegrower->registrationDate.year = registrationDate.year;
    
    vineyardplotData_init(&winegrower->vineyardplots);
 

    return E_SUCCESS;

}

// Copy the data of a tWinegrower from the source to destination
void winegrower_cpy(tWinegrower* destination, tWinegrower source){
     assert(destination != NULL);
    
    // Set the data
    winegrower_init(destination, source.id, source.document, source.registrationDate);
}


  // Release winegrower data
void winegrower_free(tWinegrower* winegrower) {
    assert(winegrower != NULL);
    
    // Release used memory
    if (winegrower->id != NULL) {
        free(winegrower->id);
        winegrower->id = NULL;
    }
    
    if (winegrower->document != NULL) {
        free(winegrower->document);
        winegrower->document = NULL;
    }
        
    
}


// Parse input from CSVEntry WINEGROWER  
void winegrower_parse(tWinegrower* wg, tVineyardplot* vineyardplot, tCSVEntry entry) {
    char stringDate[DATE_LENGTH + 1];    
    tDate date;
    char document[MAX_DOCUMENT_ID + 1];
    char id[WINEGROWERS_ID_LENGTH + 1];
    char vineyardCode[MAX_VINEYARD_CODE_LENGTH + 1];
    char doCode[DO_CODE_LENGTH + 1];
    float weight;
    tGrapeVariety grapeVariety;
    
    // Check input data
    assert(wg != NULL);
    assert(vineyardplot != NULL);
    assert(csv_numFields(entry) != NUM_FIELDS_WINEGROWER || csv_numFields(entry) != NUM_FIELDS_ONLY_WINEGROWER);

    // Get Winegrower data
    csv_getAsString(entry, 0, stringDate, DATE_LENGTH + 1);    
    
    csv_getAsString(entry, 1, document, MAX_DOCUMENT_ID + 1);        
    csv_getAsString(entry, 2, id, WINEGROWERS_ID_LENGTH + 1);        
    
    date_parse(&(date), stringDate);  
             
    winegrower_init(wg, id, document, date);
       

    if (csv_numFields(entry) == NUM_FIELDS_WINEGROWER) {
        // Get vineyardplot data
        csv_getAsString(entry, 3, vineyardCode, MAX_VINEYARD_CODE_LENGTH + 1);   
        csv_getAsString(entry, 4, doCode, DO_CODE_LENGTH + 1);    
        weight = csv_getAsReal(entry, 5);
        
        // PR3 EX 4c
        // Get the variety of the grape
        grapeVariety = csv_getAsInteger(entry, 6);

        // Initialize the vineyardplot structure
        vineyardplot_init(vineyardplot, vineyardCode, doCode, weight, grapeVariety);
    } else {

        // Initialize empty vineyardplot structure
        vineyardplot_init(vineyardplot, "", "", 0, 0);
    }
}

// Initialize the vaccine's list
void winegrowerList_init(tWinegrowerList* list) {
    assert(list != NULL);
    
    list->first = NULL;
    list->count = 0;
}

// Find a Winegrower that contains a vineyardplot in the list of Winegrowers
tWinegrower* winegrowerList_containsVineyardplot(tWinegrowerList list, const char* code){
   tWinegrower* pWinegrower = NULL;
   tWinegrowerNode *pNode = NULL;
        
    // Point the first element
    pNode = list.first;
    
    while(pWinegrower == NULL && pNode != NULL) {
       
        if(pNode->winegrower.vineyardplots.elems != NULL) {
    
            for(int i=0; i < pNode->winegrower.vineyardplots.count; i++) {
                // Compare current with given code
                if(strcmp(pNode->winegrower.vineyardplots.elems[i].code, code) == 0) {
                    pWinegrower = &pNode->winegrower;
                }
            }
        }        
            
        pNode = pNode->next;
    }
   
    return pWinegrower;    
    
    
}

void winegrowerList_insert(tWinegrowerList* list, tWinegrower winegrower){
    
    tWinegrowerNode *pNode = NULL;
    tWinegrowerNode *pPrev = NULL;
    
    assert(list != NULL);
    
    // If the list is empty add the node as first position
    if (list->count == 0) {
        list->first = (tWinegrowerNode*) malloc(sizeof(tWinegrowerNode));
        list->first->next = NULL;
        winegrower_cpy(&(list->first->winegrower), winegrower);
    } else {    
        // Point the first element
        pNode = list->first;
        pPrev = pNode;
                
        // Advance in the list up to the insertion point or the end of the list
        while(pNode != NULL && strcmp(pNode->winegrower.id, winegrower.id) < 0) {            
            pPrev = pNode;
            pNode = pNode->next;
        }
                
        if (pNode == pPrev) {
            // Insert as first element
            list->first = (tWinegrowerNode*) malloc(sizeof(tWinegrowerNode));
            list->first->next = pNode;
            winegrower_cpy(&(list->first->winegrower), winegrower);            
        } else {
            // Insert after pPrev
            pPrev->next = (tWinegrowerNode*) malloc(sizeof(tWinegrowerNode));        
            winegrower_cpy(&(pPrev->next->winegrower), winegrower);
            pPrev->next->next = pNode;            
        }
    }
    list->count ++;
    
}

tWinegrowerList winegrowerList_orderByDateAndId(tWinegrowerList* list){
    // PR3 EX 2a
    // Sort a list of winegrowers by date and id
    // The input list is in the pointer to list
    // The input list is not modified
    // A copy of the list is sorted by registrationDate and id
    // The sorted list is returned by this method
    
    tWinegrowerList listSorted;
    winegrowerList_init(&listSorted);

    //intialise current node
    tWinegrowerNode* currentNode;
    currentNode = list->first;

    //transverse through the list
    while (currentNode != NULL) {
        //create winegrower node to insert in the sorted list and allocate memory for it

        tWinegrowerNode* winegrowerNode = (tWinegrowerNode*)malloc(sizeof(tWinegrowerNode));
        
        //copy current winegrower to the new winegrower node created
        winegrower_cpy(&(winegrowerNode->winegrower), currentNode->winegrower);
        winegrowerNode->next = NULL;

        //insert new node to the beggining if list is empty or it's the first node by date and id
        if (listSorted.first == NULL || date_cmp(winegrowerNode->winegrower.registrationDate, listSorted.first->winegrower.registrationDate) < 0 ||
            (date_cmp(winegrowerNode->winegrower.registrationDate, listSorted.first->winegrower.registrationDate) == 0 && 
             strcmp(winegrowerNode->winegrower.id, listSorted.first->winegrower.id) < 0)) {
            //insert new node
            winegrowerNode->next = listSorted.first;
            listSorted.first = winegrowerNode;
            
    
        } else {
            //insert the node in a position that is not the first
            //create 2 auxiliary winegrower node (the first and second elements of the sorted list)
            tWinegrowerNode* prev = listSorted.first;
            tWinegrowerNode* curr = listSorted.first->next;
            
            //iterate through sorted list starting from the 2nd element of the sorted list. Compare it to the winegrower node to add. 
            while (curr != NULL &&
                   (date_cmp(winegrowerNode->winegrower.registrationDate, curr->winegrower.registrationDate) > 0 ||
                   (date_cmp(winegrowerNode->winegrower.registrationDate, curr->winegrower.registrationDate) == 0 &&
                    strcmp(winegrowerNode->winegrower.id, curr->winegrower.id) > 0))) {
                //update prev and curr to the next element of the list in case the winegrower node to insert has a newest day than the curr node
                prev = curr;
                curr = curr->next;
                
    
            }
            //when a winegrower node in the sorted list is found that has a newest date than the node to insert, insert the winegrower node. 
            //the current element is set as the next element of the winegrower node inserted, and the winegrower node inserted is set as the
            //next element of the prev node. 
            winegrowerNode->next = curr;
            prev->next = winegrowerNode;
        }
        listSorted.count ++;
        //update current node of the unsorted list
        currentNode = currentNode->next;
    }

    return listSorted;

}   
// Find a winegrower
tWinegrower* winegrowerList_find(tWinegrowerList list, const char* id)
{
    tWinegrowerNode *pNode = NULL;
    
    assert(id != NULL);
    
    pNode = list.first;
    
    while (pNode != NULL) {
        if (strcmp(pNode->winegrower.id, id) == 0) {
            return &(pNode->winegrower);
        }
        
        pNode = pNode->next;
    }
    
    return NULL;
}

// Find winegrowers that has a vineyard with a specific variety of grape
tWinegrowerList winegrowerList_findByGrapevariety(tWinegrowerList winegrowerList, tGrapeVariety grapeVariety) {
    // PR3 EX 2b
    // Input a list of winegrowers ordered by document id
    // Input a variety of grape
    // Output a new list of winegrowers orderd by document id that has a vineyardplot with the given variety of grape
    
    //initialise new list
    tWinegrowerList newList;
    winegrowerList_init(&newList);
    
    //initialise current node to transverse the list
    tWinegrowerNode* currentNode;
    currentNode = winegrowerList.first;
    
    //declare variable i
    int i;
    
    //transverse through winegrowerList
    while(currentNode!=NULL){
        //iterate through every vineyardplot element for every winegrower
        for (i=0; i < currentNode->winegrower.vineyardplots.count; i++){
            //if the the grape variety of a vineyard is the same as the passed as an argument add to winegrower to the new list. Break to stop for loop, the winegrower will be added
            //if there's at least one match. 
            if (currentNode->winegrower.vineyardplots.elems[i].grapeVariety == grapeVariety){
                winegrowerList_insert(&newList, currentNode->winegrower);
                break;
            }
        }
        //update current node
        currentNode = currentNode->next;
    }
    
    
    return newList;
}

tWinegrowerList winegrowerList_findByWeighingYearAndGrapevariety(tWinegrowerList winegrowerList, int year, tGrapeVariety grapeVariety) {
    // PR3 EX 2c
    // Input a list of winegrowers ordered by document id
    // Input year of the weighing
    // Input a variety of grape
    // Output a new list of winegrowers orderd by document id that has a vineyardplot that had weighing on the given year and variety of grape
    tWinegrowerList newList;
    
    // Initialize to an empty list
    winegrowerList_init(&newList);
    
    //initialise current node
    tWinegrowerNode* currentNode;
    currentNode = winegrowerList.first;
    
    //initialise current weighing node
    tWeighingNode* currentWeighingNode;
    currentWeighingNode = NULL; 
    
    //define variable i
    int i;
    
    //transverse through list
    while(currentNode!=NULL){
        //iterate through vineyarplots of a winegrower
        for (i=0; i < currentNode->winegrower.vineyardplots.count; i++){

            //define current weighing node for a weighing list
            currentWeighingNode = currentNode->winegrower.vineyardplots.elems[i].weights.first;
            
            //transverse trough the weighing list
            while(currentWeighingNode != NULL){
                if (currentWeighingNode->elem.grapeVariety == grapeVariety && currentWeighingNode->elem.harvestDay.year == year){
                    winegrowerList_insert(&newList, currentNode->winegrower);
                    break;
                }
             //update weghing list node
             currentWeighingNode = currentWeighingNode->next;
            }
            
        }
        //update node
        currentNode = currentNode->next;
    }
    
    
    return newList;
}
// Remove all elements
void winegrowerList_free(tWinegrowerList* list) {
    tWinegrowerNode *pNode = NULL;
    tWinegrowerNode *pAux = NULL;
    
    assert(list != NULL);
    
    pNode = list->first;
    while(pNode != NULL) {
        // Store the position of the current node
        pAux = pNode;
        
        vineyardplotData_free(&pNode->winegrower.vineyardplots);
        // Move to the next node in the list
        pNode = pNode->next;        
        // Remove previous node
        winegrower_free(&(pAux->winegrower));
        free(pAux);
    }
    
    // Initialize to an empty list
    winegrowerList_init(list);
}

// Get the number of winegrowers
int winegrowerList_len(tWinegrowerList list) {
    return list.count;
}

// Get the total number of vineyardplots
int winegrowerList_vineyardplots_total(tWinegrowerList list) {
    int count = 0;
    tWinegrowerNode *pNode = NULL;    
    
    pNode = list.first;
    while(pNode != NULL) {
        // Store the position of the current node
        count = count + pNode->winegrower.vineyardplots.count;
        // Move to the next node in the list
        pNode = pNode->next;            
    }
    
    return count;
}

// Get the number of vineyardplot registered on winegrower
int winegrowerVineyardplotCount(tWinegrower winegrower){
    //////////////////////////////////
    // Ex PR1 2d
    /////////////////////////////////
    return winegrower.vineyardplots.count;   
    /////////////////////////////////
    //return -1;
}
