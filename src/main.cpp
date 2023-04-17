#include <cstdio>
#include <cstdlib>

#include "menu/menu.h"

int main() {
    using namespace menu;

    bool exit = false;
    auto fn = [&](Menu* menu){
        std::system("clear");

        printf("%s", menu->title().c_str());

        menu->for_each([](Menu sub){
                std::printf("%s", sub.title().c_str());
                });

        exit = true;
    };

    Menu main_menu = MenuBuilder::create()
        ->title(" -- Main Menu --\n")
        ->fn(fn)
        ->build();

    while(!exit) main_menu();    

    return 0;
}
