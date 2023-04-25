#include <cstring>

#include "../include/app/menu.h"
#include "../include/journal/journal.h"
#include "../test/test.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace app;
    using namespace journal;
    using namespace matchit;
/* ---- Program testing -------------------------------------------------------------- */

    // If program started with --test argument, runs tests instead of program
    if(argc > 1 && !strcmp(argv[1], "--test")) {
        auto tests = Test::tests(); // Returns a vector of test function pointers

        unsigned test_count = tests->size(); // Count of tests to be run
        int passed_count{0}; // Count of tests which passed
        
        system("clear");
        printf("Running %d Tests:\n", test_count);
        
        int return_val{0}; // return value for main
        for (auto &test : *tests) {
            using error = tuple<int, string>; // Error type alias

            expected<string, error> test_result = test(); // Run test and store result in expected
            match(test_result.has_value()) (
                // If test_result is an error, print out the error message
                pattern | false = [&] {
                    int value; string message;          // Variables to store tuple values
                    tie(value, message) = test_result.error(); // Destructure tuple into individual variables

                    return_val = return_val | value; // Bitwise or the result and the value of the current test

                    printf("%s, returned %d\n", message.c_str(), value); // Print out fail message
                },
                // If test_result has a value, print out the value and increment passed_count
                pattern | true = [&] {
                    printf("%s returned %d\n", test_result.value().c_str(), 0); // Print out pass message
                    passed_count++;
                }
            );
        }
        
        printf("Tests complete: %d/%d Tests Passed\n", passed_count, test_count);
        return return_val; // Returns 0 if all tests passed, 
                       // otherwise returns bitwise or of all test return values
    }

/* ---- End of program testing --------------------------------------------------------- */

    bool exit = false; // Bool to control main program loop
    
    // Display lambda for main menu
    auto main_display = [&](Menu* menu) -> void {
        system("clear"); // Clear terminal
        printf("%s", menu->title().c_str()); // Print main menu title

        // For each sub menu, print their title
        menu->for_each([](const Menu& sub) -> void {
                printf("%s", sub.title().c_str());
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
