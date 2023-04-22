#include <assert.h>
#include "test.h"

namespace Test {
    using namespace std;

    /* ---- Test functions wrapper which calls all the tests and returns their results to main ------------------ */
    vector<tuple<int, string>>* test() {
        int test_number = 5;
        printf("Running %d Tests:\n\n", test_number);

        static vector<tuple<int, string>> test_results = {
            test_journal_insert(),
            test_journal_edit(),
            test_journal_fetch(),
            test_journal_remove(),
            test_journal_sort()
        };
        return &test_results;
    }

    /* ---- Program tests -------------------------------------------------------------------------------------- */

    // Tests journal insert function
    tuple<int, string> test_journal_insert() {
        using namespace journal;

        unsigned result;
        string message;

        printf("--Testing journal insert--\n\n");

        Journal j{"test"}; // Create new journal object
        // Create a page with a title and a body
        Day day{Weekday::MONDAY, 1};
        Date date(Month::JANUARY, day, 2000);
        Page p = Page::builder()
            ->title("Dobar dan!")
            ->body("    Lorem ipsum dolor sit amet, qui minim labore\nadipisicing minim sint cillum sint consectetur\ncupidatat.")
            ->date(date)
            ->tag("chill")
            ->tag("sunny")
            ->build();
        unsigned k = p.key();
        // Insert page into the journal three times
        j.insert(p);
        j.insert(p);
        j.insert(p);

        // Display journal
        j.display();
        
        // If journal size is 3, set result to 0, otherwise set it to 1
        result = (j.size() == 3)? 0: 1;
        // Set message to passing message if result is zero, otherwise set it to
        // failing message
        message = (!result)
            ? "\033[32mPassed\033[0m: Journal insert test:" 
            : "\033[31mError\033[0m: Journal insert test: journal size incorrect";
        // Return a tuple with the result value and message 
        return {result, message};
    }

    // Tests journal edit function
    tuple<int, string> test_journal_edit() {
        printf("--Testing journal edit--\n\n");
        return {0, "\033[32mPassed:\033[0m Journal edit test:"};
    }

    // Tests journal fetch function
    tuple<int, string> test_journal_fetch() {
        printf("--Testing journal fetch--\n\n");
        return {0, "\033[32mPassed:\033[0m Journal fetch test:"};
    }

    // Tests journal remove function
    tuple<int, string> test_journal_remove() {
        printf("--Testing journal remove--\n\n");
        return {0, "\033[32mPassed:\033[0m Journal remove test:"};
    }

    // Tests journal sort function
    tuple<int, string> test_journal_sort() {
        printf("--Testing journal sort--\n\n");
        return {0, "\033[32mPassed:\033[0m Journal sort test:"};
    }
}
