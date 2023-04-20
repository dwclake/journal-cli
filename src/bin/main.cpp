#include <cstdio>
#include <string.h>
#include "../includes/menu.h"
#include "../includes/journal.h"
#include "../test/test.h"

int main(int argc, char* argv[]) {
    using namespace app;
    using namespace journal;
    using namespace std;
   
    // If program started with --test argument, runs tests instead of program
    if(argc > 1 && !strcmp(argv[1], "--test")) {
        printf("Testing...\n");
        auto test_result = Test::test(); // Runs tests and returns a vector<tuple<int, string>>
                                         // each element corresponds to a the result
                                         // of a single test

        for(tuple<int, string> test: *test_result) { // Prints out the results of each test
            int value; string message;
            tie(value, message) = test;

            printf("%s, test returned %d\n", message.c_str(), value);
        }

        return get<0>((*test_result)[0]); // Currently returns main with the first test value
    }

    Journal journal;

    Page page = Page::builder()
        ->title("Hello world")
        ->body("Hows it going yall.\nIdk whats going on.\n")
        ->build();

    journal.insert(page);

    bool exit = false;
    auto main_display = [&](Menu* menu){
        std::system("clear");

        printf("%s", menu->title().c_str());

        menu->for_each([](Menu sub){
                std::printf("%s", sub.title().c_str());
        });

        exit = true;
    };

    Menu main_menu = Menu::builder()
        ->title(" -- Main Menu --\n")
        ->fn("main", main_display)
        ->build();
    
    while(!exit) main_menu();    

    journal.display();

    return 0;
}
