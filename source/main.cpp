#include <cstdio>
#include <string.h>
#include "../include/menu/menu.h"
#include "../include/journal/journal.h"
#include "../test/test.h"

int main(int argc, char* argv[]) {
    using namespace app;
    using namespace journal;
    using namespace std;

/* #### Program testing ############################################################## */

    // If program started with --test argument, runs tests instead of program
    if(argc > 1 && !strcmp(argv[1], "--test")) {
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
            printf("%s returned %d\n", message.c_str(), value);
        }
        return result; // Returns 1 if any test has failed
    }

/* #### End of program testing ####################################################### */


    bool exit = false; // Bool to control main program loop
    
    // Display lambda for main menu
    auto main_display = [&](Menu* menu){
        std::system("clear"); // Clear terminal

        printf("%s", menu->title().c_str()); // Print main menu title
        // For each sub menu, print their title
        menu->for_each([](Menu sub){
                std::printf("%s", sub.title().c_str());
        });

        // Set exit to true to end main loop
        exit = true;
    };

    // Create new menu, main_menu, and give it a title and the display lambda with the key "main".
    // "main" function is automatically called when object is called as a function ie: main_menu();
    Menu main_menu = Menu::builder()
        ->title("\t\t\t -- Main Menu --\n")
        ->fn("main", main_display)
        ->build(); 
    
    while(!exit) main_menu(); // Run main menu until exit is set true    

    return 0;
}
