#include "../../include/app/menu.h"

namespace app {
    using namespace std;
    // Call operator overload for menu
    void Menu::operator()() {
        this->_fns["main"](this);
    }     
    
    // Static menu function to start building new menus
    MenuBuilder* Menu::builder() {
        return new MenuBuilder;
    }

    // Applies a function to each sub menu
    void Menu::for_each(function<void(Menu)> fn) {
        map<string, Menu>::iterator it;

        for(it = _sub_menus.begin(); it != _sub_menus.end(); it++) {
            fn(it->second);
        }
    }

    // Adds a title to the menu being built
    MenuBuilder* MenuBuilder::title(string title) {
        this->_title = title;
        return this;
    }

    // Adds a function to the menu being built, can be called as many times as needed
    MenuBuilder* MenuBuilder::fn(string name, function<void (Menu *)> fn) {
        this->_fns.insert({name, fn});
        return this;
    }

    // Adds a sub menu to the menu being built, can be called as many times as needed
    MenuBuilder* MenuBuilder::sub_menu(string name, Menu &menu) {
        this->_sub_menus.insert({name, menu});
        return this;
    }

    // Builds the menu and returns it
    Menu MenuBuilder::build() {
        Menu temp;
        temp = this;
        delete this;
        return temp;
    }

    // Menu constructor taking MenuBuilder*
    Menu::Menu(MenuBuilder* builder) {
        this->_title = builder->title();
        this->_fns = std::move(*builder->fns());
        this->_sub_menus = std::move(*builder->sub_menus());
    }
}
