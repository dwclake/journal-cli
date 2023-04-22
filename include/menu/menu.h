#pragma once

#include <functional>
#include <string>
#include <map>

namespace app {
    using namespace std;

    struct MenuBuilder;
    // Menu structure containing a title, a map of sub menus, and a map of functions
    struct Menu {
        Menu() {} // Default constructor
        Menu(MenuBuilder*); // Constructor taking a MenuBuilder

        void operator() (); // Overloaded operator() to run the menu

        static MenuBuilder* builder(); // Returns a new MenuBuilder*, used to build a Menu
        string title() { return this->_title; } 
        map<string, Menu>* sub_menus() { return &this->_sub_menus; }
        Menu* sub(string name) { return &this->_sub_menus[name]; }
        function<void(Menu*)>* fn(string name) { return &this->_fns[name]; }

        void for_each(function<void(Menu)> fn); // Runs a function for each sub menu

    private:
        string _title; // Title of the menu
        map<string, Menu> _sub_menus; // Map of sub menus
        map<string, function<void(Menu*)>> _fns; // Map of functions
    };

    struct MenuBuilder {
        MenuBuilder* title(string); // Sets the title of the menu being built
        MenuBuilder* fn(string, function<void(Menu*)>); // Adds a function to the menu being built, can be called multiple times
        MenuBuilder* sub_menu(string, Menu&); // Adds a sub menu to the menu being built, can be called multiple times
        Menu build(); // Builds the menu and returns it

        string title() { return this->_title; }
        map<string, Menu>* sub_menus() { return &this->_sub_menus; }
        map<string, function<void(Menu*)>>* fns() { return &this->_fns; }

        private:
        string _title{""}; // Title of the menu being built
        map<std::string, Menu> _sub_menus; // Map of sub menus being built
        map<std::string, std::function<void(Menu*)>> _fns; // Map of functions being built
    };
}
