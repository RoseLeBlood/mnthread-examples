#include "hallo_world_task.hpp"

hello_world_task::hello_world_task()
    : basic_task("HelloWorld", 1)  { }

void*  hello_world_task::on_task() {
    basic_thread::on_task();

    int id = get_id();
    int core = get_on_core();

    for(;;) {
        printf("[%d @ %d] Hello World!!\n", id, core );
    }

    return NULL;
}