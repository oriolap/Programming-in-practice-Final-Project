#include "test_pr2.h"
#include "api.h"
#include "do.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Run all tests for PR2
bool run_pr2(tTestSuite *test_suite, const char *input) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR2", "Tests for PR2 exercices");

    section = testSuite_getSection(test_suite, "PR2");
    assert(section != NULL);

    ok = run_pr2_ex1(section, input);
    ok = run_pr2_ex2(section, input) && ok;
    ok = run_pr2_ex3(section, input) && ok;

    return ok;
}

// Run all tests for Exercice 1 of PR2
bool run_pr2_ex1(tTestSection *test_section, const char *input) {
  tApiError error;
  tDate date;
  tWeighing weighing1604, weighing1704, weighing1804, weighing1704AAAA, weighing1704ZZZZ, weighing1704Code;
  tWeighingList weighingList;
  double totalWeight;
  
  bool passed = true;
  bool failed = false;
  bool fail_all = false;
  
  date_parse(&date, "16/04/2024");
  weighing_init(&weighing1604, "CCCC", 74.91, date, NOT_ASSIGNED);
  
  date_parse(&date, "17/04/2024");
  weighing_init(&weighing1704, "MMMM", 37.53, date, NOT_ASSIGNED);
  
  date_parse(&date, "18/04/2024");
  weighing_init(&weighing1804, "AAAA", 71.58, date, NOT_ASSIGNED);
  
  date_parse(&date, "17/04/2024");
  weighing_init(&weighing1704AAAA, "AAAA", 40.84, date, NOT_ASSIGNED);
  
  date_parse(&date, "17/04/2024");
  weighing_init(&weighing1704ZZZZ, "ZZZZ", 11.47, date, NOT_ASSIGNED);
  
  date_parse(&date, "17/04/2024");
  weighing_init(&weighing1704Code, "MMMM", 44.28, date, NOT_ASSIGNED);

  /////////////////////////////
  /////  PR2 EX1 TEST 1  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX1_1", "Initialize the weighing data structure");
  
  // Initialize the data
  error = weighingList_init(&weighingList);
  
  if (error != E_SUCCESS) {
    failed = true;
    passed = false;
    fail_all = true;
  }
  
  end_test(test_section, "PR2_EX1_1", !failed);
  
  /////////////////////////////
  /////  PR2 EX1 TEST 2  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX1_2", "Check if the weighing list is empty before adding data");
  if (fail_all) {
    failed = true;
  } else {
    if (!weighingList_empty(weighingList)) {
      failed = true;
      passed = false;
      fail_all = true;
    }
  }
  end_test(test_section, "PR2_EX1_2", !failed);
  
  /////////////////////////////
  /////  PR2 EX1 TEST 3  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX1_3", "Add a weighing to an empty weighing list");
  if (fail_all) {
    failed = true;
  } else {
    // Add the weighing
    error = weighingList_add(&weighingList, weighing1704);
    
    // Check result
    if (weighingList.first == NULL || weighingList.last == NULL) {
        failed = true;
    } else if (weighingList.first->prev != NULL || weighingList.last->next != NULL) {
        failed = true;
    } else if (strcmp(weighingList.first->elem.code, weighing1704.code) != 0) {
        failed = true;
    } else if (weighingList.first->elem.weight != weighing1704.weight) {
        failed = true;
    } else if (date_cmp(weighingList.first->elem.harvestDay, weighing1704.harvestDay) != 0) {
        failed = true;
    }
      
    if (failed) {
        fail_all = true;
        passed = false;
    }
  }
  end_test(test_section, "PR2_EX1_3", !failed);
  
  /////////////////////////////
  /////  PR2 EX1 TEST 4  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX1_4", "Add a weighing to non-empty weighing list");
  if (fail_all) {
    failed = true;
  } else {
    // Add the weighing
    error = weighingList_add(&weighingList, weighing1804);
    
    // Check result
    if (error != E_SUCCESS) {
        failed = true;
    } else if (weighingList.first == NULL || weighingList.last == NULL) {
        failed = true;
    } else if (weighingList.first->prev != NULL || weighingList.last->next != NULL) {
        failed = true;
    } else if (strcmp(weighingList.first->elem.code, weighing1704.code) != 0 || weighingList.first->elem.weight != weighing1704.weight || date_cmp(weighingList.first->elem.harvestDay, weighing1704.harvestDay) != 0) {
        failed = true;
    } else if (strcmp(weighingList.first->next->elem.code, weighing1804.code) != 0 || weighingList.first->next->elem.weight != weighing1804.weight || date_cmp(weighingList.first->next->elem.harvestDay, weighing1804.harvestDay) != 0) {
        failed = true;
    }
    
    if (!failed) {
        // Add the weighing
        error = weighingList_add(&weighingList, weighing1604);
        
        // Check result
        if (error != E_SUCCESS) {
            failed = true;
        } else if (weighingList.first == NULL || weighingList.last == NULL) {
            failed = true;
        } else if (weighingList.first->prev != NULL || weighingList.last->next != NULL) {
            failed = true;
        } else if (strcmp(weighingList.first->elem.code, weighing1604.code) != 0 || weighingList.first->elem.weight != weighing1604.weight || date_cmp(weighingList.first->elem.harvestDay, weighing1604.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.first->next->elem.code, weighing1704.code) != 0 || weighingList.first->next->elem.weight != weighing1704.weight || date_cmp(weighingList.first->next->elem.harvestDay, weighing1704.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.first->next->next->elem.code, weighing1804.code) != 0 || weighingList.first->next->next->elem.weight != weighing1804.weight || date_cmp(weighingList.first->next->next->elem.harvestDay, weighing1804.harvestDay) != 0) {
            failed = true;
        }
    }
    
    if (!failed) {
        if (strcmp(weighingList.last->elem.code, weighing1804.code) != 0 || weighingList.last->elem.weight != weighing1804.weight || date_cmp(weighingList.last->elem.harvestDay, weighing1804.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->elem.code, weighing1704.code) != 0 || weighingList.last->prev->elem.weight != weighing1704.weight || date_cmp(weighingList.last->prev->elem.harvestDay, weighing1704.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->prev->elem.code, weighing1604.code) != 0 || weighingList.last->prev->prev->elem.weight != weighing1604.weight || date_cmp(weighingList.last->prev->prev->elem.harvestDay, weighing1604.harvestDay) != 0) {
            failed = true;
        }
    }
      
    if (failed) {
        fail_all = true;
        passed = false;
    }
  }
  end_test(test_section, "PR2_EX1_4", !failed);
  
  /////////////////////////////
  /////  PR2 EX1 TEST 5  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX1_5", "Add a weighing to an existing day with different code");
  if (fail_all) {
    failed = true;
  } else {
    // Add the weighing
    error = weighingList_add(&weighingList, weighing1704AAAA);
    
    // Check result
    if (error != E_SUCCESS) {
        failed = true;
    } else if (weighingList.first == NULL || weighingList.last == NULL) {
        failed = true;
    } else if (weighingList.first->prev != NULL || weighingList.last->next != NULL) {
        failed = true;
    } else if (strcmp(weighingList.first->elem.code, weighing1604.code) != 0 || weighingList.first->elem.weight != weighing1604.weight || date_cmp(weighingList.first->elem.harvestDay, weighing1604.harvestDay) != 0) {
        failed = true;
    } else if (strcmp(weighingList.first->next->elem.code, weighing1704AAAA.code) != 0 || weighingList.first->next->elem.weight != weighing1704AAAA.weight || date_cmp(weighingList.first->next->elem.harvestDay, weighing1704AAAA.harvestDay) != 0) {
        failed = true;
    } else if (strcmp(weighingList.first->next->next->elem.code, weighing1704.code) != 0 || weighingList.first->next->next->elem.weight != weighing1704.weight || date_cmp(weighingList.first->next->next->elem.harvestDay, weighing1704.harvestDay) != 0) {
        failed = true;
    } else if (strcmp(weighingList.first->next->next->next->elem.code, weighing1804.code) != 0 || weighingList.first->next->next->next->elem.weight != weighing1804.weight || date_cmp(weighingList.first->next->next->next->elem.harvestDay, weighing1804.harvestDay) != 0) {
        failed = true;
    }
    
    if (!failed) {
        // Add the weighing
        error = weighingList_add(&weighingList, weighing1704ZZZZ);
        
        // Check result
        if (error != E_SUCCESS) {
            failed = true;
        } else if (weighingList.first == NULL || weighingList.last == NULL) {
            failed = true;
        } else if (weighingList.first->prev != NULL || weighingList.last->next != NULL) {
            failed = true;
        } else if (strcmp(weighingList.first->elem.code, weighing1604.code) != 0 || weighingList.first->elem.weight != weighing1604.weight || date_cmp(weighingList.first->elem.harvestDay, weighing1604.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.first->next->elem.code, weighing1704AAAA.code) != 0 || weighingList.first->next->elem.weight != weighing1704AAAA.weight || date_cmp(weighingList.first->next->elem.harvestDay, weighing1704AAAA.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.first->next->next->elem.code, weighing1704.code) != 0 || weighingList.first->next->next->elem.weight != weighing1704.weight || date_cmp(weighingList.first->next->next->elem.harvestDay, weighing1704.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.first->next->next->next->elem.code, weighing1704ZZZZ.code) != 0 || weighingList.first->next->next->next->elem.weight != weighing1704ZZZZ.weight || date_cmp(weighingList.first->next->next->next->elem.harvestDay, weighing1704ZZZZ.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.first->next->next->next->next->elem.code, weighing1804.code) != 0 || weighingList.first->next->next->next->next->elem.weight != weighing1804.weight || date_cmp(weighingList.first->next->next->next->next->elem.harvestDay, weighing1804.harvestDay) != 0) {
            failed = true;
        }
    }
    
    if (!failed) {
        if (strcmp(weighingList.last->elem.code, weighing1804.code) != 0 || weighingList.last->elem.weight != weighing1804.weight || date_cmp(weighingList.last->elem.harvestDay, weighing1804.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->elem.code, weighing1704ZZZZ.code) != 0 || weighingList.last->prev->elem.weight != weighing1704ZZZZ.weight || date_cmp(weighingList.last->prev->elem.harvestDay, weighing1704ZZZZ.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->prev->elem.code, weighing1704.code) != 0 || weighingList.last->prev->prev->elem.weight != weighing1704.weight || date_cmp(weighingList.last->prev->prev->elem.harvestDay, weighing1704.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->prev->prev->elem.code, weighing1704AAAA.code) != 0 || weighingList.last->prev->prev->prev->elem.weight != weighing1704AAAA.weight || date_cmp(weighingList.last->prev->prev->prev->elem.harvestDay, weighing1704AAAA.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->prev->prev->prev->elem.code, weighing1604.code) != 0 || weighingList.last->prev->prev->prev->prev->elem.weight != weighing1604.weight || date_cmp(weighingList.last->prev->prev->prev->prev->elem.harvestDay, weighing1604.harvestDay) != 0) {
            failed = true;
        }
    }
      
    if (failed) {
        fail_all = true;
        passed = false;
    }
  }
  end_test(test_section, "PR2_EX1_5", !failed);
  
  /////////////////////////////
  /////  PR2 EX1 TEST 6  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX1_6", "Add a weighing to an existing day with an existing code");
  if (fail_all) {
    failed = true;
  } else {
    // Add the weighing
    error = weighingList_add(&weighingList, weighing1704Code);
    
    // Check result
    if (error != E_SUCCESS) {
        failed = true;
    } else if (weighingList.first == NULL || weighingList.last == NULL) {
        failed = true;
    } else if (weighingList.first->prev != NULL || weighingList.last->next != NULL) {
        failed = true;
    } else if (strcmp(weighingList.first->elem.code, weighing1604.code) != 0 || weighingList.first->elem.weight != weighing1604.weight || date_cmp(weighingList.first->elem.harvestDay, weighing1604.harvestDay) != 0) {
        failed = true;
    } else if (strcmp(weighingList.first->next->elem.code, weighing1704AAAA.code) != 0 || weighingList.first->next->elem.weight != weighing1704AAAA.weight || date_cmp(weighingList.first->next->elem.harvestDay, weighing1704AAAA.harvestDay) != 0) {
        failed = true;
    } else if (strcmp(weighingList.first->next->next->elem.code, weighing1704.code) != 0 || weighingList.first->next->next->elem.weight != weighing1704.weight + weighing1704Code.weight || date_cmp(weighingList.first->next->next->elem.harvestDay, weighing1704.harvestDay) != 0) {
        failed = true;
    } else if (strcmp(weighingList.first->next->next->next->elem.code, weighing1704ZZZZ.code) != 0 || weighingList.first->next->next->next->elem.weight != weighing1704ZZZZ.weight || date_cmp(weighingList.first->next->next->next->elem.harvestDay, weighing1704ZZZZ.harvestDay) != 0) {
        failed = true;
    } else if (strcmp(weighingList.first->next->next->next->next->elem.code, weighing1804.code) != 0 || weighingList.first->next->next->next->next->elem.weight != weighing1804.weight || date_cmp(weighingList.first->next->next->next->next->elem.harvestDay, weighing1804.harvestDay) != 0) {
        failed = true;
    }
    
    if (!failed) {
        if (strcmp(weighingList.last->elem.code, weighing1804.code) != 0 || weighingList.last->elem.weight != weighing1804.weight || date_cmp(weighingList.last->elem.harvestDay, weighing1804.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->elem.code, weighing1704ZZZZ.code) != 0 || weighingList.last->prev->elem.weight != weighing1704ZZZZ.weight || date_cmp(weighingList.last->prev->elem.harvestDay, weighing1704ZZZZ.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->prev->elem.code, weighing1704.code) != 0 || weighingList.last->prev->prev->elem.weight != weighing1704.weight + weighing1704Code.weight || date_cmp(weighingList.last->prev->prev->elem.harvestDay, weighing1704.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->prev->prev->elem.code, weighing1704AAAA.code) != 0 || weighingList.last->prev->prev->prev->elem.weight != weighing1704AAAA.weight || date_cmp(weighingList.last->prev->prev->prev->elem.harvestDay, weighing1704AAAA.harvestDay) != 0) {
            failed = true;
        } else if (strcmp(weighingList.last->prev->prev->prev->prev->elem.code, weighing1604.code) != 0 || weighingList.last->prev->prev->prev->prev->elem.weight != weighing1604.weight || date_cmp(weighingList.last->prev->prev->prev->prev->elem.harvestDay, weighing1604.harvestDay) != 0) {
            failed = true;
        }
    }
      
    if (failed) {
        fail_all = true;
        passed = false;
    }
  }
  end_test(test_section, "PR2_EX1_6", !failed);
  
  /////////////////////////////
  /////  PR2 EX1 TEST 7  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX1_7", "Get the total weight by code until a certain date");
  if (fail_all) {
    failed = true;
  } else {
    date_parse(&date, "16/04/2024");
    totalWeight = weighingList_getWeight(weighingList, "MMMM", date);
    
    // Check result
    if (fabs(totalWeight - 0.0) > 0.01) {
        failed = true;
    }
    
    if (!failed) {
        date_parse(&date, "17/04/2024");
        totalWeight = weighingList_getWeight(weighingList, "MMMM", date);
        
        // Check result
        if (fabs(totalWeight - (weighing1704.weight + weighing1704Code.weight)) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        date_parse(&date, "18/04/2024");
        totalWeight = weighingList_getWeight(weighingList, "MMMM", date);
        
        // Check result
        if (fabs(totalWeight - (weighing1704.weight + weighing1704Code.weight) > 0.01)) {
            failed = true;
        }
    }
    
    if (!failed) {
        date_parse(&date, "16/04/2024");
        totalWeight = weighingList_getWeight(weighingList, "AAAA", date);
        
        // Check result
        if (fabs(totalWeight - 0.0) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        date_parse(&date, "17/04/2024");
        totalWeight = weighingList_getWeight(weighingList, "AAAA", date);
        
        // Check result
        if (fabs(totalWeight - weighing1704AAAA.weight) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        date_parse(&date, "18/04/2024");
        totalWeight = weighingList_getWeight(weighingList, "AAAA", date);
        
        // Check result
        if (fabs(totalWeight - (weighing1704AAAA.weight + weighing1804.weight)) > 0.01) {
            failed = true;
        }
    }
    
    if (failed) {
        fail_all = true;
        passed = false;
    }
  }
  end_test(test_section, "PR2_EX1_7", !failed);
  
  /////////////////////////////
  /////  PR2 EX1 TEST 7  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX1_8", "Release a weighing list");
  if (fail_all) {
    failed = true;
  } else {
    weighingList_free(&weighingList);
    
    // Check result
    if (weighingList.first != NULL || weighingList.last != NULL) {
        failed = true;
    }
    
    if (failed) {
        fail_all = true;
        passed = false;
    }
  }
  end_test(test_section, "PR2_EX1_8", !failed);
  
  // Release the structures
  weighing_free(&weighing1604);
  weighing_free(&weighing1704);
  weighing_free(&weighing1804);
  weighing_free(&weighing1704AAAA);
  weighing_free(&weighing1704ZZZZ);
  weighing_free(&weighing1704Code);

  return passed;
}

// Run all tests for Exercice 2 of PR2
bool run_pr2_ex2(tTestSection *test_section, const char *input) {
  tDate date;
  tWeighing weighing1604, weighing1704, weighing1804, weighing1704AAAA, weighing1704ZZZZ, weighing1704Code,
    weighing20211, weighing20212, weighing20221, weighing20222, weighing20231, weighing20232, weighing20233;
  tVineyardplot vineyardplot1, vineyardplot2, vineyardplot3, vineyardplot4, vineyardplot5, vineyardplot6,
    *pVineyardplot1, *pVineyardplot2, *pVineyardplot3, *pVineyardplot4;
  tWinegrower winegrower1, winegrower2, winegrower3, *pWinegrower1, *pWinegrower2, *pWinegrower3;
  tDO DOPenedes, DOEmporda, DOMonsant;
  double totalWeight, totalWeighing;
  int idx;
  
  bool passed = true;
  bool failed = false;
  bool fail_all = false;
  
  date_parse(&date, "16/04/2024");
  weighing_init(&weighing1604, "CCCC", 74.91, date, NOT_ASSIGNED);
  
  date_parse(&date, "17/04/2024");
  weighing_init(&weighing1704, "MMMM", 37.53, date, NOT_ASSIGNED);
  
  date_parse(&date, "18/04/2024");
  weighing_init(&weighing1804, "AAAA", 71.58, date, NOT_ASSIGNED);
  
  date_parse(&date, "17/04/2024");
  weighing_init(&weighing1704AAAA, "AAAA", 40.84, date, NOT_ASSIGNED);
  
  date_parse(&date, "17/04/2024");
  weighing_init(&weighing1704ZZZZ, "ZZZZ", 11.47, date, NOT_ASSIGNED);
  
  date_parse(&date, "17/04/2024");
  weighing_init(&weighing1704Code, "MMMM", 44.28, date, NOT_ASSIGNED);
  
  date_parse(&date, "01/01/2021");
  weighing_init(&weighing20211, "AA20211", 84.67, date, NOT_ASSIGNED);
  
  date_parse(&date, "02/01/2021");
  weighing_init(&weighing20212, "AA20212", 47.11, date, NOT_ASSIGNED);
  
  date_parse(&date, "01/01/2022");
  weighing_init(&weighing20221, "AA20221", 77.15, date, NOT_ASSIGNED);
  
  date_parse(&date, "02/01/2022");
  weighing_init(&weighing20222, "AA20222", 68.37, date, NOT_ASSIGNED);
  
  date_parse(&date, "01/01/2023");
  weighing_init(&weighing20231, "AA20231", 31.54, date, NOT_ASSIGNED);
  
  date_parse(&date, "02/01/2023");
  weighing_init(&weighing20232, "AA20232", 88.91, date, NOT_ASSIGNED);
  
  date_parse(&date, "03/01/2023");
  weighing_init(&weighing20233, "AA20233", 55.48, date, NOT_ASSIGNED);
  
  vineyardplot_init(&vineyardplot1, "87654321098765", "PE", 650.0, NOT_ASSIGNED);
  vineyardplot_init(&vineyardplot2, "76543210987654", "EM", 450.0, NOT_ASSIGNED);
  vineyardplot_init(&vineyardplot3, "65432109876543", "EM", 400.0,NOT_ASSIGNED);
  vineyardplot_init(&vineyardplot4, "54321098765432", "EM", 500.0,NOT_ASSIGNED);
  vineyardplot_init(&vineyardplot5, "43210987654321", "EM", 525.0,NOT_ASSIGNED);
  vineyardplot_init(&vineyardplot6, "32109876543210", "EM", 770.0,NOT_ASSIGNED);
  
  date_parse(&date, "01/01/2024");
  winegrower_init(&winegrower1, "98765432109876", "87654321K", date);
  
  date_parse(&date, "01/01/2024");
  winegrower_init(&winegrower2, "87654321098765", "98765432J", date);
  
  date_parse(&date, "01/01/2024");
  winegrower_init(&winegrower3, "76543210987654", "54927077H", date);
  
  do_init(&DOPenedes, "PE", "Penedes", 70.00);
  do_init(&DOEmporda, "EM", "Emporda", 65.00);
  do_init(&DOMonsant, "MO", "Monsant", 72.00);
  
  vineyardplotData_add(&(DOPenedes.vineyards), vineyardplot1);
  vineyardplotData_add(&(DOEmporda.vineyards), vineyardplot2);
  vineyardplotData_add(&(DOEmporda.vineyards), vineyardplot3);
  vineyardplotData_add(&(DOEmporda.vineyards), vineyardplot4);
  vineyardplotData_add(&(DOEmporda.vineyards), vineyardplot5);
  vineyardplotData_add(&(DOEmporda.vineyards), vineyardplot6);
  
  winegrowerList_insert(&(DOPenedes.winegrowers), winegrower1);
  pWinegrower1 = winegrowerList_find(DOPenedes.winegrowers, winegrower1.id);
  
  winegrowerList_insert(&(DOEmporda.winegrowers), winegrower2);
  pWinegrower2 = winegrowerList_find(DOEmporda.winegrowers, winegrower2.id);
  
  winegrowerList_insert(&(DOEmporda.winegrowers), winegrower3);
  pWinegrower3 = winegrowerList_find(DOEmporda.winegrowers, winegrower3.id);
  
  vineyardplotData_add(&(pWinegrower1->vineyardplots), vineyardplot1);
  vineyardplotData_add(&(pWinegrower2->vineyardplots), vineyardplot2);
  vineyardplotData_add(&(pWinegrower2->vineyardplots), vineyardplot3);
  vineyardplotData_add(&(pWinegrower2->vineyardplots), vineyardplot4);
  vineyardplotData_add(&(pWinegrower3->vineyardplots), vineyardplot5);
  vineyardplotData_add(&(pWinegrower3->vineyardplots), vineyardplot6);
  
  idx = vineyardplotData_find(pWinegrower1->vineyardplots, vineyardplot1.code);
  pVineyardplot1 = &(pWinegrower1->vineyardplots.elems[idx]);
  
  idx = vineyardplotData_find(pWinegrower2->vineyardplots, vineyardplot2.code);
  pVineyardplot2 = &(pWinegrower2->vineyardplots.elems[idx]);
  
  idx = vineyardplotData_find(pWinegrower2->vineyardplots, vineyardplot3.code);
  pVineyardplot3 = &(pWinegrower2->vineyardplots.elems[idx]);
  
  idx = vineyardplotData_find(pWinegrower2->vineyardplots, vineyardplot4.code);
  pVineyardplot4 = &(pWinegrower2->vineyardplots.elems[idx]);
  
  weighingList_add(&(pVineyardplot1->weights), weighing1604);
  weighingList_add(&(pVineyardplot1->weights), weighing1804);
  weighingList_add(&(pVineyardplot1->weights), weighing1704AAAA);
  weighingList_add(&(pVineyardplot1->weights), weighing1704ZZZZ);
  weighingList_add(&(pVineyardplot1->weights), weighing20212);
  weighingList_add(&(pVineyardplot1->weights), weighing20221);
  weighingList_add(&(pVineyardplot1->weights), weighing20222);
  weighingList_add(&(pVineyardplot1->weights), weighing20231);
  
  weighingList_add(&(pVineyardplot2->weights), weighing1704);
  weighingList_add(&(pVineyardplot2->weights), weighing20211);
  weighingList_add(&(pVineyardplot2->weights), weighing20232);
  
  weighingList_add(&(pVineyardplot3->weights), weighing1704Code);
  
  weighingList_add(&(pVineyardplot4->weights), weighing20233);
  
  /////////////////////////////
  /////  PR2 EX2 TEST 1  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX2_1", "Check getTotalWeightByWinegrower");
  if (fail_all) {
    failed = true;
  } else {
    totalWeight = doData_getTotalWeightByWinegrower(DOMonsant, winegrower1.id);
    
    if (totalWeight != 0.0) {
        failed = true;
    }
    
    if (!failed) {
        totalWeight = doData_getTotalWeightByWinegrower(DOPenedes, winegrower2.id);
        
        if (totalWeight != 0.0) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeight = doData_getTotalWeightByWinegrower(DOPenedes, winegrower1.id);
        
        if (totalWeight != 650.0) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeight = doData_getTotalWeightByWinegrower(DOEmporda, winegrower2.id);
        
        if (totalWeight != 1350.0) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeight = doData_getTotalWeightByWinegrower(DOEmporda, winegrower3.id);
        
        if (totalWeight != 1295.0) {
            failed = true;
        }
    }
    
    if (failed) {
      passed = false;
      fail_all = true;
    }
  }
  end_test(test_section, "PR2_EX2_1", !failed);
  
  /////////////////////////////
  /////  PR2 EX2 TEST 2  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR2_EX2_2", "Check getTotalWeighingByWineGrowerAndVineyardByYear");
  if (fail_all) {
    failed = true;
  } else {
    totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOPenedes, winegrower1.id, vineyardplot1.code, 2024);
    
    if (fabs(totalWeighing - 198.8) > 0.01) {
        failed = true;
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOPenedes, winegrower1.id, vineyardplot1.code, 2020);
        
        if (fabs(totalWeighing - 0.0) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOPenedes, winegrower1.id, vineyardplot1.code, 2021);
        
        if (fabs(totalWeighing - 47.11) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOPenedes, winegrower1.id, vineyardplot1.code, 2022);
        
        if (fabs(totalWeighing - 145.52) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOPenedes, winegrower1.id, vineyardplot1.code, 2023);
        
        if (fabs(totalWeighing - 31.54) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOEmporda, winegrower2.id, vineyardplot2.code, 2024);
        
        if (fabs(totalWeighing - 37.53) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOEmporda, winegrower2.id, vineyardplot2.code, 2021);
        
        if (fabs(totalWeighing - 84.67) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOEmporda, winegrower2.id, vineyardplot2.code, 2022);
        
        if (fabs(totalWeighing - 0.0) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOEmporda, winegrower2.id, vineyardplot2.code, 2023);
        
        if (fabs(totalWeighing - 88.91) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOMonsant, winegrower2.id, vineyardplot2.code, 2024);
        
        if (fabs(totalWeighing - 0.0) > 0.01) {
            failed = true;
        }
    }
    
    if (!failed) {
        totalWeighing = doData_getTotalWeighingByWineGrowerAndVineyardByYear(DOMonsant, winegrower3.id, vineyardplot6.code, 2020);
        
        if (fabs(totalWeighing - 0.0) > 0.01) {
            failed = true;
        }
    }
    
    if (failed) {
      passed = false;
      fail_all = true;
    }
  }
  end_test(test_section, "PR2_EX2_2", !failed);
  
  // Release of the data used
  weighing_free(&(weighing1604));
  weighing_free(&(weighing1704));
  weighing_free(&(weighing1804));
  weighing_free(&(weighing1704AAAA));
  weighing_free(&(weighing1704ZZZZ));
  weighing_free(&(weighing1704Code));
  weighing_free(&(weighing20211));
  weighing_free(&(weighing20212));
  weighing_free(&(weighing20221));
  weighing_free(&(weighing20222));
  weighing_free(&(weighing20231));
  weighing_free(&(weighing20232));
  weighing_free(&(weighing20233));
  
  vineyardplot_free(&(vineyardplot1));
  vineyardplot_free(&(vineyardplot2));
  vineyardplot_free(&(vineyardplot3));
  vineyardplot_free(&(vineyardplot4));
  vineyardplot_free(&(vineyardplot5));
  vineyardplot_free(&(vineyardplot6));
  
  winegrower_free(&(winegrower1));
  winegrower_free(&(winegrower2));
  winegrower_free(&(winegrower3));
  
  do_free(&(DOPenedes));
  do_free(&(DOEmporda));
  do_free(&(DOMonsant));
  
  return passed;
}

// Run all tests for Exercice 3 of PR2
bool run_pr2_ex3(tTestSection *test_section, const char *input) {
    tApiData data;
    tApiError error;
    int nDOs;
    int nPeople;
    int nVineyardplot;
    int nWinegrowers;

    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    /////////////////////////////
    /////  PR2 EX3 TEST 1  //////
    /////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_1", "Initialize the API data");
    
    // Initialize the data    
    error = api_initData(&data);
    
    if (error != E_SUCCESS) {
        passed = false;
        failed = true;
        fail_all = true;
    } else if (api_DOCount(data) != 0) {
        passed = false; 
        failed = true;
        fail_all = true;
    }

    end_test(test_section, "PR2_EX3_1", !failed);
    
    /////////////////////////////
    /////  PR2 EX3 TEST 2  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX3_2", "Load API data");
    
    if (!fail_all) {
        error = api_loadData(&data, input, true);
        
        nVineyardplot = api_vineyardplotCount(data);
        nWinegrowers = api_winegrowersCount(data);
        nPeople = api_peopleCount(data);

        if (error != E_SUCCESS || nPeople != 3 || nWinegrowers != 3 || nVineyardplot != 8) {
            passed = false;
            failed = true;
            fail_all = true;
        }
    }
    
    end_test(test_section, "PR2_EX3_2", !failed);
    
    /////////////////////////////
    /////  PR2 EX3 TEST 3  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX3_3", "Obtain number of DOs in the API");
    
    if (!fail_all) {
        nDOs = api_DOCount(data);
        
        if (nDOs != 3) {
            passed = false;
            failed = true;
            fail_all = true;
        }
    }
    
    end_test(test_section, "PR2_EX3_3", !failed);
    
    // Release of the data used
    api_freeData(&data);

    return passed;
}
