#pragma once

#include <tuple>
#include <expected>
#include <matchit.h>
//#include <range/v3/all.hpp>
//#include <fmt/format.h>

#include "../include/app/menu.h"
#include "../include/journal/journal.h"

namespace Test {
    using namespace std;

    using error = tuple<unsigned, string>; // Error type alias

    vector<function<expected<string, error>()>>* tests(); // Runs all tests and returns a vector of tuples containing the result of each test
                                         
    // Tests journal insert function
    expected<string, error> test_journal_insert(); 
    // Tests journal edit function
    expected<string, error> test_journal_edit(); 
    // Tests journal fetch function
    expected<string, error> test_journal_fetch(); 
    // Tests journal remove function
    expected<string, error> test_journal_remove(); 
    // Tests journal sort function
    expected<string, error> test_journal_sort(); 
}
