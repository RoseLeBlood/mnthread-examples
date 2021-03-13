/*
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [=         ]   5.0% (used 16392 bytes from 327680 bytes)
Flash: [====      ]  38.2% (used 400064 bytes from 1048576 bytes)
*/

#include <miniThread.hpp>
 
using namespace mn;

#include <stdio.h>
#include <iostream>

class mutexSimpleTestTask : public basic_task {
public:
    mutexSimpleTestTask(const char* name, mutex_t& lock, int sleepMS, int cpu)
        : basic_task(name), m_refLock(lock), m_sleepMS(sleepMS) { start(cpu); };

protected:
    virtual void  on_start() {  
        std::cout << "on_start@" << m_strName << std::endl;
    }
    virtual void  on_kill() {  
        std::cout << "on_kill@" << m_strName << std::endl;
    }
    virtual void* on_task() {
        while (true) {
            basic_task::usleep(m_sleepMS);
            test_lock_print();
        }
        return 0; // Never reach
    };
private:
    void test_lock_print() {
        automutx_t lock(m_refLock);
        for (int i = 0; i < 10; i++) {
            std::cout << "test_lock_print.on_task@ " << m_strName << " " << i << std::endl;
        }
    }

private:
    mutex_t& m_refLock;
    int m_sleepMS;
};

extern "C" void app_main() {
    std::cout << "Thank you for use miniThread v. " << version::instance().to_string() << std::endl;
    std::cout << "basic mutex example" << std::endl;

    mutex_t __pMutexToTest;

    mutexSimpleTestTask _test1("testltask1", __pMutexToTest, 400, 1);
    mutexSimpleTestTask _test2("testltask2", __pMutexToTest, 300, 1);
    mutexSimpleTestTask _test3("testltask3", __pMutexToTest, 300, 1);
    mutexSimpleTestTask _test4("testltask4", __pMutexToTest, 300, 1);

    while(true) { }

    panic();
}