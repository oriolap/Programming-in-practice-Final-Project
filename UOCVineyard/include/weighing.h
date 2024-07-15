#ifndef __WEIGHING_H__
#define __WEIGHING_H__

#include <stdbool.h>
#include "date.h"
#include "grapevariety.h"
#include "error.h"
#include "csv.h"

#define NUM_FIELDS_WEIGHING 5
// Length of winegrowers code
#define WEIGHING_CODE_LENGTH 4

typedef struct _tWeighing {
    char *code;
    float weight;
    tDate harvestDay;
    // PR3 EX 1c
    tGrapeVariety grapeVariety;
} tWeighing;

typedef struct _tWeighingNode {
    tWeighing elem;
    struct _tWeighingNode* prev;
    struct _tWeighingNode* next;
} tWeighingNode;

typedef struct _tWeighingList {
    tWeighingNode* first;
    tWeighingNode* last;
} tWeighingList;

// Initialize a weighing
tApiError weighing_init(tWeighing* weighing, const char* code, float weight, tDate harvestDay, tGrapeVariety grapeVariety);

// Copy a weighing from src to dst
tApiError weighing_cpy(tWeighing* dst, tWeighing src);

// Release a weighing
void weighing_free(tWeighing* weighing);

// Initialize a weighing list
tApiError weighingList_init(tWeighingList* list);

// Check if a weighing list is empty
bool weighingList_empty(tWeighingList list);

// Insert new weighing data
tApiError weighingList_add(tWeighingList* list, tWeighing weighing);

// Return the weight until the day received as a parameter according to a code
double weighingList_getWeight(tWeighingList list, const char* code, tDate day);

// Release the list
void weighingList_free(tWeighingList* list);

// Parse input from CSVEntry WEIGHING  
void weighing_parse(tWeighing* weighing, tCSVEntry entry);

// AUX

// Create a new node for weighing list
tWeighingNode* weighingList_createNode(tWeighing weighing);

// Find a node by harvest date and code
tWeighingNode* weighingList_findNode(tWeighingList list, const char* code, tDate harvestDay);

// Find the previous node to insert a new node by its harvest day and its code
tWeighingNode* weighingList_findPrev(tWeighingList list, const char* code, tDate harvestDay);

#endif /*__WEIGHING_H__*/
