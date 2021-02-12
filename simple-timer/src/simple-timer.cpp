#include <miniThread.hpp>

#define TEST_TIMER_PERIOD_TIME 100
#define TEST_TIMER_ONESHOT_TIME 1000

#define TEST_TIMER_MAIN_DELAY   10

int err_cheak(int error, int OK) ;

/**
 * The test one shot timer
 */ 
class test_timer_onshot : public freertos_timer_t {
public:
    test_timer_onshot() 
          : freertos_timer_t("OnShot Test Timer", TEST_TIMER_ONESHOT_TIME, true) {}
protected:
    /**
     * Implementation of your actual timer code.
     * You must override this function.
     */
    virtual void on_timer() {
        static int timer = 0;
        printf("send oneshot timer: %d\n",  timer++);
    }

    /**
     * You can override this functions, call befor on_timer
     */ 
    virtual void on_enter() { 
        printf("created the onshot timer\n" );
    }
    /**
     * You can override this functions, call after on_timer
     */ 
    virtual void on_exit() { 
        printf("exit the onshot timer\n" );
    }
};

/**
 * The test period timer
 */ 
class test_timer_period : public mtimer_t {
public:
    test_timer_period() 
          : mtimer_t("Period Test Timer", TEST_TIMER_PERIOD_TIME, false) {}
protected:
    /**
     * Implementation of your actual timer code.
     * You must override this function.
     */
    virtual void on_timer() {
        static int timer = 0;
        printf("send period timer: %d\n",  timer++);
    }

    /**
     * You can override this functions, call befor on_timer
     */ 
    virtual void on_enter() { 
        printf("created the period timer\n" );
    }
    /**
     * You can override this functions, call after on_timer
     */ 
    virtual void on_exit() { 
        printf("exit the period timer\n" );
    }

};

extern "C" void app_main() {
    std::cout << "Thank you for use miniThread v. " << mnversion_t::instance().to_string() << std::endl;
    std::cout << "basic timer example" << std::endl;

    int imain = 0;

    test_timer_onshot mOneShot(TEST_TIMER_ONESHOT_TIME);
    test_timer_period mPeriodTimer(TEST_TIMER_PERIOD_TIME);

    printf("Create the one shot and period timer\n" );
    err_cheak(mOneShot.create(), ERR_TIMER_OK);
    err_cheak(mPeriodTimer.create(), ERR_TIMER_OK);

    printf("activeted the one shot and period timer\n" );
    err_cheak(mOneShot.active(), ERR_TIMER_OK);
    err_cheak(mPeriodTimer.active(), ERR_TIMER_OK);

    // Wait
    mn_usleep(5);

    // while - cheak the period timer run
    while( ((bool)mPeriodTimer) ) {
        mn_usleep(TEST_TIMER_MAIN_DELAY); // sleep TEST_TIMER_MAIN_DELAY micro seconds
        printf("send from main: %d\n", imain++ );
    }

    // when timer are dead then panic!!
    mn_panic();
}




int err_cheak(int error, int OK) {
    if(error != OK) {
        mn_panic();
    }
    return error;
}