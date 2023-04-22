#include <cstdio>
#include <string.h>
#include <tuple>
#include "../include/menu/menu.h"
#include "../include/journal/journal.h"
#include "../test/test.h"

int main(int argc, char* argv[]) {
    using namespace app;
    using namespace journal;
    using namespace std;

/* ---- Program testing -------------------------------------------------------------- */

    // If program started with --test argument, runs tests instead of program
    if(argc > 1 && !strcmp(argv[1], "--test")) {
        auto tests = Test::tests(); // Runs tests and returns a vector<tuple<int, string>>
                                         // each element corresponds to a the result
                                         // of a single test

        int test_count = tests->size(); // Count of tests to be run
        int passed_count{0}; // Count of tests which passed
    
        system("clear");
        printf("Running %d Tests:\n", test_count);

        int result{0}; // return value for main
        for(auto test: *tests) {
            try {
                string message = test();
                printf("%s, returned %d\n", message.c_str(), 0); // Print out pass message

                passed_count++;
            } catch (tuple<unsigned, string> e) {
                int value; string message; // Variables to store tuple values
                tie(value, message) = e; // Destructure tuple into individual variables
                                         
                result = result | value; // Bitwise or the result and the value of the current test

                printf("%s, returned %d\n", message.c_str(), value); // Print out fail message
            }
        }
        printf("Tests complete: %d/%d Tests Passed\n", passed_count, test_count);
        return result; // Returns 1 if any test has failed
    }

/* ---- End of program testing --------------------------------------------------------- */

    bool exit = false; // Bool to control main program loop
    
    // Display lambda for main menu
    auto main_display = [&](Menu* menu){
        std::system("clear"); // Clear terminal

        printf("%s", menu->title().c_str()); // Print main menu title

        // For each sub menu, print their title
        menu->for_each([](Menu sub){
                std::printf("%s", sub.title().c_str());
        });

        exit = true; // Exit main loop
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
