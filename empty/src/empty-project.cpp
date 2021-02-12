#include <miniThread.hpp>
#include <iostream>

using namespace mn;

extern "C" void app_main() {
    std::cout << "Thank you for use miniThread v. " << version::instance().to_string() << std::endl;
    std::cout << "simple empty example" << std::endl;

    /* Code goes hier */

    panic();
}