#pragma once

#include <vector>
#include <functional>
#include <string>

namespace menu {

    struct MenuBuilder;
    struct Menu {
        Menu() {}
        Menu(MenuBuilder*);

        void operator() ();

        std::string title() { return this->m_title; }
        std::vector<Menu>* sub_menus() { return &this->m_sub_menus; }
        Menu* get_sub(int idx) { return &this->m_sub_menus[idx]; }
        std::function<void(Menu*)>* fn() { return &this->m_fn; }

        void for_each(std::function<void(Menu)> fn);

        private:
        std::string m_title;
        std::vector<Menu> m_sub_menus;
        std::function<void(Menu*)> m_fn;
    };

    struct MenuBuilder {
        static MenuBuilder* create() { return new MenuBuilder; }
        MenuBuilder* title(std::string);
        MenuBuilder* fn(std::function<void(Menu*)>);
        MenuBuilder* sub_menu(Menu);
        Menu build();

        std::string get_title() { return this->m_title; }
        std::vector<Menu>* get_sub_menus() { return &this->m_sub_menus; }
        std::function<void(Menu*)>* get_fn() { return &this->m_fn; }

        private:
        std::string m_title{""};
        std::vector<Menu> m_sub_menus;
        std::function<void(Menu*)> m_fn{[](Menu*){}};
    };

}
