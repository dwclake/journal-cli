#include <assert.h>
#include "test.h"

namespace Test {
    using namespace std;


    vector<tuple<int, string>>* test() {
        printf("Running 4 Tests:\n");

        static vector<tuple<int, string>> test_results = {
            test_journal_insert(),
            test_journal_remove(),
            test_journal_fetch(),
            test_journal_remove()
        };
        return &test_results;
    }

    tuple<int, string> test_journal_insert() {
        unsigned result;
        string message;

        printf("Testing journal insert...\n");

        journal::Journal j; // Create new journal object
        // Create a page with a title and a body
        journal::Page p = journal::Page::builder()
            ->title("Dobar dan!")
            ->build();
        unsigned k = p.key();
        // Insert page into the journal
        j.insert(p);
        j.insert(p);
        j.insert(p);

        j.display();
        
        result = (j.size() == 3)? 0: 1;
        message = (!result)
            ? "Journal insert test passed" 
            : "Journal insert test failed, journal size incorrect";
        
        return {result, message};
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
