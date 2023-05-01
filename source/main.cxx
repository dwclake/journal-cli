#include <cstring>
#include <iostream>

#include <matchit.h>

#include "../include/app/menu.hpp"
#include "../include/journal/journal.hpp"
#include "../include/input/input.hpp"
#include "../include/utility/utility.hpp"

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
    // Could also be build like this:
    // 
    // app::Menu open_journal{
    //     "\033[33mO\033[0mpen Journal\n",
    //     {},
    //     {}
    // };

    // Create new menu, main_menu, and give it a title and the display function with the key "main", and a input function.
    // "main" function is the default function called when the menu object is called.
    app::Menu main_menu = app::Menu::builder()
        ->title("\t\t\t -- Main Menu --\n")
        ->fn("main", [&](app::Menu* menu) -> void { // Main menu display fn
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
        })
        ->fn("input", [&](app::Menu* menu) -> void { // Main menu input fn
            fmt::print("Select a option\n> ");

            // Create input hander object with a vector of chars user input must match
            input::InputHandler<char> input({
                'o', 'c', 'e',
                'O', 'C', 'E'
            });
            // Get user input by calling input object
            char response = input();
            response = tolower(response); // Set response to lowercase

            // Match response 
            match(response) (    
                pattern | 'c' = [&] { // If response is "create", call create_journal display fn
            
                },
                pattern | 'o' = [&] { // If response is "open", call open_journal display fn
            
                },
                pattern | 'e' = [&] { // If response is "exit", set exit to true
                    exit = true;
                }
            );
        })
        ->sub_menu("create", create_journal)
        ->sub_menu("open", open_journal)
        ->build();  
    // Could also be build like this if you declared the lambda functions before hand as main_display and main_input:
    //
    // app::Menu main_menu{
    //    "\t\t\t -- Main Menu --\n",
    //    {
    //        {"main", main_display},
    //        {"input", main_input}
    //    },
    //    {
    //        {"create", create_journal},
    //        {"open", open_journal}
    //    }
    // };
    while(!exit) main_menu("main"); // Run main menu until exit is set true
    
    return 0;
}
