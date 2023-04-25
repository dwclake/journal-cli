#include "test.h"

namespace Test {

    /* ---- Test functions wrapper which returns a vector of pointers to tests to be run in main ----- */
    vector<function<expected<string, error>()>>* tests() {

        static vector<function<expected<string, error>()>> tests = {
            test_journal_insert,
            test_journal_fetch,
            test_journal_remove,
            test_journal_sort
        };
        return &tests;
    }

    /* ---- Program tests ---------------------------------------------------------------------------- */

    // Tests journal insert function
    expected<string, error> test_journal_insert() {
        using namespace journal;

        printf("--Testing journal insert\n");

        int result; // Return value to throw to main if there is an error

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

        // If result is 1, return tuple with error value and message
        if(result == 1) {
            return unexpected( error {
                result,
                "\033[31mError\033[0m: Journal insert test: journal size incorrect"
            });
        }

        return "\033[32mPassed\033[0m: Journal insert test:"; // Return passing message
    }

    // Tests journal fetch function
    expected<string, error> test_journal_fetch() {
        using namespace journal;
        using namespace matchit;
        
        int result{0};
        
        printf("--Testing journal fetch\n");
        
        Journal j{"test"}; // Create new journal object
        
        // Create a page to add to the journal
        Page page = Page::builder()
            ->title("Konbanwa!")
            ->build();
        int key = page.key(); // Store key of p
        
        j.insert(page); // Insert page into the journal
        
        // Attempt to fetch page with key, and match the result
        match(j.fetch(key)) (
            pattern | none = [&] { // If p is none, set result to 1
                result = 1;
            }
        );
        // If result is 1, return tuple with error value and message
        if(result == 1) {
            return unexpected( error {
                    result,
                    "\033[31mError\033[0m: Journal fetch test: fetch returned none when page exists"
            });
        }
        
        // Attempt to fetch page with key + 1, and match the result
        Id<Page*> p;
        match(j.fetch(key + 1)) (
            pattern | some(p) = [&] { // If p is some(Page*), set result to 1
                result = 1;
            }
        );
        // If result is 1, return tuple with error value and message
        if(result == 1) {
            return unexpected( error {
                result,
                "\033[31mError\033[0m: Journal fetch test: fetch returned a Page* when page does not exist"
            });
        }
        
        
        return "\033[32mPassed:\033[0m Journal fetch test:";
    }

    // Tests journal remove function
    expected<string, error> test_journal_remove() {
        using namespace journal;
        using namespace matchit;

        int result{0};

        printf("--Testing journal remove\n");

        Journal j{"test"}; // Create new journal object

        // Create some pages to add to the journal
        Page p1 = Page::builder()
            ->title("Dobar dan!")
            ->build();
        int key1 = p1.key(); // Store key of p1
        Page p2 = Page::builder()
            ->title("Miremenjes!")
            ->build();
        int key2 = p2.key(); // Store key of p2
        Page p3 = Page::builder()
            ->title("Gamarjoba!")
            ->build();
        int key3 = p3.key(); // Store key of p3

        // Insert pages into the journal
        j.insert(p1);
        j.insert(p2);
        j.insert(p3);

        j.remove(key1); // Remove page with key1
        j.remove(key2); // Remove page with key2
        j.remove(key3); // Remove page with key3
        
        vector<std::optional<Page*>> pages = {
            j.fetch(key1), // Try to fetch page with key1
            j.fetch(key2), // Try to fetch page with key2
            j.fetch(key3)  // Try to fetch page with key3
        };

        for(auto const& page: pages) { // Iterate through pages
            Id<Page*> p; 
            match(page) ( // Match page
                pattern | some(p) = [&] { // If page is some, set result to 1
                    result = 1;
                    printf("Page with key %u found\n", p.value()->key());
                }
            );
        }

        // If any result is 1, return tuple with error value and message
        if(result) {
            return unexpected(error {
                1,
                "\033[31mError\033[0m: Journal remove test: removed page still found"
            });
        }

        return "\033[32mPassed:\033[0m Journal remove test:"; // Returned passing message
    }

    // Tests journal sort function
    expected<string, error> test_journal_sort() {
        using namespace journal;
        using namespace matchit;
        
        printf("--Testing journal sort\n");
        
        int result{0};
        
        Journal j{"test"}; // Create new journal object
        
        // Create some pages to add to the journal
        Page p1 = Page::builder()
                ->title("Dobar dan!")
                ->build();
        Page p2 = Page::builder()
                ->title("Miremenjes!")
                ->build();
        Page p3 = Page::builder()
                ->title("Gamarjoba!")
                ->build();
        
        // Insert pages into the journal
        j.insert(p1);
        j.insert(p2);
        j.insert(p3);
        
        // Sort array based on first letter of title, will be sorted in ascending order,
        // returning true if the left page name has a higher value first char then the right,
        j.sort([](Page* left, Page* right) -> bool {
           if (left->title().at(0) > right->title().at(0)) return true;
           return false;
        });
        
        // Order should now be [p1, p3, p2]
        vector<Page> expected_order = {p1, p3, p2};
        // If any page is not in the correct spot, set result to 1
        auto pages = j.pages();
        if((*pages) != expected_order) result = 1;
        
        // If any result is 1, return tuple with error value and message
        if(result) {
            return unexpected(error {
                    1,
                    "\033[31mError\033[0m: Journal sort test: pages in incorrect order"
            });
        }
        
        return "\033[32mPassed:\033[0m Journal sort test:";
    }
}
