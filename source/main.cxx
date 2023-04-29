#include <cstring>
#include <iostream>

#include <matchit.h>

#include "../include/app/menu.hpp"
#include "../include/journal/journal.hpp"
#include "../include/utility/utility.hpp"

// Checks if response matches any of the args
template<class T>
bool check_input(T response, std::vector<T> &args) {
    for(T arg: args) { // For each arg in args, check if arg == response
        if(arg == response) return true;
    }

    return false;
}   

// Gets input from user, checks if input matches any of the args
// args must be of the same type as response, and one arg is required
template<class T, class... S>
void get_input(T &response, T arg, S... args) {
    std::vector<T> vec{arg, args...}; // Create vector from args
    do { // Do while response is not in vec
        std::cin >> response;

        if(!check_input(response, vec)) {
            fmt::print("Input not recognized, please try again\n> ");
        }
    } while(!check_input(response, vec));
}

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace jcli;
    using namespace matchit;

    bool exit = false; // Bool to control main program loop

    // Create new menu, create_journal, and give it a title
    app::Menu create_journal = app::Menu::builder()
        ->title("\033[33mC\033[0mreate Journal\n")
        ->build();

    // Create new menu, open_journal, and give it a title
    app::Menu open_journal = app::Menu::builder()
        ->title("\033[33mO\033[0mpen Journal\n") 
        ->build();

    // Display lambda for main menu
    auto main_display = [&](app::Menu* menu) -> void {
        system("clear"); // Clear terminal
        fmt::print("{}", menu->title()); // Print main menu title

        // For each sub menu, print their title
        menu->for_each([](const app::Menu& sub) -> void {
                fmt::print("{}", sub.title());
        });
        fmt::print("\n");  

        fmt::print("\033[33mE\033[0mxit\n");  
        
        // Call main menu input fn
        (*menu->fn("input"))(menu);
    };

    // Input lambda for main menu
    auto main_input = [&](app::Menu* menu) -> void {
        fmt::print("Select a option\n> ");

        // Get user input
        char response;
        get_input(response, 
            'c', 'o', 'e', 
            'C', 'O', 'E'
        );
        // Match response 
        match(response) (
            // If response is "create", call create_journal display fn
            pattern | 'c' = [&] {
            
            },
            // If response is "open", call open_journal display fn
            pattern | 'o' = [&] {
            
            },
            // If response is "exit", set exit to true
            pattern | 'e' = [&] {
                exit = true;
            }
        );
    };

    // Create new menu, main_menu, and give it a title and the display lambda with the key "main".
    // "main" function is automatically called when object is called as a function ie: main_menu();
    app::Menu main_menu = app::Menu::builder()
        ->title("\t\t\t -- Main Menu --\n")
        ->fn("main", main_display)
        ->fn("input", main_input)
        ->sub_menu("create", create_journal)
        ->sub_menu("open", open_journal)
        ->build(); 
    
    while(!exit) main_menu(); // Run main menu until exit is set true
    
    return 0;
}
