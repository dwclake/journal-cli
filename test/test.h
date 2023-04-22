#pragma once

#include <vector>
#include <tuple>
#include "../include/menu/menu.h"
#include "../include/journal/journal.h"

namespace Test {
    using namespace std;

    vector<tuple<int, string>>* test(); // Runs all tests and returns a vector of tuples containing the result of each test

    tuple<int, string> test_journal_insert(); // Tests journal insert function
    tuple<int, string> test_journal_edit(); // Tests journal edit function
    tuple<int, string> test_journal_fetch(); // Tests journal fetch function
    tuple<int, string> test_journal_remove(); // Tests journal remove function
    tuple<int, string> test_journal_sort(); // Tests journal sort function
}
