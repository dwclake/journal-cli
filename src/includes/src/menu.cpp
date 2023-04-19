#include "../menu.h"

namespace app {
    using namespace std;

    void Menu::operator()() {
        this->_fns["main"](this);
    }     
    
    MenuBuilder* Menu::builder() {
        return new MenuBuilder;
    }

    void Menu::for_each(function<void(Menu)> fn) {
        map<string, Menu>::iterator it;

        for(it = _sub_menus.begin(); it != _sub_menus.end(); it++) {
            fn(it->second);
        }
    }

    MenuBuilder* MenuBuilder::title(string title) {
        this->_title = std::move(title);
        return this;
    }

    MenuBuilder* MenuBuilder::fn(string name, function<void (Menu *)> fn) {
        this->_fns.insert({name, std::move(fn)});
        return this;
    }

    MenuBuilder* MenuBuilder::sub_menu(string name, Menu menu) {
        this->_sub_menus.insert({name, std::move(menu)});
        return this;
    }

    Menu MenuBuilder::build() {
        Menu temp;
        temp = this;
        delete this;
        return temp;
    }

    Menu::Menu(MenuBuilder* builder) {
        this->_title = builder->title();
        this->_fns = *builder->fns();
        this->_sub_menus = *builder->sub_menus();
    }
}
