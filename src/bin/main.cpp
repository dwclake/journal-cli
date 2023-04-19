#include <cstdio>
#include "../includes/menu.h"
#include "../includes/journal.h"

int main() {
    using namespace app;
    using namespace journal;
    
    Journal journal;

    Page page = Page::builder()
        ->title("Hello world")
        ->body("Hows it going yall.\nIdk whats going on.")
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
