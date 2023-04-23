#pragma once

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
    
    // private Node struct, containing prev and next pointers and a page
    private: struct Node {
            Page page; // Page object
            Node* next{nullptr}; // Next node in the journal
            Node* prev{nullptr}; // Previous node in the journal

            Node() = default; // Default constructor
            explicit Node(Page  p): page(std::move(p)) {} // Constructor taking a page
        };
    public:
        Journal() = default; // Default constructor
        explicit Journal(string name): _name(std::move(name)) {} // Constructor taking the name of journal
        ~Journal() = default; // Destructor

        void display(); // Prints out every page in order
        void insert(const Page& page); // Inserts a page into the journal
        void insert(Page&& page); // Inserts a page into the journal
        void edit(const unsigned& key); // Edits a page with matching key
        void remove(const unsigned& key); // Removes page with matching key
        void sort(const Sort& type, const SortDir& dir); // Sorts based on enums from above
        void sort(const function<bool(Page*, Page*)>& predicate); // Sorts based on supplied function
        optional<Page*> fetch(const unsigned& key); // Finds page with matching key
        string name() const { return this->_name; }
        unsigned size() const { return this->_size; }
        Node* head() { return this->_head; }
        Node* tail() { return this->_tail; }
    private:
        string _name; // Name of the journal
        Node* _head{nullptr}; // First node in the journal
        Node* _tail{nullptr}; // Last node in the journal
        unsigned _size{0}; // Size of the journal
    };
}
