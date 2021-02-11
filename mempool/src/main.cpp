#include <miniThread.hpp>

#define TEST_ELEMENTS 10

struct mempool_test_buffer {
    int used;
};

int* test_array[TEST_ELEMENTS + 1];

void mempool_test_allocate(basic_mempool_t *mempool ) {
    std::string text = "";
    std::cout << "allocated test" << std::endl << std::endl;

    for(int i= 0; i < TEST_ELEMENTS + 1; i++) {
        test_array[i] = (int*)mempool->allocate(200);

        text = ( (test_array[i] == NULL) ? " empty" : " ok" );
        std::cout << i << text << std::endl;
    }
}
void mempool_test_free(basic_mempool_t *mempool) {
    std::string text = "";
    std::cout << "Free test " << std::endl << std::endl;

    for(int i= 0; i < TEST_ELEMENTS + 1; i++) {
        text = mempool->free(test_array[i], 200) ? " free" : " not free";
        std::cout << i << text << std::endl;
    }
}

extern "C" void app_main() {
    std::cout << "Thank you for use miniThread v. " << mnversion_t::instance().to_string() << std::endl;
    std::cout << "simple mempool test" << std::endl;

    basic_mempool_t *mempool = new basic_mempool_t(sizeof(mempool_test_buffer), TEST_ELEMENTS);
    err_cheak(test->create(portMAX_DELAY), NO_ERROR);

    while(true) {
        mempool_test_allocate(mempool):
        mempool_test_free(mempool);

        basic_task::sleep(1);
    }
}

void err_cheak(int error, int OK) {
    switch(error) {
        case OK: return;
    };
    mn_panic();
}