#include "../../include/journal/page.h"
#include <random>

namespace journal {
    PageBuilder* Page::builder() {
        PageBuilder* page = new PageBuilder;
        
        default_random_engine generator;
        uniform_int_distribution<unsigned> distribution;

        page->set_key(distribution(generator));
        return page;
    }

    PageBuilder* PageBuilder::title(string title) {
        this->_title = std::move(title);
        return this;
    }

    PageBuilder* PageBuilder::body(string body) {
        this->_body = std::move(body);
        return this;
    }

    PageBuilder* PageBuilder::date(Date &date) {
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
        this->_key = builder->key();
        this->_title = builder->title();
        this->_body = builder->body();
        this->_date = builder->date();
        this->_tags = std::move(*builder->tags());
    }

    void Page::display() {

        string weekday;
        switch(this->date().day().weekday) {
            case MONDAY: weekday = "Mon"; break;
            case TUESDAY: weekday = "Tue"; break;
            case WEDNESDAY: weekday = "Wed"; break;
            case THURSDAY: weekday = "Thu"; break;
            case FRIDAY: weekday = "Fri"; break;
            case SATURDAY: weekday = "Sat"; break;
            case SUNDAY: weekday = "Sun"; break;
        }

        string month;
        switch(this->date().month()) {
            case JANUARY: month = "Jan"; break;
            case FEBRUARY: month = "Feb"; break;
            case MARCH: month = "Mar"; break;
            case APRIL: month = "Apr"; break;
            case MAY: month = "May"; break;
            case JUNE: month = "Jun"; break;
            case JULY: month = "Jul"; break;
            case AUGUST: month = "Aug"; break;
            case SEPTEMBER: month = "Sep"; break;
            case OCTOBER: month = "Oct"; break;
            case NOVEMBER: month = "Nov"; break;
            case DECEMBER: month = "Dec"; break;
        }

        printf("\t\t%s %s %d %d: ", 
                weekday.c_str(), 
                month.c_str(),
                this->date().day().day,
                this->date().year());
        printf("%s\n\n", this->title().c_str());

        printf("%s\n\n", this->body().c_str());
        printf("tags: ");
        for(string tag: *this->tags()) {
            printf("[%s] ", tag.c_str());
        }
        printf("\n");
    }
}
