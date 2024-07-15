#ifndef __VINEYARDPLOT_H__
#define __VINEYARDPLOT_H__
#include "csv.h"
#include "error.h"
#include "weighing.h"
#include "grapevariety.h"

#define NUM_FIELDS_VINEYARD_PLOT 5
// Length of the code of the origin designation  
#define DO_CODE_LENGTH 2
// Length of a vineyardplot code
#define MAX_VINEYARD_CODE_LENGTH 13
// Maximum number of vineyardsplot of a winegrower
#define MAX_VINEYARDPLOTS 3


typedef struct {
    char  *code;
    char  *doCode;
    float weight;
    tWeighingList weights;
    
    // PR3 EX 1a
    tGrapeVariety grapeVariety;
} tVineyardplot;

typedef struct _tVineyardplotData {    
    tVineyardplot* elems;
    int count;
} tVineyardplotData;


// Add a new vineyardplot
void vineyardplotData_add(tVineyardplotData* data, tVineyardplot vineyardplot);

// Initialize vineyardplotdata
tApiError vineyardplot_init(tVineyardplot* vineyardplot, const char* vineyardCode, const char* doCode, float weight, tGrapeVariety grapeVariety);

// Release vineyardplotdata
void vineyardplot_free(tVineyardplot* plot);

// Copy the data of a vineyardplotfrom the source to destination
void vineyardplot_cpy(tVineyardplot* destination, tVineyardplot source);

// Initialize the vineyardplot data
void vineyardplotData_init(tVineyardplotData* data);

// Remove all elements
void vineyardplotData_free(tVineyardplotData* data);

// Get the number of vineyardplot
int vineyardplotData_len(tVineyardplotData data);

// Add a new vineyardplot
void vineyardplotData_add(tVineyardplotData* data, tVineyardplot vineyardplot);

// Remove vineyardplot from a vineyardplot data
void vineyardplotData_del(tVineyardplotData* data, const char* code);

// Return the position of a vineyardplot entry with provided information. -1 if it does not exist
int vineyardplotData_find(tVineyardplotData data, const char* code);

// Parse input from CSVEntry VINEYARDPLOT  
void vineyardplot_parse(tVineyardplot* vineyardplot, tCSVEntry entry);

// Auxiliar methods
// Check if a vineyard code is valid
bool check_vineyard_code(const char* code);


#endif