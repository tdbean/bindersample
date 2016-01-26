#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include "ISimpleService.h"

#include <sys/time.h>


using namespace android;

int main(int argc, char** argv)
{
	struct timeval tv, tv1;
	struct timezone tz, tz1;

	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder;

	binder = sm->getService(String16("simpleservice"));
	sp<ISimpleService> sc(interface_cast<ISimpleService>(binder));

	gettimeofday (&tv, &tz);
	sc->Deliver(5);
	gettimeofday (&tv1, &tz1);

	printf("TIme cost: (%lu, %lu) (%lu, %lu)\n", tv.tv_sec, tv.tv_usec, tv1.tv_sec, tv1.tv_usec );
	printf("Delta: %lu ms\n", (tv1.tv_sec - tv.tv_sec) * 1000 + (tv1.tv_usec - tv.tv_usec) / 1000);

	return 0;
}

