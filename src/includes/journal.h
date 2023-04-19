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
            Page page;
            Node* next{NULL};
            Node* prev{NULL};

            Node() {
                Page* temp = new Page;
                page = *temp;
                delete temp;
            }
            Node(Page p): page(p) {}
        };

        Journal() {}
        ~Journal() {}

        void display();
        void insert(Page page);
        void remove();
        void sort();
        bool check_date();
        Page* fetch();
        unsigned size() {return this->_size;}
        Node* head() {return this->_head;}
        Node* tail() {return this->_tail;}

    private: 
        Node* _head{NULL};
        Node* _tail{NULL};
        unsigned _size{0};
    };
}
