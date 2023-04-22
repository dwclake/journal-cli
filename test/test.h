#pragma once

#include <vector>
#include <tuple>
#include "../include/app/menu.h"
#include "../include/journal/journal.h"

namespace Test {
    using namespace std;

    vector<function<string()>>* tests(); // Runs all tests and returns a vector of tuples containing the result of each test
                                         
    // Tests journal insert function - !THROWS
    string test_journal_insert(); 
    // Tests journal edit function - !THROWS
    string test_journal_edit(); 
    // Tests journal fetch function - !THROWS
    string test_journal_fetch(); 
    // Tests journal remove function - !THROWS
    string test_journal_remove(); 
    // Tests journal sort function - !THROWS
    string test_journal_sort(); 
}
