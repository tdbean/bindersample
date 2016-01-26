#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/CallStack.h>
#include <utils/Log.h>
#include "ISimpleService.h"

#define PERFD_DEBUG 1

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "SimpleService"
#endif

namespace android {

#ifdef PERFD_DEBUG
void DebugCallstackDump(void)
{
	CallStack stack(LOG_TAG);
	printf("Callstack:\n%s\n", stack.toString().string());
}
#else
void DebugCallstackDump(void) {}
#endif

class BpSimpleService: public BpInterface<ISimpleService>
{
public:
	BpSimpleService(const sp<IBinder>& impl)  : BpInterface<ISimpleService>(impl) {}
	virtual int32_t Deliver(int32_t index)
	{
		Parcel data, reply;
		data.writeInterfaceToken(ISimpleService::getInterfaceDescriptor());
		data.writeInt32(index);
		status_t status = remote()->transact(PFD_DELIVER, data, &reply);

		if (status != NO_ERROR) {
			ALOGD("Notify() could not contact remote: %d\n", status);
			return -1;
		}

		int32_t err = reply.readExceptionCode();
		int32_t ret = reply.readInt32();
		if (err < 0) {
			ALOGD("Notify() caught exception %d\n", err);
			return -1;
		}
		return ret;
	}
};

IMPLEMENT_META_INTERFACE(SimpleService, "android.simpleservice");

// ----------------------------------------------------------------------

status_t SimpleService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
#ifdef PERFD_DEBUG
	printf("SimpleService::onTransact: pid[%d]  Code: %d\n", getpid(), code);
#endif
	DebugCallstackDump();

	switch(code) {
	case IBinder::FIRST_CALL_TRANSACTION:
	{
		CHECK_INTERFACE(ISimpleService, data, reply);
		int32_t index = data.readInt32();
		printf("SimpleService PFD_DELIVER: %d\n", index);
		int32_t ret = 6;
		reply->writeNoException();
		reply->writeInt32(ret);
		return NO_ERROR;
	}
	default:
		return BBinder::onTransact(code, data, reply, flags);
	}
}

SimpleService::SimpleService()
{
	printf("SimpleService BBinder\n");
	DebugCallstackDump();
}

// ----------------------------------------------------------------------------

}; // namespace android
