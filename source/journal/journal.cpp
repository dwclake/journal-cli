#include "../../include/journal/journal.h"

namespace journal {
    
    // Journal insert function
    void Journal::insert(const Page& page) {
        this->_pages.push_back(page);
        this->_size++;
    }
    
    // Journal insert function
    void Journal::insert(Page&& page) {
        this->_pages.push_back(std::move(page));
        this->_size++;
    }
    
    // Journal fetch function
    optional<Page*> Journal::fetch(const unsigned& key) {
        if(this->_size == 0) return nullopt;

        for(Page &page: this->_pages) {
            // If key is found, return pointer to page
            if(page.key() == key) {
                return &page;
            }
        }
        // If key is not found, return NULL
        return nullopt;
    }

    // Journal remove function
    void Journal::remove(const unsigned& key) {
        if(this->size() == 0) return;

        for(unsigned i = 0; i < this->_pages.size(); i++) {
            // If key is found, remove page
            if(this->_pages[i].key() == key) {
                this->_pages.erase(this->_pages.begin() + i);
                this->_size--;
                return;
            }
        }
    }

    void Journal::sort(const Sort& type, const SortDir& dir) {

    }

    void Journal::sort(const function<bool(Page*, Page*)>& predicate) {

    }
    
    void Journal::edit(const unsigned& key) {
    
    }

    // Journal display function
    void Journal::display() {
        printf("Journal entries:\n\n");
        if(this->_size == 0) {
            printf("Nothing to display, no pages in journal.\n");
        }
        // Iterate through list and display each page
        for(Page &page: this->_pages) {
            page.display();
        }
    }
}

