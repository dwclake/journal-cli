#include <cstdio>
#include <random>

namespace clist {
    template<typename T>
    struct clist {
        private: struct Node {
            T data;
            Node* next;
            Node* prev;

            Node(): next(NULL), prev(NULL) {}
            Node(T t): data(t), next(NULL), prev(NULL) {}

            
        }; 

    private: 
        Node* head{NULL};
        Node* tail{NULL};
        unsigned size;
    };
}
