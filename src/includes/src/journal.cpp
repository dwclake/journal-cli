#include "../journal.h"

namespace journal {
    void Journal::insert(Page page) {
        if(this->_size == 0) {
            this->_head = new Node(page);
            this->_tail = this->_head;
            
            this->_head->next = this->_tail;
            this->_head->prev = this->_tail;

            this->_tail->next = this->_head;
            this->_tail->prev = this->_tail;

            this->_size++;
            return;
        }
                
        Node* temp = new Node(page);
        temp->prev = this->_tail;
        temp->next = this->_head;
        this->_tail->next = temp;

        this->_tail = temp;
        this->_size++;
    }
}
