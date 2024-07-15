#include "test_pr1.h"
#include "api.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


// Run all tests for PR1
bool run_pr1(tTestSuite *test_suite, const char *input) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR1", "Tests for PR1 exercices");

    section = testSuite_getSection(test_suite, "PR1");
    assert(section != NULL);

    ok = run_pr1_ex1(section, input);
    ok = run_pr1_ex2(section, input) && ok;
    ok = run_pr1_ex3(section, input) && ok;

    return ok;
}

// Run all tests for Exercice 1 of PR1
bool run_pr1_ex1(tTestSection *test_section, const char *input) {
  bool passed = true, failed = false;
  const char *version;

  /////////////////////////////
  /////  PR1 EX1 TEST 1  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX1_1", "Read version information.");
  // Get the version
  version = api_version();
  if (strcmp(version, "UOC PP 20232") != 0) {
    failed = true;
    passed = false;
  }
  end_test(test_section, "PR1_EX1_1", !failed);

  return passed;
}

// Run all tests for Exercice 2 of PR1
bool run_pr1_ex2(tTestSection *test_section, const char *input) {
  tApiData data;
  tApiError error;
  tCSVEntry entry;
  
  tWinegrower *pWinegrower;
  int nVineyardplot;
  int nWinegrowers;
  int nPeople;
  bool passed = true;
  bool failed = false;
  bool fail_all = false;

  /////////////////////////////
  /////  PR1 EX2 TEST 1  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_1", "Initialize the API data structure");
  // Initialize the data
  error = api_initData(&data);
  if (error != E_SUCCESS) {
    failed = true;
    passed = false;
    fail_all = true;
  }
  end_test(test_section, "PR1_EX2_1", !failed);

  /////////////////////////////
  /////  PR1 EX2 TEST 2  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_2", "Add a winegrower with invalid format");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01/12/2023;123456789;01234567890123;AA-2003-10000;TA;1184.00;3", "WINEGROWENAWER");
    
    error = api_addWinegrower(&data, entry);
    if (error != E_INVALID_ENTRY_TYPE) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
    
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01/12/2023;123456789;01234567890123;AA-2003-10000;TA;1184.00;3;EXTRA", "WINEGROWER");
    
    error = api_addWinegrower(&data, entry);
    if (error != E_INVALID_ENTRY_FORMAT) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
    
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01/12/2023;123456789;AA-2003-10000;TA;1184.00;3", "WINEGROWER");
    
    error = api_addWinegrower(&data, entry);
    if (error != E_INVALID_ENTRY_FORMAT) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
  }
  end_test(test_section, "PR1_EX2_2", !failed);

  /////////////////////////////
  /////  PR1 EX2 TEST 3  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_3", "Add a valid winegrower");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01/12/2023;123456789;01234567890123;TA-2023-12000;TA;1184.00;3", "WINEGROWER");
              
    error = api_addWinegrower(&data, entry);
    if (error != E_SUCCESS) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
  }
  end_test(test_section, "PR1_EX2_3", !failed);

  /////////////////////////////
  /////  PR1 EX2 TEST 4  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_4", "Find a Winegrower in the data");
  if (fail_all) {
    failed = true;
  } else {

    pWinegrower = apiWinegrower_find(&data, "01234567890123");
    
    if (pWinegrower == NULL) {
      failed = true;
      passed = false;
      fail_all = true;
    } else if ((strcmp(pWinegrower->id, "01234567890123") != 0)) {
        failed = true;
        passed = false;
        fail_all = true;
           
        }
  }
  end_test(test_section, "PR1_EX2_4", !failed);

  /////////////////////////////
  /////  PR1 EX2 TEST 5  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_5", "Check the number of wineyards");
  if (fail_all) {
    failed = true;
  } else {
    nWinegrowers = api_winegrowersCount(data);
    if (nWinegrowers != 1) {
      failed = true;
      passed = false;
      fail_all = true;
    }
  }
  end_test(test_section, "PR1_EX2_5", !failed);
  
    /////////////////////////////
  /////  PR1 EX2 TEST 6  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_6", "Check the number of vineyardplots");
  if (fail_all) {
    failed = true;
  } else {
    nVineyardplot = api_vineyardplotCount(data);
    if (nVineyardplot != 1) {
      failed = true;
      passed = false;
      fail_all = true;
    }
  }
  end_test(test_section, "PR1_EX2_6", !failed);

  /////////////////////////////
  /////  PR1 EX2 TEST 7  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_7", "Add a vineyardplot with invalid code");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01234567890123;AAA-12345-12300;PE;1184.00;3", "VINEYARD_PLOT");
    
    error = api_addVineyardplot(&data, entry);
    if (error != E_INVALID_VINEYARD_CODE) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
    
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01234567890123;TA-23-01000;PE;1184.00;3", "VINEYARD_PLOT");
    
    error = api_addVineyardplot(&data, entry);
    if (error != E_INVALID_VINEYARD_CODE) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
    
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01234567890123;TA-2023-12;PE;1184.00;3", "VINEYARD_PLOT");
    
    error = api_addVineyardplot(&data, entry);
    if (error != E_INVALID_VINEYARD_CODE) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
    
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01234567890123;TA#2023#12000;PE;1184.00;3", "VINEYARD_PLOT");
    
    error = api_addVineyardplot(&data, entry);
    if (error != E_INVALID_VINEYARD_CODE) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
  }
  end_test(test_section, "PR1_EX2_7", !failed);

  /////////////////////////////
  /////  PR1 EX2 TEST 8  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_8", "Add a vineyardplot with invalid fields");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01234567890123;AA-2023-12;AA;1184.00;3", "VINEYARD_PLOTERRRR");
    
    error = api_addVineyardplot(&data, entry);
    if (error != E_INVALID_ENTRY_TYPE) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
    
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01234567890123;AA-2023-12;AA;1184.00;3;EXTRA", "VINEYARD_PLOT");
    
    error = api_addVineyardplot(&data, entry);
    if (error != E_INVALID_ENTRY_FORMAT) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
    
    csv_initEntry(&entry);
    csv_parseEntry(&entry, "01234567890123;AA-2023-12;1184.00;3", "VINEYARD_PLOT");
    
    error = api_addVineyardplot(&data, entry);
    if (error != E_INVALID_ENTRY_FORMAT) {
      failed = true;
      passed = false;
      fail_all = true;
    }
    csv_freeEntry(&entry);
  }
  end_test(test_section, "PR1_EX2_8", !failed);

  /////////////////////////////
  /////  PR1 EX2 TEST 9  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_9", "Free API data");
  if (fail_all) {
    failed = true;
  } else {
    error = api_freeData(&data);
    nPeople = api_peopleCount(data);
    nWinegrowers = api_winegrowersCount(data);
    if (error != E_SUCCESS || nPeople != 0 || nWinegrowers != 0) {
      failed = true;
      passed = false;
      fail_all = true;
    }
  }
  end_test(test_section, "PR1_EX2_9", !failed);

  /////////////////////////////
  /////  PR1 EX2 TEST 10  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX2_10", "Load data from file");
  // Load basic data to the API
  if (fail_all) {
    failed = true;
  } else {
    error = api_loadData(&data, input, true);
    nPeople = api_peopleCount(data);
    nWinegrowers = api_winegrowersCount(data);
    nVineyardplot = api_vineyardplotCount(data);
    
    if (error != E_SUCCESS || nPeople != 3 || nWinegrowers != 3 || nVineyardplot!= 8) {
      failed = true;
      passed = false;
    }
  }
  end_test(test_section, "PR1_EX2_10", !failed);

  // Release all data
  api_freeData(&data);

  return passed;
}

