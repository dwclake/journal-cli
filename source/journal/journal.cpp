#include "../../include/journal/journal.h"

namespace journal {
    
    // Journal insert function
    void Journal::insert(Page page) {
        // If journal is empty, create new node and set head/tail pointers to it
        if(this->_size == 0) {
            this->_head = new Node(page);
            this->_tail = this->_head;

            // Create circular list            
            this->_head->next = this->_tail;
            this->_head->prev = this->_tail;

            this->_tail->next = this->_head;
            this->_tail->prev = this->_tail;
            // Increment size and return
            this->_size++;
            return;
        }

        // If journal is not empty, create new node and set tail->next to it       
        Node* temp = new Node(page);
        temp->prev = this->_tail;
        temp->next = this->_head;
        this->_tail->next = temp;

        // Set new tail to temp
        this->_tail = temp;
        this->_size++;
    }

    // Journal fetch function
    optional<Page*> Journal::fetch(unsigned key) {
        if(this->_size == 0) return nullopt;

        // If journal is not empty, iterate through list until key is found
        Node* current = this->_head;
        do {
            // If key is found, return pointer to page
            if(current->page.key() == key) {
                return &current->page;
            }
            current = current->next;
        } while(current != this->_head);

        // If key is not found, return NULL
        return nullopt;
    }

    // Journal remove function
    void Journal::remove(unsigned key) {
        if(this->size() == 0) return;

        Node* current = this->_head;
        // If journal contains 1 element which matches the key, set head/tail to NULL and delete current
        if(this->size() == 1 && current->page.key() == key) {
            this->_head = nullptr;
            this->_tail = nullptr;
            this->_size = 0;

            delete current;
            return;
        }
        // If journal is not empty, iterate through list until key is found
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

        // Connect nodes before and after current to each other
        current->next->prev = current->prev;
        current->prev->next = current->next;
        // Decrement size and delete current
        this->_size--;

        // Create circular links
        this->_head->prev = this->_tail;
        this->_tail->next = this->_head;

        delete current;
    }

    void Journal::sort(Sort type, SortDir dir) {

    }

    void Journal::sort(function<bool(Page*, Page*)> predicate) {

    }

    // Journal display function
    void Journal::display() {
        printf("Journal entries:\n\n");
        if(this->_size == 0) {
            printf("Nothing to display, no pages in journal.\n");
        }
        Node* current = this->_head;
        // Iterate through list and display each page
        do {
            current->page.display();
            current = current->next;

        } while(current != this->_head);
    }
}

