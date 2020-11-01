#include "hallo_world_task.hpp"

#define NUMBER_OF_TEST_THREADS      2

extern "C" void app_main() {
    hello_world_task tasks[NUMBER_OF_TEST_THREADS];

    for(int i = 0; i < NUMBER_OF_TEST_THREADS; i++) {
        tasks[i].create( i % 2 );
    }

    mn_panic();
}