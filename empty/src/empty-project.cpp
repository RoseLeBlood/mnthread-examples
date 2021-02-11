#include <miniThread.hpp>
#include <iostream>

extern "C" void app_main() {
    std::cout << "Thank you for use miniThread v. " << mnversion_t::instance().to_string() << std::endl;
    std::cout << "simple empty example" << std::endl;

    /* Code goes hier */

    mn_panic();
}