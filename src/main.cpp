#include <cstdio>
#include <cstdlib>

#include "menu/menu.h"

int main() {
    using namespace menu;

    bool exit = false;

    Menu main_menu = MenuBuilder::create()
        ->title(" -- Main Menu --\n")
        ->fn([&](Menu* menu){
            std::system("clear");

            printf("%s", menu->title().c_str());

            menu->for_each([](Menu sub){
                std::printf("%s", sub.title().c_str());
            });

            exit = true;
        })
        ->build();

    while(!exit) main_menu();    

    return 0;
}
