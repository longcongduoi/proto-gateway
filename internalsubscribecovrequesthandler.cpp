#include "internalsubscribecovrequesthandler.h"

#include "bacnetcommon.h"
#include "iamservicedata.h"
#include "internalobjectshandler.h"
#include "bacnetdeviceobject.h"
#include "bacnetobject.h"
#include "bacnettsm2.h"

using namespace Bacnet;

InternalSubscribeCOVRequestHandler::InternalSubscribeCOVRequestHandler(BacnetConfirmedRequestData *crData, BacnetAddress &requester, BacnetAddress &destination,
                                                                       Bacnet::BacnetTSM2 *tsm, BacnetDeviceObject *device,
                                                                       BacnetApplicationLayerHandler *appLayer):
    InternalConfirmedRequestHandler(crData, requester, destination),
    _tsm(tsm),
    _device(device),
    _appLayer(appLayer)
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
    Q_CHECK_PTR(_appLayer);//should never happen in case of confirmed services.
    BacnetObject *object = _device->bacnetObject(_data._monitoredObjectId.instanceNumber());
    Q_CHECK_PTR(object);

    if (0 == object) {
        _error.setError(BacnetErrorNS::ClassObject, BacnetErrorNS::CodeUnknownObject);
    } else {
        if (_data.isCancellation()) {
            object->rmCovSubscription(_data._subscriberProcId, _requester, _data._monitoredObjectId, (*_data._propReference), &_error);
        } else {
            object->addOrUpdateCovSubscription(_data, _requester, &_error);//if something wrong happens, object will set error.
        }
    }
    finalizeInstant(_tsm);
    return true;//we are done. This instance may be deleted.
}

bool InternalSubscribeCOVRequestHandler::hasError()
{
    return _error.hasError();
}

Bacnet::Error &InternalSubscribeCOVRequestHandler::error()
{
    return _error;
}

Bacnet::BacnetServiceData *InternalSubscribeCOVRequestHandler::takeResponseData()
{
    return 0;//simple ACK.
}

qint32 InternalSubscribeCOVRequestHandler::fromRaw(quint8 *servicePtr, quint16 length)
{
    return _data.fromRaw(servicePtr, length);
}
