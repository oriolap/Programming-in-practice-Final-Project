#ifndef __WINEGROWER_H__
#define __WINEGROWER_H__
#include "csv.h"
#include "date.h"
#include "error.h"
#include "vineyardplot.h"


// Maximum number of fields of winegrower + vineyard plot
#define NUM_FIELDS_WINEGROWER 7
// Maximum number of fields of winegrower without vineyard plot information
#define NUM_FIELDS_ONLY_WINEGROWER 3
// Maximum number of fields of winegrower
#define MAX_DOCUMENT_ID 9
// Length of winegrowers code
#define WINEGROWERS_ID_LENGTH 14


typedef struct _tWinegrower{
    char  *id;
    char  *document;
    tDate registrationDate;
    tVineyardplotData vineyardplots;
} tWinegrower;


// Node of a list of Winegrowers
typedef struct _tWinegrowerNode {    
    tWinegrower winegrower;
    struct _tWinegrowerNode *next;
} tWinegrowerNode;

// List of Winegrowers
typedef struct _tWinegrowerList {    
    tWinegrowerNode* first;
    int count;
} tWinegrowerList;

// Initialize winegrower structure
tApiError winegrower_init(tWinegrower* winegrower,const char * id, const char * document, tDate registrationDate);

// Release winegrower_ data
void winegrower_free(tWinegrower* winegrower);

// Copy the data of a tWinegrower from the source to destination
void winegrower_cpy(tWinegrower* destination, tWinegrower source);

// Get the number of vineyardplot registered on winegrower
int winegrowerVineyardplotCount(tWinegrower winegrower);

// Release tWinegrowerList data
void winegrowerList_free(tWinegrowerList* list);

// Copy the data of a tWinegrowerList from the source to destination
void winegrowerList_cpy(tWinegrowerList* destination, tWinegrowerList source);

// Parse input from CSVEntry
void winegrowerList_parse(tWinegrower* winegrower, tWinegrowerList* list, tCSVEntry entry);

// Initialize the Winegrower's list
void winegrowerList_init(tWinegrowerList* list);

// Remove all elements
void winegrowerList_free(tWinegrowerList* list);

// Get the number of Winegrowers
int winegrowerList_len(tWinegrowerList list);

// Get the total number of vineyardplots
int winegrowerList_vineyardplots_total(tWinegrowerList list);

// Find a Winegrower that contains a vineyardplot in the list of Winegrowers
tWinegrower* winegrowerList_containsVineyardplot(tWinegrowerList list, const char* code);
	
// Add a new winegrower
void winegrowerList_insert(tWinegrowerList* list, tWinegrower winegrower);

// Sort a list of winegrowers by date and id
tWinegrowerList winegrowerList_orderByDateAndId(tWinegrowerList* list);

// Remove a winegrower
void winegrowerList_del(tWinegrowerList* list, const char* id);

// Get the number of winegrowers
int winegrowerList_len(tWinegrowerList list);

// Find a winegrower
tWinegrower* winegrowerList_find(tWinegrowerList list, const char* id);

// Find winegrowers that has a vineyard with a specific variety of grape
tWinegrowerList winegrowerList_findByGrapevariety(tWinegrowerList winegrowerList, tGrapeVariety grapeVariety);
// Find winegrowers that has a weighing with a specific variety of grape for a given year
tWinegrowerList winegrowerList_findByWeighingYearAndGrapevariety(tWinegrowerList winegrowerList, int year, tGrapeVariety grapeVariety);
// Parse input from CSVEntry winegrower  
void winegrower_parse(tWinegrower* wg, tVineyardplot* vineyardplot, tCSVEntry entry);

#endif