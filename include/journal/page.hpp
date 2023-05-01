#pragma once

#include <vector>
#include <random>
#include <string>

#define FMT_HEADER_ONLY
#include "fmt/format.h"

namespace jcli::journal {
    using namespace std;

    // Enum containing the months of the year
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
    
    // Enum containing the days of the week
    enum Weekday {
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };
    
    // Structure containing a weekday and a day
    struct Day {
        Weekday weekday{Weekday::MONDAY}; // Default weekday is Monday
        int day{1}; // Default day is 1

        Day() = default; // Default constructor
        Day(Weekday w, int d): weekday(w), day(d) {} // Constructor taking a weekday and a day
    };

    // Structure containing a month, a day, and a year
    struct Date {
        Month month() const { return this->_month; }
        Day day() const { return this->_day; }
        int year() const { return this->_year; }
        
        Date() = default; // Default constructor
        Date(Month m, Day d, int y): _month(m), _day(d), _year(y) {} // Constructor taking a month, a day, and a year
    private:
        Month _month{Month::JANUARY}; // Default month is January
        Day _day{Weekday::MONDAY, 1}; // Default day is Monday, 1
        int _year{1900}; // Default year is 1900
    };


    struct PageBuilder;
    // Structure containing a key, a title, a body, a date, and a vector of tags
    struct Page {
        Page() = default; // Default constructor
        explicit Page(PageBuilder*); // Constructor taking a PageBuilder*
        Page(const string &title, const string &body, const Date &date, const vector<string> &tags); // Constructor taking a title, a body, a date, and a vector of tags

        void display() const; // Displays the page
        int key() const { return this->_key; }
        string title() const { return this->_title; }
        string body() const { return this->_body; }
        Date date() const { return this->_date; }
        vector<string>* tags() const { return const_cast<vector<string>*>(&this->_tags); }
        
        bool operator ==(const Page&) const;
        bool operator !=(const Page&) const;

        static PageBuilder* builder(); // Returns a PageBuilder*, used to build a new page

    private:
        int _key{0};  // Key used to identify the page
        string _title; // Title of the page
        string _body; // Body/Content of the page
        Date _date; // Date of the page
        vector<string> _tags; // Tags of the page, to aid searching
    };

    // Structure used to build a page
    struct PageBuilder {
        PageBuilder* title(const string&); // Sets the title of the page
        PageBuilder* body(const string&); // Sets the body of the page
        PageBuilder* date(const Date&); // Sets the date of the page
        PageBuilder* tag(const string&); // Adds a tag to the page
        PageBuilder* tag(string&&); // Adds a tag to the page
        Page build(); // Builds the page and returns it

        int key() const { return this->_key; }
        void set_key(int key) { this->_key = key; }
        string title() const { return this->_title; }
        string body() const { return this->_body; }
        Date date() const { return this->_date; }
        vector<string>* tags() { return &this->_tags; }

    private:
        int _key{0}; // Key used to identify the page
        string _title; // Title of the page
        string _body; // Body/Content of the page
        Date _date; // Date of the page
        vector<string> _tags; // Tags of the page, to aid searching
    };
}
