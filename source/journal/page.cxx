#include "../../include/journal/page.hpp"

namespace journal {
    // Static page function to start building new pages
    PageBuilder* Page::builder() {
        auto* page = new PageBuilder;

        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution;

        page->set_key(distribution(generator));
        return page;
    }

    // Adds a title to the page being built
    PageBuilder* PageBuilder::title(const string &title) {
        this->_title = title;
        return this;
    }

    // Adds a body to the page being built
    PageBuilder* PageBuilder::body(const string& body) {
        this->_body = body;
        return this;
    }

    // Adds a date to the page being built
    PageBuilder* PageBuilder::date(const Date& date) {
        this->_date = date;
        return this;
    }
    // Adds a tag to the page being built, can be called as many times as needed
    PageBuilder* PageBuilder::tag(const string& tag) {
        this->_tags.push_back(tag);
        return this;
    }
    
    // Adds a tag to the page being built, can be called as many times as needed
    PageBuilder* PageBuilder::tag(string&& tag) {
        this->_tags.push_back(std::move(tag));
        return this;
    }

    // Builds the page and returns it
    Page PageBuilder::build() {
        Page temp(this);
        delete this;
        return temp;
    }

    // Page constructor taking PageBuilder*
    Page::Page(PageBuilder* builder) {
        this->_key = builder->key();
        this->_title = builder->title();
        this->_body = builder->body();
        this->_date = builder->date();
        this->_tags = std::move(*builder->tags());
    }

    // Page display function
    void Page::display() const {
        // Convert weekday to string
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
        // Convert month to string
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
        // Print date
        printf("\t\t%s %s %d %d: ", 
                weekday.c_str(), 
                month.c_str(),
                this->date().day().day,
                this->date().year());
        // Print title
        printf("%s\n\n", this->title().c_str());
        // Print body
        printf("%s\n\n", this->body().c_str());
        // Print tags
        printf("tags: ");
        for(const string& tag: *this->tags()) {
            printf("[%s] ", tag.c_str());
        }
        printf("\n");
    }
    
    bool Page::operator ==(const Page& rhs) const {
        if(this->_key != rhs.key()) return false;
        return true;
    }
    
    bool Page::operator !=(const Page& rhs) const {
        if(*this == rhs) return false;
        return true;
    }
}
