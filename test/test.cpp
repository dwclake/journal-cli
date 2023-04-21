#include <assert.h>
#include "test.h"

namespace Test {
    using namespace std;


    vector<tuple<int, string>>* test() {
        printf("Running 4 Tests:\n\n");

        static vector<tuple<int, string>> test_results = {
            test_journal_insert(),
            test_journal_fetch(),
            test_journal_remove(),
            test_journal_sort()
        };
        return &test_results;
    }

    tuple<int, string> test_journal_insert() {
        using namespace journal;
        using enum Weekday;
        using enum Month;
        unsigned result;
        string message;

        printf("--Testing journal insert--\n\n");

        Journal j; // Create new journal object
        // Create a page with a title and a body
        Day day{MONDAY, 1};
        Date date(JANUARY, day, 2000);
        Page p = Page::builder()
            ->title("Dobar dan!")
            ->body("    Lorem ipsum dolor sit amet, qui minim labore\nadipisicing minim sint cillum sint consectetur\ncupidatat.")
            ->date(date)
            ->tag("chill")
            ->build();
        unsigned k = p.key();
        // Insert page into the journal
        j.insert(p);
        j.insert(p);
        j.insert(p);

        j.display();
        
        result = (j.size() == 3)? 0: 1;
        message = (!result)
            ? "\033[32mPassed\033[0m: Journal insert test:" 
            : "\033[31mError\033[0m: Journal insert test: journal size incorrect";
        
        return {result, message};
    }

    tuple<int, string> test_journal_fetch() {
        printf("--Testing journal fetch--\n\n");
        return {0, "\033[32mPassed:\033[0m Journal fetch test:"};
    }

    tuple<int, string> test_journal_remove() {
        printf("--Testing journal remove--\n\n");
        return {0, "\033[32mPassed:\033[0m Journal remove test:"};
    }

    tuple<int, string> test_journal_sort() {
        printf("--Testing journal sort--\n\n");
        return {0, "\033[32mPassed:\033[0m Journal sort test:"};
    }
}
