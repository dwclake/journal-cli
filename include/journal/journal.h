#pragma once

#include <cstdio>
#include <random>
#include <functional>
#include <optional>
#include "page.h"

namespace journal {
    using namespace std;

    // Enum for sort type
    enum Sort {
        ALPHABETICAL,
        CHRONILOGICAL,
    };
    
    // Enum for sort direction
    enum SortDir {
        ASCENDING,
        DESCENDING,
    };
    
    // Journal struct, a CDLL, each node containing a page
    struct Journal {
    
    // private Node struct, containing prev and next pointers and a page
    private: struct Node {
            Page page; // Page object
            Node* next{NULL}; // Next node in the journal
            Node* prev{NULL}; // Previous node in the journal

            Node() {} // Default constructor
            Node(Page p): page(p) {} // Constructor taking a page
        };
    public:
        Journal() {} // Default constructor
        Journal(string name): _name(name) {} // Constructor taking the name of journal
        ~Journal() {} // Destructor

        void display(); // Prints out every page in order
        void insert(Page page); // Inserts a page into the journal
        void edit(unsigned key); // Edits a page with matching key
        void remove(unsigned key); // Removes page with matching key
        void sort(Sort type, SortDir dir); // Sorts based on enums from above
        void sort(function<bool(Page*, Page*)> predicate); // Sorts based on supplied function
        optional<Page*> fetch(unsigned key); // Finds page with matching key
        string name() { return this->_name; }
        unsigned size() { return this->_size; }
        Node* head() { return this->_head; }
        Node* tail() { return this->_tail; }
    private:
        string _name{""}; // Name of the journal
        Node* _head{NULL}; // First node in the journal
        Node* _tail{NULL}; // Last node in the journal
        unsigned _size{0}; // Size of the journal
    };
}
