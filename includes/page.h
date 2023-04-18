#include <string>
#include <vector>

namespace page {
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

    enum Day {
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };

    struct Date {
        Month month;
        Day weekday;
        unsigned day;
        unsigned year;
    };

    struct page {
        string title;
        string body;
        Date date;
        vector<string> tags;
    };
}
