#pragma once

#include <iostream>
#include <vector>

#include <matchit.h>
#include <fmt/format.h>

namespace jcli::input {
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
} // namespace jcli::input
#include "../../source/input/input.txx"