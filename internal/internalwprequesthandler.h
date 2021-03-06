#ifndef INTERNALWPREQUESTHANDLER_H
#define INTERNALWPREQUESTHANDLER_H

#include "internalconfirmedrequesthandler.h"
#include "writepropertyservicedata.h"

namespace Bacnet {

class BacnetApplicationLayerHandler;

    class InternalWPRequestHandler:
        public ::InternalConfirmedRequestHandler
    {
    public:
        InternalWPRequestHandler(BacnetConfirmedRequestData *crData, BacnetAddress &requester, BacnetAddress &destination,
                                 BacnetDeviceObject *device,
                                 BacnetApplicationLayerHandler *appLayer);
        virtual ~InternalWPRequestHandler();

    public://! overriden from InternalWhoIsRequestHandler, but \todo hsould be declaredin InternalRequestHandler.
        virtual qint32 fromRaw(quint8 *servicePtr, quint16 length);

    public://overriden InternalRequestHandler methods.
        virtual bool asynchActionFinished(int asynchId, int result, BacnetObject *object, BacnetDeviceObject *device);
        virtual bool isFinished();
        virtual void finalize(bool *deleteAfter);
        virtual bool execute();

    public://overriden InternalConfirmedRequestHandler methods.
        virtual bool hasError();
        virtual Error &error();
        virtual Bacnet::BacnetServiceData *takeResponseData();


    private:
        bool finishWriting_helper(BacnetDeviceObject *object, int resultCode);

    private:
        BacnetDeviceObject *_device;
        BacnetApplicationLayerHandler *_appLayer;

        WritePropertyServiceData _data;
        int _asynchId;
        Error _error;
    };

}

#endif // INTERNALWPREQUESTHANDLER_H
