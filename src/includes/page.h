#include <string>
#include <vector>

namespace journal {
    using namespace std;

    enum Month {
        JANUARY,
        FEBRUARY,
        MARCH,
        APRIL, 
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    enum Weekday {
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };

    struct Day {
        Weekday weekday{Weekday::MONDAY};
        unsigned day{1};

        Day() {}
        Day(Weekday w, unsigned d): weekday(w), day(d) {}
    };

    struct Date {
        Month month() { return this->_month; }  
        Day weekday() { return this->_day; }
        unsigned year() { return this->_year; }
        
        Date() {}
        Date(Month m, Day d, unsigned y): _month(m), _day(d), _year(y) {}
    private:
        Month _month{Month::JANUARY};
        Day _day{Weekday::MONDAY, 1};
        unsigned _year{1900};
    };

    struct PageBuilder;
    struct Page {
        Page() {}
        Page(PageBuilder*);

        void display();
        string title() { return this->_title; }
        string body() { return this->_body; }
        Date date() { return this->_date; }
        vector<string>* tags() { return &this->_tags; }

        static PageBuilder* builder();

    private:
        string _title;
        string _body;
        Date _date;
        vector<string> _tags;
    };

    struct PageBuilder {
        PageBuilder* title(string);
        PageBuilder* body(string);
        PageBuilder* date(Date);
        PageBuilder* tag(string);
        Page build();

        string title() { return this->_title; }
        string body() { return this->_body; }
        Date date() { return this->_date; }
        vector<string>* tags() { return &this->_tags; }

    private:
        string _title;
        string _body;
        Date _date;
        vector<string> _tags;
    };
}