// Run all tests for Exercice 3 of PR1
bool run_pr1_ex3(tTestSection *test_section, const char *input) {
  tApiData data;
  tApiError error;
  tCSVEntry entry;
  tCSVEntry refEntry;
  tCSVData report;
  tCSVData refReport;
  int nPeople;
  int nVineyardplot;
  int nWinegrowers;
  bool passed = true;
  bool failed = false;
  bool fail_all = false;

  // Initialize the data
  error = api_initData(&data);
  if (error != E_SUCCESS) {
    passed = false;
    fail_all = true;
  }

  if (!fail_all) {
    error = api_loadData(&data, input, true);
    nPeople = api_peopleCount(data);     
    nWinegrowers = api_winegrowersCount(data);
    nVineyardplot = api_vineyardplotCount(data);
     
    if (error != E_SUCCESS || nPeople != 3 || nWinegrowers !=3 || nVineyardplot!= 8) {
      passed = false;
      fail_all = true;
    }
  }

  /////////////////////////////
  /////  PR1 EX3 TEST 1  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX3_1", "Request a valid winegrower");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    csv_initEntry(&refEntry);
    csv_parseEntry(&refEntry, "76543210987654;54927077H;04/12/2023", "WINEGROWER");
    error = api_getWinegrower(data, "76543210987654", &entry);
    if (error != E_SUCCESS || !csv_equalsEntry(entry, refEntry)) {
      failed = true;
      passed = false;
    }
    csv_freeEntry(&entry);
    csv_freeEntry(&refEntry);
  }
  end_test(test_section, "PR1_EX3_1", !failed);

  /////////////////////////////
  /////  PR1 EX3 TEST 2  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX3_2", "Request a missing winegrower");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    error = api_getWinegrower(data, "NO_GROWER", &entry);    if (error != E_WINEGROWER_NOT_FOUND) {
      failed = true;
      passed = false;
    }
    csv_freeEntry(&entry);
  }
  end_test(test_section, "PR1_EX3_2", !failed);

  /////////////////////////////
  /////  PR1 EX3 TEST 3  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX3_3", "Request a vineyard_plot with invalid code");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    csv_initEntry(&refEntry);
    csv_parseEntry(&refEntry, "TA-2024-00004;TA;800.25", "VINEYARD_PLOT");

    error = api_getVineyardplot(data, "ta-2024-00004", &entry);
    if (error != E_INVALID_VINEYARD_CODE) {
      failed = true;
      passed = false;
      fail_all = true;
    } else {
       error = api_getVineyardplot(data, "TA-2024-4", &entry);
      if (error != E_INVALID_VINEYARD_CODE) {
        failed = true;
        passed = false;
        fail_all = true;
      } else {
        error = api_getVineyardplot(data, "TA-24-00004", &entry);
        if (error != E_INVALID_VINEYARD_CODE) {
          failed = true;
          passed = false;
          fail_all = true;
        }
      }
    }
    csv_freeEntry(&entry);
    csv_freeEntry(&refEntry);
  }
  end_test(test_section, "PR1_EX3_3", !failed);

  /////////////////////////////
  /////  PR1 EX3 TEST 4  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX3_4", "Request a valid vineyard");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    csv_initEntry(&refEntry);
    csv_parseEntry(&refEntry, "EM-2024-00006;EM;900.00", "VINEYARD_PLOT");
    error = api_getVineyardplot(data, "EM-2024-00006", &entry);
    if (error != E_SUCCESS || !csv_equalsEntry(entry, refEntry)) {
      failed = true;
      passed = false;
    }
    csv_freeEntry(&entry);
    csv_freeEntry(&refEntry);
  }
  end_test(test_section, "PR1_EX3_4", !failed);

  /////////////////////////////
  /////  PR1 EX3 TEST 5  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX3_5", "Request a missing vineyard");
  if (fail_all) {
    failed = true;
  } else {
    csv_initEntry(&entry);
    error = api_getVineyardplot(data, "PR-2020-00001", &entry);
    if (error != E_VINEYARD_NOT_FOUND) {
      failed = true;
      passed = false;
    }
    csv_freeEntry(&entry);
  }
  end_test(test_section, "PR1_EX3_5", !failed);

  /////////////////////////////
  /////  PR1 EX3 TEST 6  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX3_6", "Get registered winegrowers");
  if (fail_all) {
    failed = true;
  } else {
    csv_init(&report);
    csv_init(&refReport);

    csv_addStrEntry(&refReport, "76543210987654;54927077H;04/12/2023", "WINEGROWER");    
    csv_addStrEntry(&refReport, "87654321098765;98765432J;03/12/2023", "WINEGROWER");
    csv_addStrEntry(&refReport, "98765432109876;87654321K;02/12/2023", "WINEGROWER");


    error = api_getWinegrowers(data, &report);
    if (error != E_SUCCESS || !csv_equals(report, refReport)) {
      failed = true;
      passed = false;
    }
    csv_free(&report);
    csv_free(&refReport);
  }
  end_test(test_section, "PR1_EX3_6", !failed);

  /////////////////////////////
  /////  PR1 EX3 TEST 7  //////
  /////////////////////////////
  failed = false;
  start_test(test_section, "PR1_EX3_7", "Get registered vineyardplots");
  if (fail_all) {
    failed = true;
  } else {
    csv_init(&report);
    csv_init(&refReport);        
            
    // winegrower 76543210987654
    csv_addStrEntry(&refReport, "MO-2023-45678;MO;1100.75" ,"VINEYARD_PLOT");
    csv_addStrEntry(&refReport, "TA-2024-00004;TA;800.25" ,"VINEYARD_PLOT");
    csv_addStrEntry(&refReport, "PR-2024-00005;PR;850.75" ,"VINEYARD_PLOT");
    csv_addStrEntry(&refReport, "EM-2024-00006;EM;900.00" ,"VINEYARD_PLOT");
    
    // winegrower 87654321098765
    csv_addStrEntry(&refReport, "EM-2023-54321;EM;1200.50" ,"VINEYARD_PLOT");
    csv_addStrEntry(&refReport, "CS-2024-00002;CS;650.00" ,"VINEYARD_PLOT");
    csv_addStrEntry(&refReport, "CB-2024-00003;CB;700.50" ,"VINEYARD_PLOT");
    // winegrower 98765432109876
    csv_addStrEntry(&refReport, "PE-2023-67890;PE;950.00","VINEYARD_PLOT");          
        
    error = api_getVineyardplots(data, &report);
    if (error != E_SUCCESS || !csv_equals(report, refReport)) {
      failed = true;
      passed = false;
    }
    csv_free(&report);
    csv_free(&refReport);
  }
  end_test(test_section, "PR1_EX3_7", !failed);

  // Release all data
  api_freeData(&data);

  return passed;
}
