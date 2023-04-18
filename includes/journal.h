#include <cstdio>
#include <random>

namespace clist {
    template<typename T>
    struct Journal {
        private: struct Node {
            T data;
            Node* next{NULL};
            Node* prev{NULL};

            Node() {
                T* temp = new T;
                data = *temp;
                delete temp;
            }
            Node(T t): data(t) {}
        };

        Journal() {}
        ~Journal() {}

        void display();
        void insert();
        void remove();
        void sort();
        bool check_date();
        T* fetch();
        unsigned size() {return this->_size;}
        Node* head() {return this->_head;}
        Node* tail() {return this->_tail;}

    private: 
        Node* _head{NULL};
        Node* _tail{NULL};
        unsigned _size;
    };
}
