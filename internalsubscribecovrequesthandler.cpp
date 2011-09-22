#include "internalsubscribecovrequesthandler.h"

#include "bacnetcommon.h"
#include "iamservicedata.h"
#include "internalobjectshandler.h"
#include "bacnetdeviceobject.h"
#include "bacnettsm2.h"

using namespace Bacnet;

InternalSubscribeCOVRequestHandler::InternalSubscribeCOVRequestHandler(Bacnet::BacnetTSM2 *tsm, BacnetDeviceObject *device,
                                                         InternalObjectsHandler *internalHandler, ExternalObjectsHandler *externalHandler):
InternalUnconfirmedRequestHandler(/*tsm, device, internalHandler, externalHandler*/),
_tsm(tsm),
_device(device),
_internalHandler(internalHandler),
_externalHandler(externalHandler)
{
}

InternalSubscribeCOVRequestHandler::~InternalSubscribeCOVRequestHandler()
{

}

bool InternalSubscribeCOVRequestHandler::asynchActionFinished(int asynchId, int result, BacnetObject *object, BacnetDeviceObject *device)
{
    Q_UNUSED(asynchId);
    Q_UNUSED(result);
    Q_UNUSED(object);
    Q_UNUSED(device);
    Q_ASSERT(false);//shouldn't be invoked
    return true;//in case it is, tell it's done.
}

bool InternalSubscribeCOVRequestHandler::isFinished()
{
    return true;
}

void InternalSubscribeCOVRequestHandler::finalize(bool *deleteAfter)
{
    Q_CHECK_PTR(deleteAfter);
    if (deleteAfter)
        *deleteAfter = true;
}

bool InternalSubscribeCOVRequestHandler::execute()
{
}

qint32 InternalSubscribeCOVRequestHandler::fromRaw(quint8 *servicePtr, quint16 length)
{
    return _data.fromRaw(servicePtr, length);
}
