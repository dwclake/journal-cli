#pragma once

#include <vector>
#include <tuple>
#include "../include/menu/menu.h"
#include "../include/journal/journal.h"

namespace Test {
    using namespace std;

    vector<function<string()>>* tests(); // Runs all tests and returns a vector of tuples containing the result of each test

    string test_journal_insert(); // Tests journal insert function
    string test_journal_edit(); // Tests journal edit function
    string test_journal_fetch(); // Tests journal fetch function
    string test_journal_remove(); // Tests journal remove function
    string test_journal_sort(); // Tests journal sort function
}
