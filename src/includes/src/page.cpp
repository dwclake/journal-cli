#include "../page.h"

namespace journal {
    PageBuilder* Page::builder() {
        return new PageBuilder;
    }

    PageBuilder* PageBuilder::title(string title) {
        this->_title = std::move(title);
        return this;
    }

    PageBuilder* PageBuilder::body(string body) {
        this->_body = std::move(body);
        return this;
    }

    PageBuilder* PageBuilder::date(Date date) {
        this->_date = std::move(date);
        return this;
    }

    PageBuilder* PageBuilder::tag(string tag) {
        this->_tags.push_back(std::move(tag));
        return this;
    }

    Page PageBuilder::build() {
        Page temp;
        temp = this;
        delete this;
        return temp;
    }

    Page::Page(PageBuilder* builder) {
        this->_title = builder->title();
        this->_body = builder->body();
        this->_date = builder->date();
        this->_tags = std::move(*builder->tags());
    }

    void Page::display() {
        printf("%s\n", this->title().c_str());
        printf("%s\n", this->body().c_str());
    }


}
