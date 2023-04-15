#include "../menu.h"

namespace menu {
    void Menu::operator()() {
        this->m_fn(this);
    }     

    void Menu::for_each(std::function<void(Menu)> fn) {
        for(Menu sub: m_sub_menus) {
            fn(sub);
        }
    }

    MenuBuilder* MenuBuilder::title(std::string title) {
        this->m_title = std::move(title);
        return this;
    }

    MenuBuilder* MenuBuilder::fn(std::function<void (Menu *)> fn) {
        this->m_fn = std::move(fn);
        return this;
    }

    MenuBuilder* MenuBuilder::sub_menu(Menu menu) {
        this->m_sub_menus.push_back(std::move(menu));
        return this;
    }

    Menu MenuBuilder::build() {
        Menu temp;
        temp = this;
        delete this;
        return temp;
    }

    Menu::Menu(MenuBuilder* builder) {
        this->m_title = builder->get_title();
        this->m_fn = *builder->get_fn();
        this->m_sub_menus = *builder->get_sub_menus();
    }
}
