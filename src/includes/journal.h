#include <cstdio>
#include <random>
#include "page.h"

namespace journal {

    enum Sort {
        ALPHABETICAL,
        CHRONILOGICAL,
    };

    enum SortDir {
        ASCENDING,
        DESCENDING,
    };

    struct Journal {
        private: struct Node {
            journal::Page page;
            Node* next{NULL};
            Node* prev{NULL};

            Node() {
                journal::Page* temp = new journal::Page;
                page = *temp;
                delete temp;
            }
            Node(journal::Page p): page(p) {}
        };

        Journal() {}
        ~Journal() {}

        void display();
        void insert();
        void remove();
        void sort();
        bool check_date();
        journal::Page* fetch();
        unsigned size() {return this->_size;}
        Node* head() {return this->_head;}
        Node* tail() {return this->_tail;}

    private: 
        Node* _head{NULL};
        Node* _tail{NULL};
        unsigned _size{0};
    };
}
