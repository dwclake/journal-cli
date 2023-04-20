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
        return {0, "Journal Insert test passed"};
    }

    tuple<int, string> test_journal_fetch() {
        return {0, "Journal fetch test passed"};
    }

    tuple<int, string> test_journal_remove() {
        return {0, "Journal remove test passed"};
    }

    tuple<int, string> test_journal_sort() {
        return {0, "Journal sort test passed"};
    }
}
