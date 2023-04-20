#include <cstdio>
#include <string.h>
#include "../includes/menu.h"
#include "../includes/journal.h"
#include "../test/test.h"

int main(int argc, char* argv[]) {
    using namespace app;
    using namespace journal;
    using namespace std;

/* Program testing */

    // If program started with --test argument, runs tests instead of program
    if(argc > 1 && !strcmp(argv[1], "--test")) {
        printf("Testing...\n");
        auto test_result = Test::test(); // Runs tests and returns a vector<tuple<int, string>>
                                         // each element corresponds to a the result
                                         // of a single test

        int result{0}; // return value for main
        
        // Print out the results of each test
        for(tuple<int, string> test: *test_result) {
            int value; string message;
            tie(value, message) = test; // Destructure tuple into individual variables

            result = result | value; // Bitwise or the result and the value of the current test

            // Prints out current tests message and value
            printf("%s, test returned %d\n", message.c_str(), value);
        }

        return result; // Returns 1 if any test has failed
    }

    bool exit = false; // Bool to control main program loop
                       
    Journal journal; // Create new journal object
    // Create a page with a title and a body
    Page page = Page::builder()
        ->title("Dobar dan!")
        ->body("    Lorem ipsum dolor sit amet, officia excepteur ex fugiat reprehenderit\
enim labore culpa sint ad nisi Lorem pariatur mollit ex esse exercitation amet.\
Nisi anim cupidatat excepteur officia. Reprehenderit nostrud nostrud ipsum Lorem\
est aliquip amet voluptate voluptate dolor minim nulla est proident. Nostrud officia\
pariatur ut officia. Sit irure elit esse ea nulla sunt ex occaecat reprehenderit\
commodo officia dolor Lorem duis laboris cupidatat officia voluptate. Culpa proident\
adipisicing id nulla nisi laboris ex in Lorem sunt duis officia eiusmod. Aliqua\
reprehenderit commodo ex non excepteur duis sunt velit enim. Voluptate laboris\
sint cupidatat ullamco ut ea consectetur et est culpa et culpa duis.")
        ->build();
    // Insert page into the journal
    journal.insert(page);

    // Display lambda for main menu
    auto main_display = [&](Menu* menu){
        std::system("clear"); // Clear terminal

        printf("%s", menu->title().c_str()); // Print main menu title
        // For each sub menu, print their title
        menu->for_each([](Menu sub){
                std::printf("%s", sub.title().c_str());
        });
        
        printf("Journal entries:\n");
        journal.display(); // Displays all pages in the journal
        // Set exit to true to end main loop
        exit = true;
    };

/* End of program testing */

    // Create new menu, main_menu, and give it a title and the display lambda with the key "main".
    // "main" function is automatically called when object is called as a function ie: main_menu();
    Menu main_menu = Menu::builder()
        ->title("\t\t\t -- Main Menu --\n")
        ->fn("main", main_display)
        ->build(); 
    
    while(!exit) main_menu(); // Run main menu until exit is set true    

    return 0;
}
