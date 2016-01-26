
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/CallStack.h>
#include <utils/Log.h>

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

#include <binder/ProcessState.h>

using namespace android;
//namespace android {

void DebugCallstackDump(void)
{
	CallStack stack("TINYSVC");
	printf("Callstack:\n%s\n", stack.toString().string());
}

class TinySvc: public BBinder {
public:
	status_t onTransact(uint32_t code, const Parcel& data,
		Parcel* reply, uint32_t flags = 0)
	{
		printf("onTransact: pid[%d]  Code: %d\n", getpid(), code);
		DebugCallstackDump();
		return BBinder::onTransact(code, data, reply, flags);
	}
};

int main(int argc, char** argv)
{
	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();

	sm->addService(String16("tinysvc"), new TinySvc());

	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
	return 0;
}

//} // namespace android
