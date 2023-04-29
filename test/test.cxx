#include <cstring>

#include "journal_test.hpp"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace matchit;
    using namespace jcli;
/* ---- Testing -------------------------------------------------------------- */
    
    // If program started with --journal argument, run journal test
    if(argc > 1 && !strcmp(argv[1], "--journal")) {
        auto tests = journal::test::tests(); // Returns a vector of test function pointers

        unsigned test_count = tests->size(); // Count of tests to be run
        int passed_count{0}; // Count of tests which passed

        system("clear");
        fmt::print("Running {} Tests:\n", test_count);

        int return_val{0}; // return value for main
        for (auto &test : *tests) {
            using error = tuple<int, string>; // Error type alias

            expected<string, error> test_result = test(); // Run test and store result in expected
            match(test_result.has_value()) (
                // If test_result is an error, print out the error message
                pattern | false = [&] {
                    int value; string message;          // Variables to store tuple values
                    tie(value, message) = test_result.error(); // Destructure tuple into individual variables

                    return_val = return_val | value; // Bitwise or the result and the value of the current test

                    fmt::print("{}, returned {}\n", message, value); // Print out fail message
                },
                // If test_result has a value, print out the value and increment passed_count
                pattern | true = [&] {
                    fmt::print("{} returned {}\n", test_result.value(), 0); // Print out pass message
                    passed_count++;
                }
            );
        }

        fmt::print("Journal Tests complete: {}/{} Tests Passed\n", passed_count, test_count);
        return return_val; // Returns 0 if all tests passed, 
                           // otherwise returns bitwise or of all test return values
    }
}
