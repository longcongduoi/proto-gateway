#ifndef ANALOGINPUTOBJECT_H
#define ANALOGINPUTOBJECT_H

#include <QMap>

#include "bacnetdata.h"
#include "bacnetobject.h"
#include "bacnetobjectinternalsupport.h"

class BacnetDeviceObject;
class Property;
class AnalogInputObject:
        public BacnetObject,
        public BacnetObjectInternalSupport
{
public:
    AnalogInputObject(Bacnet::ObjectIdStruct identifier, BacnetDeviceObject *parent);
    AnalogInputObject(quint32 instanceNumber, BacnetDeviceObject *parent);
    ~AnalogInputObject();

public://functions overridden from
    //! Used to check if we can read from the device. If not yet, the asynchronous id for read request should be returned or error status.
    virtual int ensurePropertyReadyRead(BacnetProperty::Identifier propertyId);
    //! Returns the data associated with the propertyId.
    virtual Bacnet::BacnetDataInterface *propertyReadInstantly(Bacnet::ReadPropertyServiceData *rpStruct, Bacnet::Error *error);
    virtual int ensurePropertyReadySet(Bacnet::PropertyValueStruct &writeData, Bacnet::Error *error);

public://functions overridden from PropertyOwner
    /** Hook function that is called after having requested reading/writting a property (which obviously doesn't
        belong to Bacnet). Here we find, which property it is, add some BACnet specific parameters and propagate
        them upwards to device, which calls Protocol handler.
      */
    virtual void asynchActionFinished(int asynchId, Property *property, Property::ActiontResult actionResult);

    //not used
    virtual int getPropertyRequest(PropertySubject *toBeGotten);
    virtual int setPropertyRequest(PropertySubject *toBeSet, QVariant &value);


public:
    QVariant::Type variantTypeForProperty_helper(BacnetProperty::Identifier propertyId);
    Bacnet::BacnetDataInterface *createBacnetTypeForProperty_helper(BacnetProperty::Identifier propertyId, quint32 arrayIdx);

    BacnetDeviceObject *_parentDevice;
    Bacnet::ObjectIdStruct _id;
    QMap<BacnetProperty::Identifier, Bacnet::BacnetDataInterface*> _specializedProperties;
};

#endif // ANALOGINPUTOBJECT_H