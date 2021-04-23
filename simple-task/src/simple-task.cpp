#include <stdio.h>
#include <iostream>
#include <miniThread.hpp>

using namespace mn;

#define NUMBER_OF_TEST_THREADS      2
#define _PROJECT_NAME 				"basic task example"

class hello_world_task : public basic_task {
public:
    hello_world_task();

    virtual void*  on_task() override;
};

hello_world_task::hello_world_task()
    : basic_task("HelloWorld", basic_task::PriorityNormal)  { }

void*  hello_world_task::on_task() {

    int id = get_id();
    int core = get_on_core();

    for(;;) {
        printf("[%d @ %d] Hello World!!\n", id, core );
    }

    return NULL;
}
MN_EXTERNC_BEGINN

void app_main() {
    MN_THREAD_VERSION_INFO(_PROJECT_NAME);

    hello_world_task tasks[NUMBER_OF_TEST_THREADS];

    for(int i = 0; i < NUMBER_OF_TEST_THREADS; i++) {
        tasks[i].start( i % 2 );
    }

    panic();
}

MN_EXTERNC_END
