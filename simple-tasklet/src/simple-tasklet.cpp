#include <miniThread.hpp>
#include <mn_schedular.hpp>
#include <iostream>

using namespace mn;

void err_cheak(int error, int OK);

#define TASKLET_TEST_NUMBER     3
#define TASKLET_TEST_DELAY      5
#define TASKLET_TEST_PARAMETER  35

class test_tasklet : public tasklet_t {
public:
    test_tasklet(char id) : tasklet_t(), m_iId(id) { }
protected:
    bool on_tasklet(uint32_t arg) {
        BaseType_t xInterfaceToService;
        xInterfaceToService = ( BaseType_t ) arg;

        printf("[TSK: %d] param: %d\n", m_iId,  xInterfaceToService);
        return true;
    }
private:
    char m_iId;
};

class test_tasklet_task : public basic_task {
public:
    test_tasklet_task()
        : basic_task("test_tasklet_task"), m_iParameter(TASKLET_TEST_PARAMETER) { }

    virtual void on_start() override {
        std::cout << "start task test_tasklet_task" << std::endl;

        for (int i = 0; i < TASKLET_TEST_NUMBER; i++) {
            m_testTask[i] = new test_tasklet((char)i);
        }
    }
    virtual void*  on_task() override {

        while(true) {
            basic_task::usleep(TASKLET_TEST_DELAY);

            for (int i = 0; i < TASKLET_TEST_NUMBER; i++) {
                m_testTask[i]->schedule(m_iParameter);
            }
            m_iParameter++;
        }
        // Never reach
        return NULL;
    }
private:
    int m_iParameter;
    test_tasklet* m_testTask[TASKLET_TEST_NUMBER];
};

MN_EXTERNC_BEGINN

void app_main() {
	MN_THREAD_VERSION_INFO("basic tasklet example");

    test_tasklet_task test_tasklet_task;

    err_cheak(test_tasklet_task.start(), ERR_TASK_OK);

    schedular::start();

    std::cout << "scheduler ended" << std::endl;
}

void err_cheak(int error, int OK) {

    if(error == ERR_TASK_CANTINITMUTEX) {
        printf("The task can not started - (error creating the using LockObjets, the task is not created)\n");
    } else if(error == ERR_TASK_ALREADYRUNNING) {
        printf("The task can not started - (All ready running)\n");
    } else if (error == ERR_TASK_CANTSTARTTHREAD) {
        printf("The task can not started - (can't create task handle)\n");
    } else if(error == OK) {
        printf("The task are created\n");
        return;
    }
    panic();
}

MN_EXTERNC_END
