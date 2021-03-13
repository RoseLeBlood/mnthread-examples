#include <miniThread.hpp>

using namespace mn;

#define TEST_ELEMENTS 10




struct mempool_tester {
    using mempool_t = mn::memory::basic_mempool_t<int, TEST_ELEMENTS>;

    mempool_tester() {
        __mempool.create(portMAX_DELAY);
    }
    void test(){
        while(true) {
            test_allocate();
            test_free();

            basic_task::sleep(1);
        }
    }
    void test_allocate( ) {
        std::string text = "";
        std::cout << "allocated test" << std::endl << std::endl;

        for(int i= 0; i < TEST_ELEMENTS + 1; i++) {
            test_array[i] = (int*)__mempool.allocate(true, 200);

            text = ( (test_array[i] == NULL) ? " empty" : " ok" );
            std::cout << i << text << std::endl;
        }
    }
    void test_free() {
        std::string text = "";
        std::cout << "Free test " << std::endl << std::endl;
        
        for(int i= 0; i < TEST_ELEMENTS + 1; i++) {
            text = __mempool.free(test_array[i]) ? " free" : " not free";
            std::cout << i << text << std::endl;
        }
    }

    mempool_t __mempool;
    int* test_array[TEST_ELEMENTS + 1];
};


extern "C" void app_main() {
    std::cout << "Thank you for use miniThread v. " << mn::version::instance().to_string() << std::endl;
    std::cout << "simple __mempool test" << std::endl;

    mempool_tester tester;
    tester.test();
    
}

