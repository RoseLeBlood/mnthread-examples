#include <miniThread.hpp>

int err_cheak(int error, int OK) ;

class test_tasklet : public tasklet_t {
protected: 
    bool on_coroutine(uint32_t arg) {
        BaseType_t xInterfaceToService;
        xInterfaceToService = ( BaseType_t ) arg;

        printf("Interface to service: %d\n", xInterfaceToService);
    }
};

extern "C" void app_main() {
    std::cout << "Thank you for use miniThread v. " << mnversion_t::instance().to_string() << std::endl;
    std::cout << "basic tasklet example" << std::endl;

    test_tasklet taskLet_test;

    err_cheak(taskLet_test.create(0), ERR_COROUTINE_OK);

    for(;;) ;
}

void err_cheak(int error, int OK) {

    if(error == ERR_COROUTINE_CANTSTART) {
        printf("The tasklet can not started - (i.e. timeout)\n");
    } else if(error == ERR_COROUTINE_CANTSTART) {
        printf("The tasklet can not started - the Locking Object can't create\n");
    } else if(error == OK) {
        printf("The tasklet are created\n");
        return;
    }
    mn_panic();
}