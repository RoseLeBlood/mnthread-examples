#include <miniThread.hpp>
#include <iostream>

#define _PROJECT_NAME "simple empty example"

using namespace mn;

MN_EXTERNC_BEGINN

void app_main() {
	MN_THREAD_VERSION_INFO(_PROJECT_NAME);

    /* Code goes hier */

    panic();
}

MN_EXTERNC_END
