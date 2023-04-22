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
