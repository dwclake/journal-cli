namespace jcli::input {
    using namespace std;

    // Struct for handling user input
    template<class T>
    bool InputHandler<T>::check_input() {
        for(T arg : this->_args) { // For each arg in args, check if arg == response
            if(arg == this->_response)
                return true;
        }

        return false;
    }

    // Gets user input
    template<class T>
    T InputHandler<T>::get_input() {
        do { // Do while response is not in args
            cin >> this->_response;

            if(!check_input()) {
                fmt::print("Input not recognized, please try again\n> ");
            }
        } while(!check_input());

        return this->_response;
    }

    // Calls get_input and returns it value
    template<class T>
    T InputHandler<T>::operator() () {
        return this->get_input();
    }    
} // namespace jcli::input