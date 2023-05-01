#pragma once

#include <functional>
#include <map>
#include <string>

namespace jcli::app {
    using namespace std;
    
    struct MenuBuilder;
    // Menu structure containing a title, a map of sub menus, and a map of functions
    struct Menu {
        Menu() = default; // Default constructor
        explicit Menu(MenuBuilder*); // Constructor taking a MenuBuilder
        // Constructor taking a title, a map of functions, and a map of sub menus
        Menu(const string &s, const map<string, function<void(Menu*)>> &fns, const map<string, Menu> &menus) 
            : _title(s), _fns{fns}, _sub_menus{menus} {}

        void operator() (const string& fn = "main"); // Overloaded operator() to run the menu

        static MenuBuilder* builder(); // Returns a new MenuBuilder*, used to build a Menu
        string title() const { return this->_title; }
        map<string, Menu>* sub_menus() { return &this->_sub_menus; }
        Menu* sub(const string& name) { return &this->_sub_menus[name]; }
        function<void(Menu*)>* fn(const string& name) { return &this->_fns[name]; }

        void for_each(const function<void(Menu)>& fn); // Runs a function for each sub menu

    private:
        string _title; // Title of the menu
        map<string, Menu> _sub_menus; // Map of sub menus
        map<string, function<void(Menu*)>> _fns; // Map of functions
    };

    struct MenuBuilder {
        MenuBuilder* title(const string&); // Sets the title of the menu being built
        MenuBuilder* fn(const string&, const function<void(Menu*)>&); // Adds a function to the menu being built, can be called multiple times
        MenuBuilder* fn(const string&, function<void(Menu*)>&&); // Adds a function to the menu being built, can be called multiple times
        MenuBuilder* sub_menu(const string&, const Menu&); // Adds a sub menu to the menu being built, can be called multiple times
        MenuBuilder* sub_menu(const string&, Menu&&); // Adds a sub menu to the menu being built, can be called multiple times
        Menu build(); // Builds the menu and returns it

        string title() { return this->_title; }
        map<string, Menu>* sub_menus() { return &this->_sub_menus; }
        map<string, function<void(Menu*)>>* fns() { return &this->_fns; }

        private:
        string _title; // Title of the menu being built
        map<string, Menu> _sub_menus; // Map of sub menus being built
        map<string, function<void(Menu*)>> _fns; // Map of functions being built
    };
}
