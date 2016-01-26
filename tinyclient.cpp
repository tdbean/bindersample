#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <sys/time.h>

#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/CallStack.h>
#include <utils/Log.h>


using namespace android;

int main(int argc, char** argv)
{
	struct timeval tv, tv1;
	struct timezone tz, tz1;

	Parcel data, reply;


	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder;

	binder = sm->getService(String16("tinysvc"));

	//data.writeInterfaceToken(ISimpleService::getInterfaceDescriptor());
	data.writeInt32(6);

	gettimeofday (&tv, &tz);
	status_t status = binder->transact(IBinder::FIRST_CALL_TRANSACTION + 1, data, &reply);
	gettimeofday (&tv1, &tz1);

	printf("TIme cost: (%lu, %lu) (%lu, %lu)\n", tv.tv_sec, tv.tv_usec, tv1.tv_sec, tv1.tv_usec );
	printf("Delta: %lu ms\n", (tv1.tv_sec - tv.tv_sec) * 1000 + (tv1.tv_usec - tv.tv_usec) / 1000);

	return 0;
}
