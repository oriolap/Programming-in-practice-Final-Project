#include "assert.h"
#include "string.h"
#include "stdlib.h"
#include "do.h"

// Initialize to NULL all pointers of a DO
void do_initEmpty(tDO* DO)
{
    // Preconditions
    assert(DO != NULL);
    
    DO->code = NULL;
    DO->name = NULL;
    
    winegrowerList_init(&(DO->winegrowers));
    vineyardplotData_init(&(DO->vineyards));
}

// Initialize a DO
tApiError do_init(tDO* DO, const char* code, const char* name, double avgCropField)
{
    // Preconditions
    assert(DO != NULL);
    assert(code != NULL);
    assert(name != NULL);
    
    DO->code = (char*)malloc(sizeof(char) * (strlen(code) + 1));
    
    if (DO->code == NULL) {
        return E_MEMORY_ERROR;
    }
    
    DO->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    
    if (DO->name == NULL) {
        return E_MEMORY_ERROR;
    }
    
    strcpy(DO->code, code);
    strcpy(DO->name, name);
    DO->avgCropField = avgCropField;
    
    winegrowerList_init(&(DO->winegrowers));
    vineyardplotData_init(&(DO->vineyards));
    
    return E_SUCCESS;
}

// Copy a DO
tApiError do_cpy(tDO* dst, tDO src)
{
    // Preconditions
    assert(dst != NULL);
    
    return do_init(dst, src.code, src.name, src.avgCropField);
}

// Release a DO
void do_free(tDO* DO)
{
    // Preconditions
    assert(DO != NULL);
    
    if (DO->code != NULL) {
        free(DO->code);
        DO->code = NULL;
    }
    
    if (DO->name != NULL) {
        free(DO->name);
        DO->name = NULL;
    }
    
    winegrowerList_free(&(DO->winegrowers));
    vineyardplotData_free(&(DO->vineyards));
}

// Initialize a DO data
void doData_init(tDOData* data)
{
    // Preconditions
    assert(data != NULL);
    
    data->elems = NULL;
    data->count = 0;
}

// Release a DO data
void doData_free(tDOData* data)
{
    int i;
    
    // Preconditions
    assert(data != NULL);
    
    if(data->elems != NULL) {
        for(i = 0; i < data->count; i++) {
            do_free(&(data->elems[i]));
        }
        
        free(data->elems);
        doData_init(data);
    }
}

// Return the number of DO in data
int doData_len(tDOData data)
{
    return data.count;
}

// Insert a DO to the DO data
tApiError doData_add(tDOData* data, tDO DO)
{
    // Preconditions
    assert(data != NULL);
    
    if (data->count == 0) {
        data->elems = (tDO*)malloc(sizeof(tDO));
    } else {
        data->elems = (tDO*)realloc(data->elems, sizeof(tDO) * (data->count + 1));
    }
    
    if (data->elems == NULL) {
        return E_MEMORY_ERROR;
    }
    
    do_cpy(&(data->elems[data->count]), DO);
    data->count++;
    
    return E_SUCCESS;
}

// Find a DO in DO data
tDO* doData_find(tDOData data, const char* code)
{
    int i;
    
    // Preconditions
    assert(code != NULL);
    
    for (i = 0; i < data.count; i++) {
        if (strcmp(data.elems[i].code, code) == 0) {
            return &(data.elems[i]);
        }
    }
    
    return NULL;
}

// Parse input from CSVEntry
void do_parse(tDO* data, tCSVEntry entry) {
    // Check input data
    assert(data != NULL);
    
    // Check entry fields
    assert(csv_numFields(entry) == NUM_FIELDS_DO);
    
    int pos = 0; // Allow to easy change position of the income data
    
    // Release the DO
    do_free(data);
    
    // Copy code data
    data->code = (char*) malloc((strlen(entry.fields[pos]) + 1) * sizeof(char));
    assert(data->code != NULL);
    memset(data->code, 0, (strlen(entry.fields[pos]) + 1) * sizeof(char));
    csv_getAsString(entry, pos, data->code, strlen(entry.fields[pos]) + 1);
    
    // Copy name data
    pos = 1;
    data->name = (char*) malloc((strlen(entry.fields[pos]) + 1) * sizeof(char));
    assert(data->name != NULL);
    memset(data->name, 0, (strlen(entry.fields[pos]) + 1) * sizeof(char));
    csv_getAsString(entry, pos, data->name, strlen(entry.fields[pos]) + 1);
    
    // Copy avgCropField data
    pos = 2;
    data->avgCropField = csv_getAsReal(entry, pos);
    
    winegrowerList_init(&(data->winegrowers));
    vineyardplotData_init(&(data->vineyards));
}

// Get the total weight from an specific winegrower
double doData_getTotalWeightByWinegrower(tDO DO, const char* winegrowerId)
{
    // PR2 EX 2a
    tWinegrower *winegrower;
    
    // Preconditions
    assert(winegrowerId != NULL);
    
    if ((winegrower = winegrowerList_find(DO.winegrowers, winegrowerId)) == NULL) {
        return 0.0;
    }
    
    return doData_getTotalWeightByWinegrower_recursive(winegrower->vineyardplots, winegrower->vineyardplots.count);
    /////////////////////////////////
    //return 0.0;
}

// Recursive version to get the total weight
double doData_getTotalWeightByWinegrower_recursive(tVineyardplotData vineyards, int index)
{
    double totalWeight;
    
    if (index == 0) {
        // Base case
        totalWeight = 0.0;
    } else {
        // Recursive case
        totalWeight = doData_getTotalWeightByWinegrower_recursive(vineyards, index-1) + vineyards.elems[index-1].weight;
    }
    
    return totalWeight;
}

