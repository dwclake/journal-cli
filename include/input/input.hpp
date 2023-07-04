#pragma once

#include <iostream>
#include <vector>

#include <matchit.h>
#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace ReView::input {
    using namespace std;

    // Struct for handling user input
    template<class T>
    struct InputHandler {
        InputHandler(const vector<T> &args) { _args = args; }

        T operator () (); // Calls get_input and returns it value
    private:
        vector<T> _args; // Vector of args that input must match
        T _response; // User input

        bool check_input(); // Checks if response is in args
        T get_input(); // Gets user input
    };
} // namespace ReView::input
#include "../../source/input/input.hpp"
