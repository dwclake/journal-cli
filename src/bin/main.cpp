#include <cstdio>
#include <string.h>
#include "../includes/menu.h"
#include "../includes/journal.h"
#include "../test/test.h"

int main(int argc, char* argv[]) {
    using namespace app;
    using namespace journal;
    
    if(strcmp(argv[0],  "--test")) {
        printf("Testing...\n");
        int test_result = Test::test();

        printf("Test returned %d\n", test_result);
        return test_result;
    }

    Journal journal;

    Page page = Page::builder()
        ->title("Hello world")
        ->body("Hows it going yall.\nIdk whats going on.\n")
        ->build();
    Page page2 = Page::builder()
        ->title("Dobar dan")
        ->body("Prijatelji\n")
        ->build();
    Page page3 = Page::builder()
        ->title("Miredita")
        ->build();

    journal.insert(page);
    journal.insert(page2);
    journal.insert(page3);

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
