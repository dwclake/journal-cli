#pragma once

#include <matchit.h>

#include <cstdio>
#include <functional>
#include <optional>
#include <utility>
#include "page.h"

namespace journal {
    using namespace std;

    // Enum for sort type
    enum Sort {
        ALPHABETICAL,
        CHRONOLOGICAL,
    };
    
    // Enum for sort direction
    enum SortDir {
        ASCENDING,
        DESCENDING,
    };
    
    // Journal struct, a CDLL, each node containing a page
    struct Journal {
        Journal() = default; // Default constructor
        explicit Journal(string name): _name(std::move(name)) {} // Constructor taking the name of journal
        ~Journal() = default; // Destructor

        void display(); // Prints out every page in order
        void insert(const Page& page); // Inserts a page into the journal
        void remove(const int& key); // Removes page with matching key
        void sort(const function<bool(Page*, Page*)>& predicate); // Sorts based on supplied function
        vector<Page>* pages() const { return const_cast<vector<Page>*>(&this->_pages); } // Returns pointer to pages
        vector<Page>* mut_pages() { return &this->_pages; } // Returns copy of pages
        optional<Page*> fetch(const int& key); // Finds page with matching key
        string name() const { return this->_name; }
        unsigned size() const { return this->_size; }

        vector<Page>::iterator begin() { return this->_pages.begin(); } // Returns iterator to beginning of journal
        vector<Page>::iterator end() { return this->_pages.end(); } // Returns iterator to end of journal
    private:
        string _name; // Name of the journal
        vector<Page> _pages; 
        unsigned _size{0}; // Size of the journal
        
        int partition(int lo, int hi, const function<bool(Page * , Page * )>& predicate);
        void quicksort(int lo, int hi, const function<bool(Page * , Page * )>& predicate);
    };
}
