#pragma once

#include <vector>
#include <tuple>
#include "../includes/menu.h"
#include "../includes/journal.h"

namespace Test {
    using namespace std;

    vector<tuple<int, string>>* test();
    tuple<int, string> test_journal_insert();
    tuple<int, string> test_journal_fetch();
    tuple<int, string> test_journal_remove();
    tuple<int, string> test_journal_sort();
}
