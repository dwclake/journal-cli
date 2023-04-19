#include <cstdio>
#include "../includes/menu.h"
#include "../includes/journal.h"

int main() {
    using namespace app;

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

    return 0;
}
