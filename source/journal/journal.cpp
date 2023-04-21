#include "../../include/journal/journal.h"

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

    Page* Journal::fetch(unsigned key) {
        if(this->_size == 0) return NULL;

        Node* current = this->_head;
        do {
            if(current->page.key() == key) {
                return &current->page;
            }
            current = current->next;
        } while(current != this->_head);

        return NULL;
    }

    void Journal::remove(unsigned key) {
        if(this->size() == 0) return;

        Node* current = this->_head;

        if(this->size() == 1) {
            this->_head = NULL;
            this->_tail = NULL;
            this->_size = 0;

            delete current;
            return;
        }

        do {
            if(current->page.key() == key) break;

            current = current->next;
        } while(current != this->_head);
        
        // If current is tail or is head and matches key, adjust head/tail pointer
        // If current is head but doesn't match key, key not found in list
        if(current == this->_head && current->page.key() == key) {
            this->_head = current->next;
        } else if(current == this->_head) {
            printf("Page not found, cannot remove\n");
            return;
        } else if(current == this->_tail) {
            this->_tail = current->prev;
        }

        // Connect nodes before and after current to eachother
        current->next->prev = current->prev;
        current->prev->next = current->next;
        // Set current nodes 
        current->next = NULL;
        current->prev = NULL;

        this->_size--;

        delete current;
    }

    void Journal::sort(Sort type, SortDir dir) {

    }

    void Journal::display() {
        printf("Journal entries:\n");
        if(this->_size == 0) {
            printf("Nothing to display, no pages in journal.\n");
        }
        Node* current = this->_head;

        do {
            current->page.display();
            current = current->next;

        } while(current != this->_head);
    }
}

