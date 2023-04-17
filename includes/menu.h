#pragma once

#include <functional>
#include <string>
#include <map>

namespace menu {
    using namespace std;

    struct MenuBuilder;
    struct Menu {
        Menu() {}
        Menu(MenuBuilder*);

        void operator() ();

        string title() { return this->_title; }
        map<string, Menu>* sub_menus() { return &this->_sub_menus; }
        Menu* get_sub(string name) { return &this->_sub_menus[name]; }
        function<void(Menu*)>* fn(string name) { return &this->_fns[name]; }

        void for_each(function<void(Menu)> fn);

        private:
        string _title;
        map<string, Menu> _sub_menus;
        map<string, function<void(Menu*)>> _fns;
    };

    struct MenuBuilder {
        static MenuBuilder* create() { return new MenuBuilder; }
        MenuBuilder* title(string);
        MenuBuilder* fn(string, function<void(Menu*)>);
        MenuBuilder* sub_menu(string, Menu);
        Menu build();

        string get_title() { return this->_title; }
        map<string, Menu>* get_sub_menus() { return &this->_sub_menus; }
        map<string, function<void(Menu*)>>* get_fns() { return &this->_fns; }

        private:
        string _title{""};
        map<std::string, Menu> _sub_menus;
        map<std::string, std::function<void(Menu*)>> _fns;
    };

}
