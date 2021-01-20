#ifndef _MINITHREAD_EXAMPLE_BASIC_HALLO_WORLD_TASK_
#define _MINITHREAD_EXAMPLE_BASIC_HALLO_WORLD_TASK_

#include <miniThread.hpp>

#define NUMBER_OF_TEST_THREADS      2

class hello_world_task : public basic_task { 
public:
    hello_world_task();

    virtual void*  on_task() override;
};

#endif