// Get the total weighing for an specific winegrower, specific vineyard and specific year
double doData_getTotalWeighingByWineGrowerAndVineyardByYear(tDO DO, const char* winegrowerId, const char* vineyardplotCode, int year)
{
    // PR2 EX 2b
    tWinegrower *winegrower;
    tVineyardplot *vineyardplot;
    int idx;
    
    // Preconditions
    assert(winegrowerId != NULL);
    assert(vineyardplotCode != NULL);
    
    if ((winegrower = winegrowerList_find(DO.winegrowers, winegrowerId)) == NULL) {
        return 0.0;
    }
    
    if ((idx = vineyardplotData_find(winegrower->vineyardplots, vineyardplotCode)) == -1) {
        return 0.0;
    }
    
    vineyardplot = &(winegrower->vineyardplots.elems[idx]);
    
    return doData_getTotalWeighingByWineGrowerAndVineyardByYear_recursive(vineyardplot->weights.first, year);
    /////////////////////////////////
    //return 0.0;
}

// Recursive version to get the total weighing
double doData_getTotalWeighingByWineGrowerAndVineyardByYear_recursive(tWeighingNode *pNode, int year)
{
    double totalWeighing;
    
    if (pNode == NULL) {
        // Base case
        totalWeighing = 0.0;
    } else {
        // Recursive case
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear_recursive(pNode->next, year);
        
        // Add the weighing if the year is the same
        if (pNode->elem.harvestDay.year == year) {
            totalWeighing += pNode->elem.weight;
        }
    }
    
    return totalWeighing;
}

// Get the total weighing for a specific DO on a specific year
double do_getTotalWeighing(tDO DO, int year) {
    // PR3 EX 3a
    // Each DO can have multiple vineyards and each vineyard can have multiple weighings for a given year
    // The sum of all the weighing for a given year is returned by this method
    
    //initialise variables
    double totalWeighing;
    totalWeighing = 0.0;
    int i; 
    
    //initialise current weighing node
    tWeighingNode* currentNode;
    currentNode = NULL;
    
    //iterate for each vineyard of the DO
    for(i=0; i < DO.vineyards.count; i++){
        //set current node as the first element of the weights list of the current vineyard
        currentNode = DO.vineyards.elems[i].weights.first;
        //transverse through the weighting list and add the weight to the total if the year matches
        while(currentNode != NULL){
            if(currentNode->elem.harvestDay.year == year){
                totalWeighing += currentNode->elem.weight;
            } 
            
            currentNode = currentNode->next;
        } 
    }
    
    return totalWeighing;
}

// Sort a DO Data by the weighing on a given year
tDOData doData_orderByWeighing(tDOData* DOData, int year) {
    // PR3 EX 3b
    // The input DO Data is in the pointer to tDOData
    // A copy of the DO Data is sorted by weighing on a given year
    // The sorted DO Data is returned by this method
    tDOData newDOData;
    doData_init(&newDOData);
    
    int i;
    
    tWeighingNode* currentNode;
    currentNode = NULL;

    //loop through DOData
    for (int i = 0; i < DOData->count; i++) {
        // add DO element to the new DO Data list
        doData_add(&newDOData, DOData->elems[i]);

        //get the index for the newDOdata element
        int newDOIndex = newDOData.count - 1;

        //copy vineyards using the index saved previously
        for (int j = 0; j < DOData->elems[i].vineyards.count; j++) {
            vineyardplotData_add(&newDOData.elems[newDOIndex].vineyards, DOData->elems[i].vineyards.elems[j]);

            //get the index for the new vineyard saved
            int newVineyardIndex = newDOData.elems[newDOIndex].vineyards.count - 1;

            //copy weighings using the index saved previously
            tWeighingNode* currentWeighingNode = DOData->elems[i].vineyards.elems[j].weights.first;
            while (currentWeighingNode != NULL) {
                weighingList_add(&newDOData.elems[newDOIndex].vineyards.elems[newVineyardIndex].weights, currentWeighingNode->elem);
                currentWeighingNode = currentWeighingNode->next;
            }
        }
    }
        
    //iterate through each element of newDOData
    for (int i = 0; i < newDOData.count - 1; i++) {
        //set the index of the current element iterated as the index of the highest weight
        int maxIdx = i;
        //iterate from the second element. Save the weight of this element and the weight of the highest element
        for (int j = i + 1; j < newDOData.count; j++) {
            double weightJ = do_getTotalWeighing(newDOData.elems[j], year);
            double weightMax = do_getTotalWeighing(newDOData.elems[maxIdx], year);
            
            //compare the weight of the current weight with the weight of the highes element (and the DO code in case weights are equal)
            //if current weight is higher than the weight of the current maxIdx element, set maxIdx as the position of the current element
            if (weightJ > weightMax || 
                (weightJ == weightMax && strcmp(newDOData.elems[j].code, newDOData.elems[maxIdx].code) < 0)) {
                maxIdx = j;
            }
        }
        //in case the maxIdx is not i swap the element in i position with the element in maxIdx position
        if (maxIdx != i) {
            swap(&newDOData.elems[i], &newDOData.elems[maxIdx]);
        }
    }

    return newDOData;
} 


//aux

//function to swap the values of two tDO elements 
void swap(tDO *a, tDO *b) {
    tDO temp = *a;
    *a = *b;
    *b = temp;
}