#include <assert.h>
#include <functional>
#include <tuple>
#include "test.h"

namespace Test {
    using namespace std;

    /* ---- Test functions wrapper which returns a vector of pointers to tests which will be run in main ------- */
    vector<function<string()>>* tests() {

        static vector<function<string()>> tests = {
            test_journal_insert,
            test_journal_edit,
            test_journal_fetch,
            test_journal_remove,
            test_journal_sort
        };
        return &tests;
    }

    /* ---- Program tests -------------------------------------------------------------------------------------- */

    // Tests journal insert function - !THROWS
    string test_journal_insert() {
        using namespace journal;

        printf("--Testing journal insert\n");

        unsigned result; // Return value to throw to main if their is an error

        Journal j{"test"}; // Create new journal object

        // Create a page with a title, body, date, and two tags
        Day day{Weekday::MONDAY, 1};
        Date date(Month::JANUARY, day, 2000);
        Page p = Page::builder()
            ->title("Dobar dan!")
            ->body("    Lorem ipsum dolor sit amet, qui minim labore\nadipisicing minim sint cillum sint consectetur\ncupidatat.")
            ->date(date)
            ->tag("chill")
            ->tag("sunny")
            ->build();

        // Insert page into the journal three times
        j.insert(p);
        j.insert(p);
        j.insert(p);

        result = (j.size() == 3)? 0: 1; // If journal size is 3, set result to 0, 
                                        // otherwise set it to 1

        // If result is 1, throw tuple with error value and message
        if(result == 1) {
            tuple<unsigned, string> error{result, "\033[31mError\033[0m: Journal insert test: journal size incorrect"};
            throw error;
        }

        return "\033[32mPassed\033[0m: Journal insert test:"; // Return passing message
    }

    // Tests journal edit function - !THROWS
    string test_journal_edit() {
        printf("--Testing journal edit\n");
        return {"\033[32mPassed:\033[0m Journal edit test:"};
    }

    // Tests journal fetch function - !THROWS
    string test_journal_fetch() {
        printf("--Testing journal fetch\n");
        return {"\033[32mPassed:\033[0m Journal fetch test:"};
    }

    // Tests journal remove function - !THROWS
    string test_journal_remove() {
        printf("--Testing journal remove\n");
        return {"\033[32mPassed:\033[0m Journal remove test:"};
    }

    // Tests journal sort function - !THROWS
    string test_journal_sort() {
        printf("--Testing journal sort\n");
        return {"\033[32mPassed:\033[0m Journal sort test:"};
    }
}
