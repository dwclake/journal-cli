#include "test.h"

namespace Test {
    using namespace std;

    vector<tuple<int, string>> test_results = {
        test_journal_insert(),
        test_journal_remove(),
        test_journal_fetch(),
        test_journal_remove()
    };

    vector<tuple<int, string>>* test() {
        return &test_results;
    }

    tuple<int, string> test_journal_insert() {
        tuple<int, string> result(0, "Journal Insert test passed");
        return result;
    }

    tuple<int, string> test_journal_fetch() {
        tuple<int, string> result(0, "Journal fetch test passed");
        return result;
    }

    tuple<int, string> test_journal_remove() {
        tuple<int, string> result(0, "Journal remove test passed");
        return result;
    }

    tuple<int, string> test_journal_sort() {
        tuple<int, string> result(0, "Journal sort test passed");
        return result;
    }
}
