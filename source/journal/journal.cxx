#include "../../include/journal/journal.hpp"

namespace ReView::journal {
    
    // Journal insert function
    void Journal::insert(const Page& page) {
        this->_pages.push_back(page);
        this->_size++;
    }
    
    // Journal fetch function
    optional<Page*> Journal::fetch(const int& key) {
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
    void Journal::remove(const int& key) {
        if(this->size() == 0) return;

        for(int i = 0; i < this->_pages.size(); i++) {
            // If key is found, remove page
            if(this->_pages[i].key() == key) {
                this->_pages.erase(this->_pages.begin() + i);
                this->_size--;
                return;
            }
        }
    }
    
    void swap(Page* left, Page* right) {
        Page temp = *left;
        *left = *right;
        *right = temp;
    }
    
    int Journal::partition(int lo, int hi, const function<bool(Page*, Page*)>& predicate) {
        Page* pivot = &this->_pages.at(hi);
        int i = lo - 1;
        
        for(int j = lo; j <= hi; j++) {
            if(!predicate(&this->_pages.at(j), pivot)) {
                swap(&this->_pages.at(j), pivot);
            }
        }
        
        swap(&this->_pages.at(i + 1), pivot);
        return i + 1;
    }
    
    void Journal::quicksort(int lo, int hi, const function<bool(Page*, Page*)>& predicate) {
        if(lo < hi) {
            int pivot = partition(lo, hi, predicate);
            quicksort(lo, pivot - 1, predicate);
            quicksort(pivot + 1, hi, predicate);
        }
    }
    
    void Journal::sort(const function<bool(Page*, Page*)>& predicate) {
        if(this->_size == 0) return;
        
        quicksort(0, this->_size - 1, predicate);
    }
    
    // Journal display function
    void Journal::display() {
        fmt::print("Journal entries:\n\n");
        if(this->_size == 0) {
            fmt::print("Nothing to display, no pages in journal.\n");
        }
        // Iterate through list and display each page
        for(Page &page: this->_pages) {
            page.display();
        }
    }
}

