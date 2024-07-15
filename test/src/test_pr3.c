#include "test_pr3.h"
#include "api.h"
#include "do.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Run all tests for PR3
bool run_pr3(tTestSuite *test_suite, const char *input) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR3", "Tests for PR3 exercices");

    section = testSuite_getSection(test_suite, "PR3");
    assert(section != NULL);

    ok = run_pr3_ex1(section, input);
    
    ok = run_pr3_ex2(section, input) && ok;
    
    ok = run_pr3_ex3(section, input) && ok;
    
    ok = run_pr3_ex4(section, input) && ok;

    return ok;
}

// Run all tests for Exercice 1 of PR3
bool run_pr3_ex1(tTestSection *test_section, const char *input) {
    tApiError error;
    tDate date;
    tWeighing weighing1604, weighing1604cp;
    tVineyardplot vineyardplot1, vineyardplot2;
    tWinegrower winegrower1, winegrower2, winegrower3, winegrower4, winegrower5;
    
   
    date_parse(&date, "01/01/2020");
    winegrower_init(&winegrower1, "98765432109876", "87654321K", date);
  
    date_parse(&date, "01/05/2021");
    winegrower_init(&winegrower2, "87654321098765", "98765432J", date);
  
    date_parse(&date, "01/06/2021");
    winegrower_init(&winegrower3, "76543210987654", "54927077H", date);
  
    date_parse(&date, "01/06/2023");
    winegrower_init(&winegrower4, "12345678999999", "12345678T", date);
  
    date_parse(&date, "01/06/2023");
    winegrower_init(&winegrower5, "99999987654321", "87654321A", date);
  
    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    /////////////////////////////
    /////  PR3 EX1 TEST 1  //////
    /////////////////////////////
    failed = false;
    start_test(test_section, "PR3_EX1_1", "Initialize a vineyardplot with a grape variety");
  
    // Initialize the data
    error = vineyardplot_init(&vineyardplot1, "PE-2024-00001", "PE", 650.0, BOBAL);
  
    if (error != E_SUCCESS || vineyardplot1.grapeVariety != BOBAL) {
        failed = true;
        passed = false;
        fail_all = true;
    }
  
    end_test(test_section, "PR3_EX1_1", !failed);
    
    
    /////////////////////////////
    /////  PR3 EX1 TEST 2  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_2", "Copy a vineyardplot with a grape variety");
    // Initialize the data
    vineyardplot_cpy(&vineyardplot2, vineyardplot1);
    if (fail_all) {
        failed = true;
    } else {
        if (vineyardplot2.grapeVariety != BOBAL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    
    end_test(test_section, "PR3_EX1_2", !failed);

    /////////////////////////////
    /////  PR3 EX1 TEST 3  //////
    /////////////////////////////
    fail_all = false;
    start_test(test_section, "PR3_EX1_3", "Initialize a weighing with a grape variety");
    date_parse(&date, "16/04/2024");
    weighing1604.grapeVariety = NOT_ASSIGNED;
    error = weighing_init(&weighing1604, "CCCC", 74.91, date, BOBAL);
    
    if (error != E_SUCCESS || weighing1604.grapeVariety != BOBAL) {
        failed = true;
        passed = false;
        fail_all = true;
    }
    
    end_test(test_section, "PR3_EX1_3", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 4  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX1_4", "Copy a weighing with a grape variety");
    // Initialize the data
    weighing_cpy(&weighing1604cp, weighing1604);
    if (fail_all) {
        failed = true;
    } else {
        if (weighing1604cp.grapeVariety != BOBAL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    
    end_test(test_section, "PR3_EX1_4", !failed);
    // Release the structures
    weighing_free(&weighing1604);
    weighing_free(&weighing1604cp);
    vineyardplot_free(&(vineyardplot1));
    vineyardplot_free(&(vineyardplot2));
    winegrower_free(&(winegrower1));
    winegrower_free(&(winegrower2));
    winegrower_free(&(winegrower3));
    winegrower_free(&(winegrower4));
    winegrower_free(&(winegrower5));
    
    return passed;
}

// Run all tests for Exercice 2 of PR3
bool run_pr3_ex2(tTestSection *test_section, const char *input) {
    tDate date;
    tVineyardplot vineyardplot1, vineyardplot2, vineyardplot3, vineyardplot4, vineyardplot5, vineyardplot6, vineyardplot7, vineyardplot8, vineyardplot9, vineyardplot10;
    tWinegrower winegrower1, winegrower2, winegrower3, winegrower4, winegrower5, *pWinegrower1, *pWinegrower3, *pWinegrower4, *pWinegrower5;
    
    tWinegrowerList winegrowerListNotSorted, winegrowerListSorted, winegrowerListFind;
    
    tWeighing weighing1_1, weighing1_2, weighing3_1, weighing3_2, weighing4_1, weighing5_1, weighing6_1, weighing6_2, weighing7_1, weighing8_1;
    
    date_parse(&date, "01/01/2020");
    winegrower_init(&winegrower1, "98765432109876", "87654321K", date);
  
    date_parse(&date, "01/05/2021");
    winegrower_init(&winegrower2, "87654321098765", "98765432J", date);
  
    date_parse(&date, "01/06/2021");
    winegrower_init(&winegrower3, "76543210987654", "54927077H", date);
  
    date_parse(&date, "01/06/2023");
    winegrower_init(&winegrower4, "12345678999999", "12345678T", date);
  
    date_parse(&date, "01/06/2023");
    winegrower_init(&winegrower5, "99999987654321", "87654321A", date);
    
    date_parse(&date, "01/01/2022");
    weighing_init(&weighing1_1, "AAAA", 10.00, date, BOBAL);
    date_parse(&date, "01/01/2024");
    weighing_init(&weighing1_2, "BBBB", 20.00, date, BOBAL);
    date_parse(&date, "01/01/2022");
    weighing_init(&weighing3_1, "CCCC", 35.00, date, GARNACHA);
    date_parse(&date, "01/01/2024");
    weighing_init(&weighing3_2, "DDDD", 35.50, date, TEMPRANILLO);
    date_parse(&date, "01/02/2024");
    weighing_init(&weighing4_1, "EEEE", 70.20, date, GARNACHA);
    date_parse(&date, "10/01/2024");
    weighing_init(&weighing5_1, "FFFF", 100.30, date, TEMPRANILLO);
    date_parse(&date, "10/05/2024");
    weighing_init(&weighing6_1, "GGGG", 500.50, date, BOBAL);
    date_parse(&date, "11/05/2024");
    weighing_init(&weighing6_2, "HHHH", 1000.20, date, BOBAL);
    date_parse(&date, "01/01/2023");
    weighing_init(&weighing7_1, "IIII", 3050.60, date, MONASTRELL);
    date_parse(&date, "01/01/2024");
    weighing_init(&weighing8_1, "JJJJ", 10000.10, date, BOBAL);
    
    winegrowerList_init(&winegrowerListFind);
    
    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    /////////////////////////////
    /////  PR3 EX2 TEST 1  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_1", "Sort and empty winegrowerList by Date");
    winegrowerList_init(&winegrowerListNotSorted);
    winegrowerListSorted = winegrowerList_orderByDateAndId(&winegrowerListNotSorted);
    
    if (winegrowerListSorted.count != 0 || winegrowerListSorted.first != NULL) {
        failed = true;
        passed = false;
        fail_all = true;
    }
    
    end_test(test_section, "PR3_EX2_1", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 2  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_2", "Sort a winegrowerList by Date");
    
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower1);
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower2);
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower3);
    
    if (fail_all) {
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListSorted));
        winegrowerListSorted = winegrowerList_orderByDateAndId(&winegrowerListNotSorted);
        
        if (winegrowerListSorted.count != winegrowerListNotSorted.count) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListSorted.first == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        else if (strcmp(winegrowerListSorted.first->winegrower.id, winegrower1.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        }  else if (winegrowerListSorted.first->next == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListSorted.first->next->winegrower.id, winegrower2.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListSorted.first->next->next == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListSorted.first->next->next->winegrower.id, winegrower3.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListSorted.first->next->next->next != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_2", !failed);
    
    
    /////////////////////////////
    /////  PR3 EX2 TEST 3  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_3", "Sort a winegrowerList by Date and id");
    
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower4);
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower5);
    
    
    if (fail_all) {
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListSorted));
        winegrowerListSorted = winegrowerList_orderByDateAndId(&winegrowerListNotSorted);
        
        if (winegrowerListSorted.count != winegrowerListNotSorted.count) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListSorted.first == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListSorted.first->winegrower.id, winegrower1.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        }  else if (winegrowerListSorted.first->next == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListSorted.first->next->winegrower.id, winegrower2.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListSorted.first->next->next == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListSorted.first->next->next->winegrower.id, winegrower3.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListSorted.first->next->next->next == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListSorted.first->next->next->next->winegrower.id, winegrower4.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListSorted.first->next->next->next->next == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListSorted.first->next->next->next->next->winegrower.id, winegrower5.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListSorted.first->next->next->next->next->next != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    } 
    end_test(test_section, "PR3_EX2_3", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 4  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_4", "Find winegrowers by grape variety - Empty list");
    if (fail_all) {
        failed = true;
    } else {
        winegrowerList_free(&winegrowerListNotSorted);
        winegrowerListFind = winegrowerList_findByGrapevariety(winegrowerListNotSorted, BOBAL);
        
        if (winegrowerListFind.count != 0 || winegrowerListFind.first != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    
    end_test(test_section, "PR3_EX2_4", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 5  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_5", "Find winegrowers by grape variety - GARNACHA_TINTORELLA");
    
    vineyardplot_init(&vineyardplot1, "PE-2024-00001", "PE", 650.0, BOBAL);
    vineyardplot_init(&vineyardplot2, "EM-2024-00001", "EM", 450.0, BOBAL);
    vineyardplot_init(&vineyardplot3, "PE-2024-00002", "PE", 400.0,TEMPRANILLO);
    vineyardplot_init(&vineyardplot4, "EM-2024-00002", "EM", 500.0,GARNACHA);
    vineyardplot_init(&vineyardplot5, "EM-2024-00003", "EM", 525.0,TEMPRANILLO);
    vineyardplot_init(&vineyardplot6, "EM-2024-00004", "EM", 770.0,BOBAL);
    vineyardplot_init(&vineyardplot7, "MO-2024-00001", "MO", 450.0, MONASTRELL);
    vineyardplot_init(&vineyardplot8, "MO-2024-00002", "MO", 400.0,BOBAL);
    vineyardplot_init(&vineyardplot9, "MO-2024-00003", "MO", 500.0,MONASTRELL);
    vineyardplot_init(&vineyardplot10, "MO-2024-00004", "MO", 525.0,TEMPRANILLO);
    
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower1);
    pWinegrower1 = winegrowerList_find(winegrowerListNotSorted, winegrower1.id);
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower2);
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower3);
    pWinegrower3 = winegrowerList_find(winegrowerListNotSorted, winegrower3.id);
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower4);
    pWinegrower4 = winegrowerList_find(winegrowerListNotSorted, winegrower4.id);
    winegrowerList_insert(&(winegrowerListNotSorted), winegrower5);
    pWinegrower5 = winegrowerList_find(winegrowerListNotSorted, winegrower5.id);
    
    
    vineyardplotData_add(&(pWinegrower1->vineyardplots), vineyardplot1);
    vineyardplotData_add(&(pWinegrower1->vineyardplots), vineyardplot3);
    vineyardplotData_add(&(pWinegrower3->vineyardplots), vineyardplot2);
    vineyardplotData_add(&(pWinegrower4->vineyardplots), vineyardplot4);
    vineyardplotData_add(&(pWinegrower4->vineyardplots), vineyardplot5);
    vineyardplotData_add(&(pWinegrower4->vineyardplots), vineyardplot6);
    vineyardplotData_add(&(pWinegrower5->vineyardplots), vineyardplot7);
    vineyardplotData_add(&(pWinegrower5->vineyardplots), vineyardplot8);
    vineyardplotData_add(&(pWinegrower5->vineyardplots), vineyardplot9);
    vineyardplotData_add(&(pWinegrower5->vineyardplots), vineyardplot10);
    
    if (fail_all) {
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListFind));        
        winegrowerListFind = winegrowerList_findByGrapevariety(winegrowerListNotSorted, GARNACHA_TINTORELLA);
        
        if (winegrowerListFind.count != 0 || winegrowerListFind.first != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_5", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 6  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_6", "Find winegrowers by grape variety - BOBAL");
    if (fail_all) {
        failed = true;
    } else {
        winegrowerListFind = winegrowerList_findByGrapevariety(winegrowerListNotSorted, BOBAL);
        
        if (winegrowerListFind.count != 4) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->winegrower.id,winegrower4.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->next->winegrower.id,winegrower3.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->next->next->winegrower.id,winegrower1.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->next->next->next->winegrower.id,winegrower5.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListFind.first->next->next->next->next != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_6", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 7  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_7", "Find winegrowers by grape variety - TEMPRANILLO");
    if (fail_all) {
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListFind));
        winegrowerListFind = winegrowerList_findByGrapevariety(winegrowerListNotSorted, TEMPRANILLO);
        
        if (winegrowerListFind.count != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->winegrower.id,winegrower4.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->next->winegrower.id,winegrower1.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->next->next->winegrower.id,winegrower5.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        }  else if (winegrowerListFind.first->next->next->next != NULL){
            failed = true;
            passed = false;
            fail_all = true;
        } 
    }
    end_test(test_section, "PR3_EX2_7", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 8  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_8", "Find winegrowers by grape variety - MONASTRELL");
    if (fail_all) {
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListFind));
        winegrowerListFind = winegrowerList_findByGrapevariety(winegrowerListNotSorted, MONASTRELL);
        
        if (winegrowerListFind.count != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->winegrower.id,winegrower5.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListFind.first->next != NULL){
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_8", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 9  //////
    /////////////////////////////
    
    fail_all = false;
    start_test(test_section, "PR3_EX2_9", "Find winegrowers with a weighing for a given year and grape variety - No weighing");
    
    winegrowerList_free(&(winegrowerListFind));
    winegrowerListFind = winegrowerList_findByWeighingYearAndGrapevariety(winegrowerListNotSorted, 2024, BOBAL);
    
    if (winegrowerListFind.count != 0 || winegrowerListFind.first != NULL) {
        failed = true;
        passed = false;
        fail_all = true;
    }
    
    end_test(test_section, "PR3_EX2_9", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 10 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_10", "Find winegrowers with a weighing for a given year and grape variety - GARNACHA_TINTORELLA 2024");
    
    if (fail_all) {
        failed = true;
    } else {
        weighingList_add(&(pWinegrower1->vineyardplots.elems[0].weights), weighing1_1);
        weighingList_add(&(pWinegrower1->vineyardplots.elems[0].weights), weighing1_2);
        weighingList_add(&(pWinegrower1->vineyardplots.elems[1].weights), weighing3_1);
        weighingList_add(&(pWinegrower1->vineyardplots.elems[1].weights), weighing3_2);
        weighingList_add(&(pWinegrower4->vineyardplots.elems[0].weights), weighing4_1);
        weighingList_add(&(pWinegrower4->vineyardplots.elems[1].weights), weighing5_1);
        weighingList_add(&(pWinegrower4->vineyardplots.elems[2].weights), weighing6_1);
        weighingList_add(&(pWinegrower4->vineyardplots.elems[2].weights), weighing6_2);
        weighingList_add(&(pWinegrower5->vineyardplots.elems[0].weights), weighing7_1);
        weighingList_add(&(pWinegrower5->vineyardplots.elems[1].weights), weighing8_1);
        winegrowerList_free(&(winegrowerListFind));
        winegrowerListFind = winegrowerList_findByWeighingYearAndGrapevariety(winegrowerListNotSorted, 2024, GARNACHA_TINTORELLA);
    }
    if (winegrowerListFind.count != 0 || winegrowerListFind.first != NULL) {
        failed = true;
        passed = false;
        fail_all = true;
    }
    end_test(test_section, "PR3_EX2_10", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 11 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_11", "Find winegrowers with a weighing for a given year and grape variety - BOBAL 2024");
    if (fail_all) {
        
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListFind));
        winegrowerListFind = winegrowerList_findByWeighingYearAndGrapevariety(winegrowerListNotSorted, 2024, BOBAL);
        
        if (winegrowerListFind.count != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->winegrower.id,winegrower4.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->next->winegrower.id,winegrower1.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->next->next->winegrower.id,winegrower5.id) != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListFind.first->next->next->next != NULL){
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_11", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 12 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_12", "Find winegrowers with a weighing for a given year and grape variety - BOBAL 2022");
    if (fail_all) {
        
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListFind));
        winegrowerListFind = winegrowerList_findByWeighingYearAndGrapevariety(winegrowerListNotSorted, 2022, BOBAL);
        
        if (winegrowerListFind.count != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->winegrower.id,winegrower1.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListFind.first->next != NULL){
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_12", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 13 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_13", "Find winegrowers with a weighing for a given year and grape variety - TEMPRANILLO 2024");
    if (fail_all) {
        
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListFind));
        winegrowerListFind = winegrowerList_findByWeighingYearAndGrapevariety(winegrowerListNotSorted, 2024, TEMPRANILLO);
        
        if (winegrowerListFind.count != 2) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->winegrower.id,winegrower4.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->next->winegrower.id,winegrower1.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListFind.first->next->next != NULL){
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_13", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 14 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX2_14", "Find winegrowers with a weighing for a given year and grape variety - MONASTRELL 2023");
    if (fail_all) {
        
        failed = true;
    } else {
        winegrowerList_free(&(winegrowerListFind));
        winegrowerListFind = winegrowerList_findByWeighingYearAndGrapevariety(winegrowerListNotSorted, 2023, MONASTRELL);
        
        if (winegrowerListFind.count != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrowerListFind.first->winegrower.id,winegrower5.id) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (winegrowerListFind.first->next != NULL){
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_14", !failed);
    
    // Release the structures
    weighing_free(&(weighing1_1));
    weighing_free(&(weighing1_2));
    weighing_free(&(weighing3_1));
    weighing_free(&(weighing3_2));
    weighing_free(&(weighing4_1));
    weighing_free(&(weighing5_1));
    weighing_free(&(weighing6_1));
    weighing_free(&(weighing6_2));
    weighing_free(&(weighing7_1));
    weighing_free(&(weighing8_1));
    vineyardplot_free(&(vineyardplot1));
    vineyardplot_free(&(vineyardplot2));
    vineyardplot_free(&(vineyardplot3));
    vineyardplot_free(&(vineyardplot4));
    vineyardplot_free(&(vineyardplot5));
    vineyardplot_free(&(vineyardplot6));
    vineyardplot_free(&(vineyardplot7));
    vineyardplot_free(&(vineyardplot8));
    vineyardplot_free(&(vineyardplot9));
    vineyardplot_free(&(vineyardplot10));
    winegrower_free(&(winegrower1));
    winegrower_free(&(winegrower2));
    winegrower_free(&(winegrower3));
    winegrower_free(&(winegrower4));
    winegrower_free(&(winegrower5));
    winegrowerList_free(&(winegrowerListNotSorted));
    winegrowerList_free(&(winegrowerListSorted));
    winegrowerList_free(&(winegrowerListFind));
    return passed;
}


// Run all tests for Exercice 3 of PR3
bool run_pr3_ex3(tTestSection *test_section, const char *input) {
    tDate date;
    tVineyardplot vineyardplot1, vineyardplot2, vineyardplot3, vineyardplot4, vineyardplot5, vineyardplot6, vineyardplot7, vineyardplot8, vineyardplot9, vineyardplot10;
    tWinegrower winegrower1, winegrower2, winegrower3, winegrower4, winegrower5, *pWinegrower1, *pWinegrower3, *pWinegrower4, *pWinegrower5;
    
    tWeighing weighing1_1, weighing1_2, weighing3_1, weighing3_2, weighing4_1, weighing5_1, weighing6_1, weighing6_2, weighing7_1, weighing8_1;
    
    tDO DOPenedes, DOEmporda, DOMonsant, *pDOPenedes, *pDOEmporda, *pDOMonsant;
    tDOData DOData, DODataNew;
    double totalWeighing1, totalWeighing2, totalWeighing3, totalWeighing4;
    
    date_parse(&date, "01/01/2020");
    winegrower_init(&winegrower1, "98765432109876", "87654321K", date);
  
    date_parse(&date, "01/05/2021");
    winegrower_init(&winegrower2, "87654321098765", "98765432J", date);
  
    date_parse(&date, "01/06/2021");
    winegrower_init(&winegrower3, "76543210987654", "54927077H", date);
  
    date_parse(&date, "01/06/2023");
    winegrower_init(&winegrower4, "12345678999999", "12345678T", date);
  
    date_parse(&date, "01/06/2023");
    winegrower_init(&winegrower5, "99999987654321", "87654321A", date);
    
    date_parse(&date, "01/01/2022");
    weighing_init(&weighing1_1, "AAAA", 10.00, date, BOBAL);
    date_parse(&date, "01/01/2024");
    weighing_init(&weighing1_2, "BBBB", 20.00, date, BOBAL);
    date_parse(&date, "01/01/2022");
    weighing_init(&weighing3_1, "CCCC", 35.00, date, GARNACHA);
    date_parse(&date, "01/01/2024");
    weighing_init(&weighing3_2, "DDDD", 35.50, date, TEMPRANILLO);
    date_parse(&date, "01/02/2024");
    weighing_init(&weighing4_1, "EEEE", 70.20, date, GARNACHA);
    date_parse(&date, "10/01/2024");
    weighing_init(&weighing5_1, "FFFF", 100.30, date, TEMPRANILLO);
    date_parse(&date, "10/05/2024");
    weighing_init(&weighing6_1, "GGGG", 500.50, date, BOBAL);
    date_parse(&date, "11/05/2024");
    weighing_init(&weighing6_2, "HHHH", 1000.20, date, BOBAL);
    date_parse(&date, "01/01/2023");
    weighing_init(&weighing7_1, "IIII", 3050.60, date, MONASTRELL);
    date_parse(&date, "01/01/2024");
    weighing_init(&weighing8_1, "JJJJ", 10000.10, date, BOBAL);
    
    vineyardplot_init(&vineyardplot1, "PE-2024-00001", "PE", 650.0, BOBAL);
    vineyardplot_init(&vineyardplot2, "EM-2024-00001", "EM", 450.0, BOBAL);
    vineyardplot_init(&vineyardplot3, "PE-2024-00002", "PE", 400.0,TEMPRANILLO);
    vineyardplot_init(&vineyardplot4, "EM-2024-00002", "EM", 500.0,GARNACHA);
    vineyardplot_init(&vineyardplot5, "EM-2024-00003", "EM", 525.0,TEMPRANILLO);
    vineyardplot_init(&vineyardplot6, "EM-2024-00004", "EM", 770.0,BOBAL);
    vineyardplot_init(&vineyardplot7, "MO-2024-00001", "MO", 450.0, MONASTRELL);
    vineyardplot_init(&vineyardplot8, "MO-2024-00002", "MO", 400.0,BOBAL);
    vineyardplot_init(&vineyardplot9, "MO-2024-00003", "MO", 500.0,MONASTRELL);
    vineyardplot_init(&vineyardplot10, "MO-2024-00004", "MO", 525.0,TEMPRANILLO);    
    
    do_init(&DOPenedes, "PE", "Penedes", 70.00);
    do_init(&DOEmporda, "EM", "Emporda", 65.00);
    do_init(&DOMonsant, "MO", "Monsant", 72.00);
    
    doData_init(&DODataNew);
    doData_init(&DOData);
    doData_add(&DOData, DOPenedes);
    doData_add(&DOData, DOEmporda);
    doData_add(&DOData, DOMonsant);
    pDOPenedes = doData_find(DOData, DOPenedes.code);
    pDOEmporda = doData_find(DOData, DOEmporda.code);
    pDOMonsant = doData_find(DOData, DOMonsant.code);
    
    vineyardplotData_add(&(pDOPenedes->vineyards), vineyardplot1);
    vineyardplotData_add(&(pDOPenedes->vineyards), vineyardplot3);
    vineyardplotData_add(&(pDOEmporda->vineyards), vineyardplot2);
    vineyardplotData_add(&(pDOEmporda->vineyards), vineyardplot4);
    vineyardplotData_add(&(pDOEmporda->vineyards), vineyardplot5);
    vineyardplotData_add(&(pDOEmporda->vineyards), vineyardplot6);
    vineyardplotData_add(&(pDOMonsant->vineyards), vineyardplot7);
    vineyardplotData_add(&(pDOMonsant->vineyards), vineyardplot8);
    vineyardplotData_add(&(pDOMonsant->vineyards), vineyardplot9);
    vineyardplotData_add(&(pDOMonsant->vineyards), vineyardplot10);
    
    winegrowerList_insert(&(pDOPenedes->winegrowers), winegrower1);
    pWinegrower1 = winegrowerList_find(pDOPenedes->winegrowers, winegrower1.id);
    winegrowerList_insert(&(pDOPenedes->winegrowers), winegrower2);
    winegrowerList_insert(&(pDOEmporda->winegrowers), winegrower3);
    pWinegrower3 = winegrowerList_find(pDOEmporda->winegrowers, winegrower3.id);
    winegrowerList_insert(&(pDOEmporda->winegrowers), winegrower4);
    pWinegrower4 = winegrowerList_find(pDOEmporda->winegrowers, winegrower4.id);
    winegrowerList_insert(&(pDOMonsant->winegrowers), winegrower5);
    pWinegrower5 = winegrowerList_find(pDOMonsant->winegrowers, winegrower5.id);
    
    vineyardplotData_add(&(pWinegrower1->vineyardplots), vineyardplot1);
    vineyardplotData_add(&(pWinegrower1->vineyardplots), vineyardplot3);
    vineyardplotData_add(&(pWinegrower3->vineyardplots), vineyardplot2);
    vineyardplotData_add(&(pWinegrower4->vineyardplots), vineyardplot4);
    vineyardplotData_add(&(pWinegrower4->vineyardplots), vineyardplot5);
    vineyardplotData_add(&(pWinegrower4->vineyardplots), vineyardplot6);
    vineyardplotData_add(&(pWinegrower5->vineyardplots), vineyardplot7);
    vineyardplotData_add(&(pWinegrower5->vineyardplots), vineyardplot8);
    vineyardplotData_add(&(pWinegrower5->vineyardplots), vineyardplot9);
    vineyardplotData_add(&(pWinegrower5->vineyardplots), vineyardplot10);
    
    weighingList_add(&(pWinegrower1->vineyardplots.elems[0].weights), weighing1_1);
    weighingList_add(&(pWinegrower1->vineyardplots.elems[0].weights), weighing1_2);
    weighingList_add(&(pWinegrower1->vineyardplots.elems[1].weights), weighing3_1);
    weighingList_add(&(pWinegrower1->vineyardplots.elems[1].weights), weighing3_2);
    weighingList_add(&(pWinegrower4->vineyardplots.elems[0].weights), weighing4_1);
    weighingList_add(&(pWinegrower4->vineyardplots.elems[1].weights), weighing5_1);
    weighingList_add(&(pWinegrower4->vineyardplots.elems[2].weights), weighing6_1);
    weighingList_add(&(pWinegrower4->vineyardplots.elems[2].weights), weighing6_2);
    weighingList_add(&(pWinegrower5->vineyardplots.elems[0].weights), weighing7_1);
    weighingList_add(&(pWinegrower5->vineyardplots.elems[1].weights), weighing8_1);
    
    weighingList_add(&(pDOPenedes->vineyards.elems[0].weights), weighing1_1);
    weighingList_add(&(pDOPenedes->vineyards.elems[0].weights), weighing1_2);
    weighingList_add(&(pDOPenedes->vineyards.elems[1].weights), weighing3_1);
    weighingList_add(&(pDOPenedes->vineyards.elems[1].weights), weighing3_2);
    weighingList_add(&(pDOEmporda->vineyards.elems[0].weights), weighing4_1);
    weighingList_add(&(pDOEmporda->vineyards.elems[1].weights), weighing5_1);
    weighingList_add(&(pDOEmporda->vineyards.elems[2].weights), weighing6_1);
    weighingList_add(&(pDOEmporda->vineyards.elems[2].weights), weighing6_2);
    weighingList_add(&(pDOMonsant->vineyards.elems[0].weights), weighing7_1);
    weighingList_add(&(pDOMonsant->vineyards.elems[1].weights), weighing8_1);
    
    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    /////////////////////////////
    /////  PR3 EX3 TEST 1  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_1", "Get Total Weighing");
    totalWeighing1 = do_getTotalWeighing(*pDOPenedes, 2024);
    totalWeighing2 = do_getTotalWeighing(*pDOPenedes, 2023);
    totalWeighing3 = do_getTotalWeighing(*pDOEmporda, 2024);
    totalWeighing4 = do_getTotalWeighing(*pDOMonsant, 2024);
    
    if (fabs(totalWeighing1 - 55.5) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (fabs(totalWeighing2 - 0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (fabs(totalWeighing3 - 1671.2) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    }  else if (fabs(totalWeighing4 - 10000.10) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    }
    end_test(test_section, "PR3_EX3_1", !failed);

    /////////////////////////////
    /////  PR3 EX3 TEST 2  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_2", "Order by Weighing - 2024");
    if (fail_all) {
        failed = true;
    } else {
        doData_free(&(DODataNew));
        DODataNew = doData_orderByWeighing(&DOData,2024);
        
        if (DODataNew.count != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[0].code, DOMonsant.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[1].code, DOEmporda.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[2].code, DOPenedes.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_2", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 3  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_3", "Order by Weighing - 2023");
    if (fail_all) {
        failed = true;
    } else {
        doData_free(&(DODataNew));
        DODataNew = doData_orderByWeighing(&DOData,2023);
        
        if (DODataNew.count != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[0].code, DOMonsant.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[1].code, DOEmporda.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[2].code, DOPenedes.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_3", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 4  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_4", "Order by Weighing - 2022");
    if (fail_all) {
        failed = true;
    } else {
        doData_free(&(DODataNew));
        DODataNew = doData_orderByWeighing(&DOData,2022);
        
        if (DODataNew.count != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[0].code, DOPenedes.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[1].code, DOEmporda.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[2].code, DOMonsant.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_4", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 5  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_5", "Order by Weighing - 1990");
    if (fail_all) {
        failed = true;
    } else {
        doData_free(&(DODataNew));
        DODataNew = doData_orderByWeighing(&DOData,1990);
        
        if (DODataNew.count != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[0].code, DOEmporda.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[1].code, DOMonsant.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(DODataNew.elems[2].code, DOPenedes.code) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_5", !failed);
    
    
    // Release the structures
    weighing_free(&(weighing1_1));
    weighing_free(&(weighing1_2));
    weighing_free(&(weighing3_1));
    weighing_free(&(weighing3_2));
    weighing_free(&(weighing4_1));
    weighing_free(&(weighing5_1));
    weighing_free(&(weighing6_1));
    weighing_free(&(weighing6_2));
    weighing_free(&(weighing7_1));
    weighing_free(&(weighing8_1));
    vineyardplot_free(&(vineyardplot1));
    vineyardplot_free(&(vineyardplot2));
    vineyardplot_free(&(vineyardplot3));
    vineyardplot_free(&(vineyardplot4));
    vineyardplot_free(&(vineyardplot5));
    vineyardplot_free(&(vineyardplot6));
    vineyardplot_free(&(vineyardplot7));
    vineyardplot_free(&(vineyardplot8));
    vineyardplot_free(&(vineyardplot9));
    vineyardplot_free(&(vineyardplot10));
    winegrower_free(&(winegrower1));
    winegrower_free(&(winegrower2));
    winegrower_free(&(winegrower3));
    winegrower_free(&(winegrower4));
    winegrower_free(&(winegrower5));
    do_free(&(DOPenedes));
    do_free(&(DOEmporda));
    do_free(&(DOMonsant));
    doData_free(&(DOData));
    doData_free(&(DODataNew));
    return passed;
}

// Run all tests for Exercice 4 of PR3
bool run_pr3_ex4(tTestSection *test_section, const char *input) {
    tApiData data;
    tApiError error;
    tCSVEntry entry;
    tWeighing weighing1_1, weighing1_2, weighing3_1, weighing3_2, weighing4_1, weighing5_1, weighing6_1, weighing6_2, weighing7_1, weighing8_1;
    tVineyardplot vineyardplot1, vineyardplot2, vineyardplot3, vineyardplot4, vineyardplot5, vineyardplot6, vineyardplot7, vineyardplot8, vineyardplot9,vineyardplot1_1, vineyardplot2_1, vineyardplot3_1, vineyardplot4_1, vineyardplot5_1;
    
    tWinegrower winegrower1, winegrower2, winegrower3, winegrower4, winegrower5;
    
    api_initData(&data);
    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    /////////////////////////////
    /////  PR3 EX4 TEST 1  //////
    /////////////////////////////
    failed = false;
    start_test(test_section, "PR3_EX4_1", "Initialize weighings by CSV");
    
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01/01/2022;AAAA;10.00;3;PE-2024-00001", "WEIGHING");
    weighing1_1.code = NULL;
    weighing_parse(&weighing1_1,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/01/2024;BBBB;20.00;3;PE-2024-00001", "WEIGHING");
    weighing_parse(&weighing1_2,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/01/2022;CCCC;35.00;2;PE-2024-00002", "WEIGHING");
    weighing_parse(&weighing3_1,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/01/2024;DDDD;35.50;1;PE-2024-00002", "WEIGHING");
    weighing_parse(&weighing3_2,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/02/2024;EEEE;70.20;2;EM-2024-00002", "WEIGHING");
    weighing_parse(&weighing4_1,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "10/01/2024;FFFF;100.30;1;EM-2024-00003", "WEIGHING");
    weighing_parse(&weighing5_1,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "10/05/2024;GGGG;500.50;3;EM-2024-00004", "WEIGHING");
    weighing_parse(&weighing6_1,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "11/05/2024;HHHH;1000.20;3;EM-2024-00004", "WEIGHING");
    weighing_parse(&weighing6_2,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/01/2023;IIII;3050.60;5;MO-2024-00001", "WEIGHING");
    weighing_parse(&weighing7_1,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/01/2024;JJJJ;10000.10;3;MO-2024-00002", "WEIGHING");
    weighing_parse(&weighing8_1,entry);
      
    if (weighing1_1.code == NULL)  {
        failed = true;
        passed = false;
    } else if (strcmp(weighing1_1.code,"AAAA") != 0 || weighing1_1.grapeVariety != BOBAL || weighing1_1.harvestDay.year != 2022 || weighing1_1.harvestDay.day != 1 || weighing1_1.harvestDay.month != 1 || fabs(weighing1_1.weight - 10.00) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing1_2.code,"BBBB") != 0 || weighing1_2.grapeVariety != BOBAL || weighing1_2.harvestDay.year != 2024 || weighing1_2.harvestDay.day != 1 || weighing1_2.harvestDay.month != 1 || fabs(weighing1_2.weight - 20.00) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing3_1.code,"CCCC") != 0 || weighing3_1.grapeVariety != GARNACHA || weighing3_1.harvestDay.year != 2022 || weighing3_1.harvestDay.day != 1 || weighing3_1.harvestDay.month != 1 || fabs(weighing3_1.weight - 35.00) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing3_2.code,"DDDD") != 0 || weighing3_2.grapeVariety != TEMPRANILLO || weighing3_2.harvestDay.year != 2024 || weighing3_2.harvestDay.day != 1 || weighing3_2.harvestDay.month != 1 || fabs(weighing3_2.weight - 35.50) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing4_1.code,"EEEE") != 0 || weighing4_1.grapeVariety != GARNACHA || weighing4_1.harvestDay.year != 2024 || weighing4_1.harvestDay.day != 1 || weighing4_1.harvestDay.month != 2 || fabs(weighing4_1.weight - 70.20) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing5_1.code,"FFFF") != 0 || weighing5_1.grapeVariety != TEMPRANILLO || weighing5_1.harvestDay.year != 2024 || weighing5_1.harvestDay.day != 10 || weighing5_1.harvestDay.month != 1 || fabs(weighing5_1.weight - 100.30) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing6_1.code,"GGGG") != 0 || weighing6_1.grapeVariety != BOBAL || weighing6_1.harvestDay.year != 2024 || weighing6_1.harvestDay.day != 10 || weighing6_1.harvestDay.month != 5 || fabs(weighing6_1.weight - 500.50) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing6_2.code,"HHHH") != 0 || weighing6_2.grapeVariety != BOBAL || weighing6_2.harvestDay.year != 2024 || weighing6_2.harvestDay.day != 11 || weighing6_2.harvestDay.month != 5 || fabs(weighing6_2.weight - 1000.20) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing7_1.code,"IIII") != 0 || weighing7_1.grapeVariety != MONASTRELL || weighing7_1.harvestDay.year != 2023 || weighing7_1.harvestDay.day != 1 || weighing7_1.harvestDay.month != 1 || fabs(weighing7_1.weight - 3050.60) > 0.01) {
        failed = true;
        passed = false;
    } else if (strcmp(weighing8_1.code,"JJJJ") != 0 || weighing8_1.grapeVariety != BOBAL || weighing8_1.harvestDay.year != 2024 || weighing8_1.harvestDay.day != 1 || weighing8_1.harvestDay.month != 1 || fabs(weighing8_1.weight - 10000.10) > 0.01) {
        failed = true;
        passed = false;
    }
  
    end_test(test_section, "PR3_EX4_1", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 2  //////
    /////////////////////////////
    failed = false;
    start_test(test_section, "PR3_EX4_2", "Initialize vineyards by CSV");
    
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "98765432109876;PE-2024-00001;PE;650.00;3", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot1,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "76543210987654;EM-2024-00001;EM;450.00;3", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot2,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "98765432109876;PE-2024-00002;PE;400.00;1", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot3,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "12345678999999;EM-2024-00002;EM;500.00;2", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot4,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "12345678999999;EM-2024-00003;EM;525.0;1", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot5,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "12345678999999;EM-2024-00004;EM;770.0;3", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot6,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "99999987654321;MO-2024-00001;MO;450.00;5", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot7,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "99999987654321;MO-2024-00002;MO;400.00;3", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot8,entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "99999987654321;MO-2024-00003;MO;500.00;5", "VINEYARD_PLOT");
    vineyardplot_parse(&vineyardplot9,entry);
    
    if (strcmp(vineyardplot1.code,"PE-2024-00001") != 0 || strcmp(vineyardplot1.doCode,"PE") != 0  || vineyardplot1.grapeVariety != BOBAL || fabs(vineyardplot1.weight - 650.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (strcmp(vineyardplot2.code,"EM-2024-00001") != 0 || strcmp(vineyardplot2.doCode,"EM") != 0  || vineyardplot2.grapeVariety != BOBAL || fabs(vineyardplot2.weight - 450.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (strcmp(vineyardplot3.code,"PE-2024-00002") != 0 || strcmp(vineyardplot3.doCode,"PE") != 0  || vineyardplot3.grapeVariety != TEMPRANILLO || fabs(vineyardplot3.weight - 400.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (strcmp(vineyardplot4.code,"EM-2024-00002") != 0 || strcmp(vineyardplot4.doCode,"EM") != 0  || vineyardplot4.grapeVariety != GARNACHA || fabs(vineyardplot4.weight - 500.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (strcmp(vineyardplot5.code,"EM-2024-00003") != 0 || strcmp(vineyardplot5.doCode,"EM") != 0  || vineyardplot5.grapeVariety != TEMPRANILLO || fabs(vineyardplot5.weight - 525.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (strcmp(vineyardplot6.code,"EM-2024-00004") != 0 || strcmp(vineyardplot6.doCode,"EM") != 0  || vineyardplot6.grapeVariety != BOBAL || fabs(vineyardplot6.weight - 770.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (strcmp(vineyardplot7.code,"MO-2024-00001") != 0 || strcmp(vineyardplot7.doCode,"MO") != 0  || vineyardplot7.grapeVariety != MONASTRELL || fabs(vineyardplot7.weight - 450.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (strcmp(vineyardplot8.code,"MO-2024-00002") != 0 || strcmp(vineyardplot8.doCode,"MO") != 0  || vineyardplot8.grapeVariety != BOBAL || fabs(vineyardplot8.weight - 400.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    } else if (strcmp(vineyardplot9.code,"MO-2024-00003") != 0 || strcmp(vineyardplot9.doCode,"MO") != 0  || vineyardplot9.grapeVariety != MONASTRELL || fabs(vineyardplot9.weight - 500.0) > 0.01) {
        failed = true;
        passed = false;
        fail_all = true;
    }
  
    
    end_test(test_section, "PR3_EX4_2", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 3  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX4_3", "Initialize winegrowers by CSV");
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/01/2020;87654321K;98765432109876", "WINEGROWER");
    winegrower_parse(&winegrower1, &vineyardplot1_1, entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/05/2021;98765432J;87654321098765", "WINEGROWER");
    winegrower_parse(&winegrower2, &vineyardplot2_1, entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/06/2021;54927077H;76543210987654", "WINEGROWER");
    winegrower_parse(&winegrower3, &vineyardplot3_1, entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/06/2023;12345678T;12345678999999", "WINEGROWER");
    winegrower_parse(&winegrower4, &vineyardplot4_1, entry);
    csv_freeEntry(&entry);
    csv_parseEntry(&entry, "01/06/2023;87654321A;99999987654321;MO-2024-00004;MO;525.00;1", "WINEGROWER");
    winegrower_parse(&winegrower5, &vineyardplot5_1, entry);
    csv_freeEntry(&entry);
    if (fail_all) {
        failed = true;
    } else {       
        if (strcmp(winegrower1.id,"98765432109876") != 0){
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(winegrower2.id,"87654321098765") != 0){
            failed = true;
            passed = false;
            fail_all = true;
        }  else if (strcmp(winegrower3.id,"76543210987654") != 0){
            failed = true;
            passed = false;
            fail_all = true;
        }  else if (strcmp(winegrower4.id,"12345678999999") != 0 ){
            failed = true;
            passed = false;
            fail_all = true;
        }  else if (strcmp(winegrower5.id,"99999987654321") != 0 ||  vineyardplot5_1.grapeVariety != TEMPRANILLO){
            failed = true;
            passed = false;
            fail_all = true;
        } 
    }
    end_test(test_section, "PR3_EX4_3", !failed);
    
    
    /////////////////////////////
    /////  PR3 EX4 TEST 4  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX4_4", "Load weighings to API data");
    if (fail_all) {
        failed = true;
    } else {
        
        //At this stage is normal that the method returns an error (E_INVALID_ENTRY_TYPE) because we have not added yet the type WEIGHING to the method api_addDataEntry
        error = api_loadData(&data, input, true);
        
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "01/01/2022;AAAA;10.00;3;PE-2024-00001", "WEIGHING");
        api_addWeighing(&data,entry);
        csv_freeEntry(&entry);
        csv_parseEntry(&entry, "01/01/2024;BBBB;20.00;3;PE-2024-00001", "WEIGHING");
        api_addWeighing(&data,entry);
        csv_freeEntry(&entry);
        csv_parseEntry(&entry, "01/01/2022;CCCC;35.00;2;PE-2024-00002", "WEIGHING");
        api_addWeighing(&data,entry);
        
        if (data.winegrowers.first->next->next->winegrower.vineyardplots.elems[0].weights.first == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.winegrowers.first->next->next->winegrower.vineyardplots.elems[0].weights.first->elem.code,"AAAA") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }   else if (strcmp(data.winegrowers.first->next->next->winegrower.vineyardplots.elems[0].weights.first->next->elem.code,"BBBB") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }   else if (strcmp(data.winegrowers.first->next->next->winegrower.vineyardplots.elems[1].weights.first->elem.code,"CCCC") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } 
    }
    
    end_test(test_section, "PR3_EX4_4", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 5  //////
    /////////////////////////////
    failed = false;
    start_test(test_section, "PR3_EX4_5", "Load API data with weighings");
    if (fail_all) {
        failed = true;
    } else {
        api_freeData(&data);
        error = api_loadData(&data, input, true);
        
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.winegrowers.first->winegrower.vineyardplots.elems[0].weights.first->elem.code,"EEEE") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.winegrowers.first->winegrower.vineyardplots.elems[0].weights.first->next != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.winegrowers.first->winegrower.vineyardplots.elems[1].weights.first->elem.code,"FFFF") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.winegrowers.first->winegrower.vineyardplots.elems[2].weights.first->elem.code,"GGGG") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.winegrowers.first->winegrower.vineyardplots.elems[2].weights.first->next->elem.code,"HHHH") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.winegrowers.first->next->winegrower.vineyardplots.elems[0].weights.first != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.winegrowers.first->next->next->winegrower.vineyardplots.elems[0].weights.first->elem.code, "AAAA")) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    
    end_test(test_section, "PR3_EX4_5", !failed);
    
    // Release the structures
    csv_freeEntry(&entry);
    weighing_free(&(weighing1_1));
    weighing_free(&(weighing1_2));
    weighing_free(&(weighing3_1));
    weighing_free(&(weighing3_2));
    weighing_free(&(weighing4_1));
    weighing_free(&(weighing5_1));
    weighing_free(&(weighing6_1));
    weighing_free(&(weighing6_2));
    weighing_free(&(weighing7_1));
    weighing_free(&(weighing8_1));
    vineyardplot_free(&(vineyardplot1));
    vineyardplot_free(&(vineyardplot2));
    vineyardplot_free(&(vineyardplot3));
    vineyardplot_free(&(vineyardplot4));
    vineyardplot_free(&(vineyardplot5));
    vineyardplot_free(&(vineyardplot6));
    vineyardplot_free(&(vineyardplot7));
    vineyardplot_free(&(vineyardplot8));
    vineyardplot_free(&(vineyardplot9));
    vineyardplot_free(&(vineyardplot1_1));
    vineyardplot_free(&(vineyardplot2_1));
    vineyardplot_free(&(vineyardplot3_1));
    vineyardplot_free(&(vineyardplot4_1));
    vineyardplot_free(&(vineyardplot5_1));
    winegrower_free(&(winegrower1));
    winegrower_free(&(winegrower2));
    winegrower_free(&(winegrower3));
    winegrower_free(&(winegrower4));
    winegrower_free(&(winegrower5));
    api_freeData(&data);
    
    return passed;
}