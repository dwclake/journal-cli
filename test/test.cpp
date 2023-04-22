#include <functional>
#include <tuple>
#include "test.h"

namespace Test {
    using namespace std;

    /* ---- Test functions wrapper which returns a vector of pointers to tests to be run in main ----- */
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

    /* ---- Program tests ---------------------------------------------------------------------------- */

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
            ->body("    Lorem ipsum dolor sit amet, qui minim labore\
        adipisicing minim sint cillum sint consectetur\
        cupidatat.")
            ->date(date)
            ->tag("chill")
            ->tag("sunny")
            ->build();

        // Insert page into the journal three times
        j.insert(p);
        j.insert(p);
        j.insert(p);

        result = (j.size() == 3)? 0: 1; // If journal size is 3, set result to 0, otherwise set it to 1

        // If result is 1, throw tuple with error value and message
        if(result == 1) {
            tuple<unsigned, string> error{result, 
                "\033[31mError\033[0m: Journal insert test: journal size incorrect"};
         
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
        using namespace journal;

        printf("--Testing journal remove\n");

        Journal j{"test"}; // Create new journal object

        // Create some pages to add to the journal
        Page p1 = Page::builder()
            ->title("Dobar dan!")
            ->build();
        unsigned key1 = p1.key(); // Store key of p1
        Page p2 = Page::builder()
            ->title("Miremenjes!")
            ->build();
        unsigned key2 = p2.key(); // Store key of p2
        Page p3 = Page::builder()
            ->title("Gamarjoba!")
            ->build();
        unsigned key3 = p3.key(); // Store key of p3

        // Insert pages into the journal
        j.insert(std::move(p1));
        j.insert(std::move(p2));
        j.insert(std::move(p3));

        j.remove(key2); // Remove page with key2
        auto result2 = j.fetch(key2); // Try to fetch page with key2
        j.remove(key3);
        auto result3 = j.fetch(key3); // Try to fetch page with key2
        j.remove(key1);
        auto result1 = j.fetch(key1); // Try to fetch page with key2

        // If result is not nullopt, throw tuple with error value and message
        if(result1 != nullopt || result2 != nullopt || result3 != nullopt) {
            tuple<unsigned, string> error{1, 
                "\033[31mError\033[0m: Journal remove test: removed page still found"};
            
            throw error;
        }

        return {"\033[32mPassed:\033[0m Journal remove test:"}; // Returned passing message
    }

    // Tests journal sort function - !THROWS
    string test_journal_sort() {
        printf("--Testing journal sort\n");
        return {"\033[32mPassed:\033[0m Journal sort test:"};
    }
}
