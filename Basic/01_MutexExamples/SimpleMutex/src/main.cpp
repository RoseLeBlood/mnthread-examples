#include <miniThread.hpp>

#include <stdio.h>
#include <iostream>

class mutexSimpleTestTask : public basic_task {
public:
    TestThread(std::string name, mutex_t& lock, int sleepMS, int cpu)
        : basic_task(name), Lock(lock), m_sleepMS(sleepMS) { start(cpu); };

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
        std::cout << "test_lock_print.on_task@ " << m_strName << std::endl;
    }

private:
    int m_sleepMS;
    mutex_t& m_refLock;
};

extern "C" void app_main() {
    std::cout << "Thank you for use miniThread v. " << mnversion_t::instance().to_string() << std::endl;
    std::cout << "basic mutex example" << std::endl;

    mutex_t * __pMutexToTest = new mutex_t();

    mutexSimpleTestTask _test1("testltask1", *__pMutexToTest, 400, 1);
    mutexSimpleTestTask _test2("testltask2", *__pMutexToTest, 300, 1);
    mutexSimpleTestTask _test3("testltask3", *__pMutexToTest, 300, 1);
    mutexSimpleTestTask _test4("testltask4", *__pMutexToTest, 300, 1);

    while(true) { }

    mn_panic();
}