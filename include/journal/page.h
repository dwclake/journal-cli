#pragma once

#include <string>
#include <vector>
#include <random>

namespace journal {
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
    
    // Sturcture containing a weekday and a day
    struct Day {
        Weekday weekday{Weekday::MONDAY}; // Default weekday is Monday
        unsigned day{1}; // Default day is 1

        Day() {} // Default constructor
        Day(Weekday w, unsigned d): weekday(w), day(d) {} // Constructor taking a weekday and a day
    };

    // Structure containing a month, a day, and a year
    struct Date {
        Month month() { return this->_month; }  
        Day day() { return this->_day; }
        unsigned year() { return this->_year; }
        
        Date() {} // Default constructor
        Date(Month m, Day d, unsigned y): _month(m), _day(d), _year(y) {} // Constructor taking a month, a day, and a year
    private:
        Month _month{Month::JANUARY}; // Default month is January
        Day _day{Weekday::MONDAY, 1}; // Default day is Monday, 1
        unsigned _year{1900}; // Default year is 1900
    };


    struct PageBuilder;
    // Structure containing a key, a title, a body, a date, and a vector of tags
    struct Page {
        Page() {} // Default constructor
        Page(PageBuilder*); // Constructor taking a PageBuilder*

        void display(); // Displays the page
        unsigned key() { return this->_key; }
        string title() { return this->_title; }
        string body() { return this->_body; }
        Date date() { return this->_date; }
        vector<string>* tags() { return &this->_tags; }

        static PageBuilder* builder(); // Returns a PageBuilder*, used to build a new page

    private:
        unsigned _key;  // Key used to identify the page
        string _title; // Title of the page
        string _body; // Body/Content of the page
        Date _date; // Date of the page
        vector<string> _tags; // Tags of the page, to aid searching
    };

    // Structure used to build a page
    struct PageBuilder {
        PageBuilder* title(string); // Sets the title of the page
        PageBuilder* body(string); // Sets the body of the page
        PageBuilder* date(Date&); // Sets the date of the page
        PageBuilder* tag(string); // Adds a tag to the page
        Page build(); // Builds the page and returns it

        unsigned key() { return this->_key; }
        void set_key(unsigned key) { this->_key = key; }
        string title() { return this->_title; }
        string body() { return this->_body; }
        Date date() { return this->_date; }
        vector<string>* tags() { return &this->_tags; }

    private:
        unsigned _key{0}; // Key used to identify the page
        string _title{""}; // Title of the page
        string _body{""}; // Body/Content of the page
        Date _date; // Date of the page
        vector<string> _tags; // Tags of the page, to aid searching
    };
}
