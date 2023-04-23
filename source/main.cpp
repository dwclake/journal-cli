#include <cstring>

#include "../include/app/menu.h"
#include "../include/journal/journal.h"
#include "../test/test.h"

int main(int argc, char* argv[]) {

/* ---- Program testing -------------------------------------------------------------- */

    // If program started with --test argument, runs tests instead of program
    if(argc > 1 && !std::strcmp(argv[1], "--test")) {
        auto tests = Test::tests(); // Returns a vector of test function pointers

        unsigned test_count = tests->size(); // Count of tests to be run
        unsigned passed_count{0}; // Count of tests which passed
        
        std::system("clear");
        std::printf("Running %d Tests:\n", test_count);
        
        int result{0}; // return value for main
        for(auto &test: *tests) {
            try {
                std::string message = test(); // Run test and store message
                std::printf("%s returned %d\n", message.c_str(), 0); // Print out pass message
                
                passed_count++;
            } catch (std::tuple<unsigned, std::string> &e) {
                int value; std::string message; // Variables to store tuple values
                std::tie(value, message) = e; // Destructure tuple into individual variables
                
                result = result | value; // Bitwise or the result and the value of the current test
                
                std::printf("%s, returned %d\n", message.c_str(), value); // Print out fail message
            }
        }
        std::printf("Tests complete: %d/%d Tests Passed\n", passed_count, test_count);
        return result; // Returns 0 if all tests passed, 
                       // otherwise returns bitwise or of all test return values
    }

/* ---- End of program testing --------------------------------------------------------- */

    bool exit = false; // Bool to control main program loop
    
    // Display lambda for main menu
    auto main_display = [&](app::Menu* menu) -> void {
        std::system("clear"); // Clear terminal
        std::printf("%s", menu->title().c_str()); // Print main menu title

        // For each sub menu, print their title
        menu->for_each([](const app::Menu& sub) -> void {
                std::printf("%s", sub.title().c_str());
        });

        exit = true; // Exit main loop
    };
    // Create new menu, main_menu, and give it a title and the display lambda with the key "main".
    // "main" function is automatically called when object is called as a function ie: main_menu();
    app::Menu main_menu = app::Menu::builder()
        ->title("\t\t\t -- Main Menu --\n")
        ->fn("main", main_display)
        ->build(); 
    
    while(!exit) main_menu(); // Run main menu until exit is set true
    
    return 0;
}
