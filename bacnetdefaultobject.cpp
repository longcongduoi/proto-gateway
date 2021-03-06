#include "bacnetdefaultobject.h"

#include "bacnetprimitivedata.h"
#include "bacnetconstructeddata.h"
#include "bacnetdataabstract.h"
#include "bacnetprimitivedata.h"
#include "bacnetproperty.h"

using namespace Bacnet;

BacnetDefaultObject *BacnetDefaultObject::_instance = 0;

BacnetDefaultObject::BacnetDefaultObject()
{
}

BacnetDefaultObject *BacnetDefaultObject::instance()
{
    if (_instance == 0)
        _instance = new BacnetDefaultObject();
    return _instance;
}


Bacnet::BacnetDataInterface *BacnetDefaultObject::createDataProperty(AppTags::BacnetTags propertyType, QVariant *value, bool *ok)
{
    BacnetDataInterface *result(0);

    switch (propertyType) {
    case (AppTags::Null):                   result = new Bacnet::Null(); break;
    case (AppTags::Boolean):                result = new Bacnet::Boolean(); break;
    case (AppTags::UnsignedInteger):        result = new Bacnet::UnsignedInteger(); break;
    case(AppTags::SignedInteger):           result = new Bacnet::SignedInteger(); break;
    case(AppTags::Real):                    result = new Bacnet::Real(); break;
    case(AppTags::Double):                  result = new Bacnet::Double(); break;
    case(AppTags::OctetString):             result = new Bacnet::OctetString(); break;
    case(AppTags::CharacterString):         result = new Bacnet::CharacterString(); break;
    case(AppTags::BitString):               result = new Bacnet::BitString(); break;
    case(AppTags::Enumerated):              result = new Bacnet::Enumerated(); break;
    case(AppTags::Date):                    result = new Bacnet::Date(); break;
    case(AppTags::Time):                    result = new Bacnet::Time(); break;
    case(AppTags::BacnetObjectIdentifier):  result = new Bacnet::ObjectIdentifier(); break;
    default:
        ;//do nothing - result is already set to 0
    }

    if ( (0 != result) && (0 != value) ) {
        bool okey = result->setInternal(*value);
        if (0 != ok)
            *ok = okey;
    }

    return result;
}

Bacnet::BacnetDataInterface *BacnetDefaultObject::createDataForObjectProperty(BacnetObjectTypeNS::ObjectType type, BacnetPropertyNS::Identifier propertyId, quint32 arrayIndex)
{
    switch (type)
    {
    case (BacnetObjectTypeNS::Device):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::SystemStatus):                    return new Bacnet::DeviceStatus();
        case (BacnetPropertyNS::VendorName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::VendorIdentifier):                return new Bacnet::Unsigned16();//DataType::Unsigned16;
        case (BacnetPropertyNS::ModelName):                       return new Bacnet::CharacterString();
        case (BacnetPropertyNS::FirmwareRevision):                return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ApplicationSoftwareVersion):      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::Location):                        return new Bacnet::CharacterString();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ProtocolVersion):                 return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::ProtocolRevision):                return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::ProtocolServicesSupported):       return new Bacnet::ServicesSupported();
        case (BacnetPropertyNS::ProtocolObjectTypesSupported):    return new Bacnet::ObjectTypesSupported();
        case (BacnetPropertyNS::ObjectList):
#warning "Set stored type to ObjectID!"
            if (arrayIndex == ArrayIndexNotPresent)
                return new Bacnet::BacnetArray(/*DataType::BACnetObjectIdentifier*/);
            else
                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::MaxApduLengthAccepted):           return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::SegmentationSupported):           return new Bacnet::Segmentation();
            //        case (BacnetProperty::MaxSegmentsAccepted):             return DataType::Unsigned;
            //        case (BacnetProperty::VtClassesSupported):              return DataType::BACnetList | DataType::BACnetVTClass;;
            //        case (BacnetProperty::ActiveVtSessions):                return DataType::BACnetList | DataType::BACnetVTSession;
            //        case (BacnetProperty::LocalTime):                       return DataType::Time;
            //        case (BacnetProperty::LocalDate):                       return DataType::Date;
            //        case (BacnetProperty::UtcOffset):                       return DataType::Signed;
            //        case (BacnetProperty::DaylightSavingsStatus):           return DataType::BOOLEAN;
            //        case (BacnetProperty::ApduSegmentTimeout):              return DataType::Unsigned;
        case (BacnetPropertyNS::ApduTimeout):                     return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NumberOfAPDURetries):             return new Bacnet::UnsignedInteger();
            //        case (BacnetProperty::ListOfSessionKeys):               return DataType::BACnetList | DataType::BACnetSessionKey;
            //        case (BacnetProperty::TimeSynchronizationRecipients):   return DataType::BACnetList | DataType::BACnetRecipient;
            //        case (BacnetProperty::MaxMaster):                       return DataType::Unsigned;
            //        case (BacnetProperty::MaxInfoFrames):                   return DataType::Unsigned;
        case (BacnetPropertyNS::DeviceAddressBinding):
            if (arrayIndex != ArrayIndexNotPresent)
                return new Bacnet::BacnetList(/*DataType::BACnetAddressBinding*/);
            else {
#warning "This has to be handled by device object separately!"
                return new Bacnet::Address();
            }
        case (BacnetPropertyNS::DatabaseRevision):                return new Bacnet::UnsignedInteger();
            //        case (BacnetProperty::ConfigurationFiles):              return DataType::BACnetArray | DataType::BACnetObjectIdentifier;
            //        case (BacnetProperty::LastRestoreTime):                 return DataType::BACnetTimeStamp;
            //        case (BacnetProperty::BackupFailureTimeout):            return DataType::Unsigned16;
        case (BacnetPropertyNS::ActiveCovSubscriptions):          return new Bacnet::BacnetList(/*DataType::BACnetCOVSubscription*/);
            //        case (BacnetProperty::SlaveProxyEnable):                return DataType::BACnetArray | DataType::BOOLEAN;
            //        case (BacnetProperty::ManualSlaveAddressBinding):       return DataType::BACnetList | DataType::BACnetAddressBinding;
            //        case (BacnetProperty::AutoSlaveDiscovery):              return DataType::BACnetArray | DataType::BOOLEAN;
            //        case (BacnetProperty::SlaveAddressBinding):             return DataType::BACnetList | DataType::BACnetAddressBinding;
        case (BacnetPropertyNS::ProfileName):                       return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    case (BacnetObjectTypeNS::AnalogInput):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::PresentValue):                    return new Bacnet::Real();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::DeviceType):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::StatusFlags):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventState):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Reliability):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::OutOfService):                    return new Bacnet::Boolean();
        case (BacnetPropertyNS::UpdateInterval):                  return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::Units):                           return new Bacnet::Enumerated();
        case (BacnetPropertyNS::MinPresValue):                    return new Bacnet::Real();
        case (BacnetPropertyNS::MaxPresValue):                    return new Bacnet::Real();
        case (BacnetPropertyNS::Resolution):                      return new Bacnet::Real();
        case (BacnetPropertyNS::CovIncrement):                    return new Bacnet::Real();
        case (BacnetPropertyNS::TimeDelay):                       return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NotificationClass):               return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::HighLimit):                       return new Bacnet::Real();
        case (BacnetPropertyNS::LowLimit):                        return new Bacnet::Real();
        case (BacnetPropertyNS::Deadband):                        return new Bacnet::Real();
        case (BacnetPropertyNS::LimitEnable):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventEnable):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::AckedTransitions):                return new Bacnet::BitString();
        case (BacnetPropertyNS::NotifyType):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventTimeStamps):
            if (ArrayIndexNotPresent != arrayIndex)
                return new Bacnet::BacnetArray(/*DataType::BACnetTimeStamp*/);
            else {
                return new Bacnet::TimeStamp();
            }
        case (BacnetPropertyNS::ProfileName):                     return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    case (BacnetObjectTypeNS::AnalogOutput):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::PresentValue):                    return new Bacnet::Real();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::DeviceType):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::StatusFlags):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventState):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Reliability):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::OutOfService):                    return new Bacnet::Boolean();
        case (BacnetPropertyNS::Units):                           return new Bacnet::Enumerated();
        case (BacnetPropertyNS::MinPresValue):                    return new Bacnet::Real();
        case (BacnetPropertyNS::MaxPresValue):                    return new Bacnet::Real();
        case (BacnetPropertyNS::Resolution):                      return new Bacnet::Real();
        case (BacnetPropertyNS::RelinquishDefault):               return new Bacnet::Real();
            //        case (BacnetProperty::PriorityArray):                   return new Bacnet::PRIORITYARRAY
        case (BacnetPropertyNS::CovIncrement):                    return new Bacnet::Real();
        case (BacnetPropertyNS::TimeDelay):                       return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NotificationClass):               return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::HighLimit):                       return new Bacnet::Real();
        case (BacnetPropertyNS::LowLimit):                        return new Bacnet::Real();
        case (BacnetPropertyNS::Deadband):                        return new Bacnet::Real();
        case (BacnetPropertyNS::LimitEnable):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventEnable):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::AckedTransitions):                return new Bacnet::BitString();
        case (BacnetPropertyNS::NotifyType):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventTimeStamps):
            if (arrayIndex == ArrayIndexNotPresent)
                return new Bacnet::BacnetArray(/*DataType::BACnetTimeStamp*/);
            else
                return new Bacnet::TimeStamp();
        case (BacnetPropertyNS::ProfileName):                     return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    case (BacnetObjectTypeNS::AnalogValue):
        switch(propertyId)
        {
        case (BacnetPropertyNS::PresentValue):                return new Bacnet::Real();
        default:
            return new Bacnet::DataAbstract();
        }
    case (BacnetObjectTypeNS::BinaryInput):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::PresentValue):                    return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::DeviceType):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::StatusFlags):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventState):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Reliability):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::OutOfService):                    return new Bacnet::Boolean();
        case (BacnetPropertyNS::Polarity):                        return new Bacnet::Enumerated();
        case (BacnetPropertyNS::InactiveText):                    return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ActiveText):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ChangeOfStateTime):               return new Bacnet::DateTime();
        case (BacnetPropertyNS::ChangeOfStateCount):              return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeOfStateCountReset):           return new Bacnet::DateTime();
        case (BacnetPropertyNS::ElapsedActiveTime):               return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeOfActiveTimeReset):           return new Bacnet::DateTime();
        case (BacnetPropertyNS::MinimumOffTime):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::MinimumOnTime):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeDelay):                       return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NotificationClass):               return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::AlarmValue):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventEnable):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::AckedTransitions):                return new Bacnet::BitString();
        case (BacnetPropertyNS::NotifyType):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventTimeStamps):
            if (arrayIndex == ArrayIndexNotPresent)
                return new Bacnet::BacnetArray(/*DataType::BACnetTimeStamp*/);
            else
                return new Bacnet::TimeStamp();
        case (BacnetPropertyNS::ProfileName):                     return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    case (BacnetObjectTypeNS::BinaryOutput):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::PresentValue):                    return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::DeviceType):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::StatusFlags):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventState):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Reliability):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::OutOfService):                    return new Bacnet::Boolean();
        case (BacnetPropertyNS::Polarity):                        return new Bacnet::Enumerated();
        case (BacnetPropertyNS::InactiveText):                    return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ActiveText):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ChangeOfStateTime):               return new Bacnet::DateTime();
        case (BacnetPropertyNS::ChangeOfStateCount):              return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeOfStateCountReset):           return new Bacnet::DateTime();
        case (BacnetPropertyNS::ElapsedActiveTime):               return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeOfActiveTimeReset):           return new Bacnet::DateTime();
        case (BacnetPropertyNS::MinimumOffTime):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::MinimumOnTime):                    return new Bacnet::UnsignedInteger();
//        case (BacnetProperty::PriorityArray):                   return new Bacnet::PRIORITYARRAY
        case (BacnetPropertyNS::RelinquishDefault):               return new Bacnet::Enumerated();
        case (BacnetPropertyNS::TimeDelay):                       return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NotificationClass):               return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::FeedbackValue):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventEnable):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::AckedTransitions):                return new Bacnet::BitString();
        case (BacnetPropertyNS::NotifyType):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventTimeStamps):
            if (arrayIndex == ArrayIndexNotPresent)
                return new Bacnet::BacnetArray(/*DataType::BACnetTimeStamp*/);
            else
                return new Bacnet::TimeStamp();
        case (BacnetPropertyNS::ProfileName):                     return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    case (BacnetObjectTypeNS::BinaryValue):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::PresentValue):                    return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::StatusFlags):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventState):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Reliability):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::OutOfService):                    return new Bacnet::Boolean();
        case (BacnetPropertyNS::InactiveText):                    return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ActiveText):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ChangeOfStateTime):               return new Bacnet::DateTime();
        case (BacnetPropertyNS::ChangeOfStateCount):              return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeOfStateCountReset):           return new Bacnet::DateTime();
        case (BacnetPropertyNS::ElapsedActiveTime):               return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeOfActiveTimeReset):           return new Bacnet::DateTime();
        case (BacnetPropertyNS::MinimumOffTime):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::MinimumOnTime):                    return new Bacnet::UnsignedInteger();
//        case (BacnetProperty::PriorityArray):                   return new Bacnet::PRIORITYARRAY
        case (BacnetPropertyNS::RelinquishDefault):               return new Bacnet::Enumerated();
        case (BacnetPropertyNS::TimeDelay):                       return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NotificationClass):               return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::AlarmValue):                        return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventEnable):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::AckedTransitions):                return new Bacnet::BitString();
        case (BacnetPropertyNS::NotifyType):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventTimeStamps):
            if (arrayIndex == ArrayIndexNotPresent)
                return new Bacnet::BacnetArray(/*DataType::BACnetTimeStamp*/);
            else
                return new Bacnet::TimeStamp();
        case (BacnetPropertyNS::ProfileName):                     return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    case (BacnetObjectTypeNS::MultiStateInput):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::PresentValue):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::DeviceType):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::StatusFlags):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventState):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Reliability):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::OutOfService):                    return new Bacnet::Boolean();
        case (BacnetPropertyNS::NumberOfStates):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::StateText):
            if (ArrayIndexNotPresent == arrayIndex)
                return new Bacnet::BacnetArray(/*Bacnet::CharacterString*/);
            else
                return new Bacnet::CharacterString();
        case (BacnetPropertyNS::TimeDelay):                         return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NotificationClass):                 return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::AlarmValues):   //fall through
        case (BacnetPropertyNS::FaultValues):
            if (ArrayIndexNotPresent == arrayIndex)
                return new Bacnet::BacnetList(/*DataType::Unsigned*/);
            else
                return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::EventEnable):                   return new Bacnet::BitString();
        case (BacnetPropertyNS::AckedTransitions):              return new Bacnet::BitString();
        case (BacnetPropertyNS::NotifyType):                    return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventTimeStamps):
            if (ArrayIndexNotPresent == arrayIndex)
                return new Bacnet::BacnetArray(/*BacnetTimeStamp*/);
            else
                return new Bacnet::TimeStamp();
        case (BacnetPropertyNS::ProfileName):                   return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    case (BacnetObjectTypeNS::MultiStateOutput):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::PresentValue):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::DeviceType):                        return new Bacnet::CharacterString();
        case (BacnetPropertyNS::StatusFlags):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventState):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Reliability):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::OutOfService):                    return new Bacnet::Boolean();
        case (BacnetPropertyNS::NumberOfStates):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::StateText):
            if (ArrayIndexNotPresent == arrayIndex)
                return new Bacnet::BacnetArray(/*Bacnet::CharacterString*/);
            else
                return new Bacnet::CharacterString();
//        case (BacnetPropertyNS::PriorityArray):
        case (BacnetPropertyNS::RelinquishDefault):                 return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeDelay):                         return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NotificationClass):                 return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::FeedbackValue):                     return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::EventEnable):                   return new Bacnet::BitString();
        case (BacnetPropertyNS::AckedTransitions):              return new Bacnet::BitString();
        case (BacnetPropertyNS::NotifyType):                    return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventTimeStamps):
            if (ArrayIndexNotPresent == arrayIndex)
                return new Bacnet::BacnetArray(/*BacnetTimeStamp*/);
            else
                return new Bacnet::TimeStamp();
        case (BacnetPropertyNS::ProfileName):                   return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    case (BacnetObjectTypeNS::MultiStateValue):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return new Bacnet::ObjectIdentifier();
        case (BacnetPropertyNS::ObjectName):                      return new Bacnet::CharacterString();
        case (BacnetPropertyNS::ObjectType):                      return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::PresentValue):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::Description):                     return new Bacnet::CharacterString();
        case (BacnetPropertyNS::StatusFlags):                     return new Bacnet::BitString();
        case (BacnetPropertyNS::EventState):                      return new Bacnet::Enumerated();
        case (BacnetPropertyNS::Reliability):                     return new Bacnet::Enumerated();
        case (BacnetPropertyNS::OutOfService):                    return new Bacnet::Boolean();
        case (BacnetPropertyNS::NumberOfStates):                    return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::StateText):
            if (ArrayIndexNotPresent == arrayIndex)
                return new Bacnet::BacnetArray(/*Bacnet::CharacterString*/);
            else
                return new Bacnet::CharacterString();
 //        case (BacnetPropertyNS::PriorityArray):
        case (BacnetPropertyNS::RelinquishDefault):                 return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::TimeDelay):                         return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::NotificationClass):                 return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::AlarmValues):   //fall through
        case (BacnetPropertyNS::FaultValues):
            if (ArrayIndexNotPresent == arrayIndex)
                return new Bacnet::BacnetList(/*DataType::Unsigned*/);
            else
                return new Bacnet::UnsignedInteger();
        case (BacnetPropertyNS::EventEnable):                   return new Bacnet::BitString();
        case (BacnetPropertyNS::AckedTransitions):              return new Bacnet::BitString();
        case (BacnetPropertyNS::NotifyType):                    return new Bacnet::Enumerated();
        case (BacnetPropertyNS::EventTimeStamps):
            if (ArrayIndexNotPresent == arrayIndex)
                return new Bacnet::BacnetArray(/*BacnetTimeStamp*/);
            else
                return new Bacnet::TimeStamp();
        case (BacnetPropertyNS::ProfileName):                   return new Bacnet::CharacterString();
        default:
            return new Bacnet::DataAbstract();
        }
        break;
    default:
        return 0;
    }
}



quint32 BacnetDefaultObject::proeprtyType(BacnetObjectTypeNS::ObjectType type, BacnetPropertyNS::Identifier propertyId, quint32 arrayIdx)
{
    switch (type)
    {
    case (BacnetObjectTypeNS::Device):
        switch (propertyId)
        {
        case (BacnetPropertyNS::ObjectIdentifier):                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::ObjectName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ObjectType):                      return DataType::BACnetObjectType;
        case (BacnetPropertyNS::SystemStatus):                    return DataType::BACnetDeviceStatus;
        case (BacnetPropertyNS::VendorName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::VendorIdentifier):                return DataType::Unsigned16;
        case (BacnetPropertyNS::ModelName):                       return DataType::CharacterString;
        case (BacnetPropertyNS::FirmwareRevision):                return DataType::CharacterString;
        case (BacnetPropertyNS::ApplicationSoftwareVersion):      return DataType::CharacterString;
        case (BacnetPropertyNS::Location):                        return DataType::CharacterString;
        case (BacnetPropertyNS::Description):                     return DataType::CharacterString;
        case (BacnetPropertyNS::ProtocolVersion):                 return DataType::Unsigned;
        case (BacnetPropertyNS::ProtocolRevision):                return DataType::Unsigned;
        case (BacnetPropertyNS::ProtocolServicesSupported):       return DataType::BACnetServicesSupported;
        case (BacnetPropertyNS::ProtocolObjectTypesSupported):    return DataType::BACnetObjectTypesSupported;
        case (BacnetPropertyNS::ObjectList):
            if (arrayIdx == ArrayIndexNotPresent)
                return DataType::BACnetArray | DataType::BACnetObjectIdentifier;
            else
                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::MaxApduLengthAccepted):           return DataType::Unsigned;
        case (BacnetPropertyNS::SegmentationSupported):           return DataType::BACnetSegmentation;;
            //        case (BacnetProperty::MaxSegmentsAccepted):             return DataType::Unsigned;
            //        case (BacnetProperty::VtClassesSupported):              return DataType::BACnetList | DataType::BACnetVTClass;;
            //        case (BacnetProperty::ActiveVtSessions):                return DataType::BACnetList | DataType::BACnetVTSession;
            //        case (BacnetProperty::LocalTime):                       return DataType::Time;
            //        case (BacnetProperty::LocalDate):                       return DataType::Date;
            //        case (BacnetProperty::UtcOffset):                       return DataType::Signed;
            //        case (BacnetProperty::DaylightSavingsStatus):           return DataType::BOOLEAN;
            //        case (BacnetProperty::ApduSegmentTimeout):              return DataType::Unsigned;
        case (BacnetPropertyNS::ApduTimeout):                     return DataType::Unsigned;
        case (BacnetPropertyNS::NumberOfAPDURetries):             return DataType::Unsigned;
            //        case (BacnetProperty::ListOfSessionKeys):               return DataType::BACnetList | DataType::BACnetSessionKey;
            //        case (BacnetProperty::TimeSynchronizationRecipients):   return DataType::BACnetList | DataType::BACnetRecipient;
            //        case (BacnetProperty::MaxMaster):                       return DataType::Unsigned;
            //        case (BacnetProperty::MaxInfoFrames):                   return DataType::Unsigned;
        case (BacnetPropertyNS::DeviceAddressBinding):
            if (arrayIdx == ArrayIndexNotPresent)
                return DataType::BACnetList | DataType::BACnetAddressBinding;
            else
                return DataType::BACnetAddressBinding;
        case (BacnetPropertyNS::DatabaseRevision):                return DataType::Unsigned;
            //        case (BacnetProperty::ConfigurationFiles):              return DataType::BACnetArray | DataType::BACnetObjectIdentifier;
            //        case (BacnetProperty::LastRestoreTime):                 return DataType::BACnetTimeStamp;
            //        case (BacnetProperty::BackupFailureTimeout):            return DataType::Unsigned16;
        case (BacnetPropertyNS::ActiveCovSubscriptions):
            if (arrayIdx == ArrayIndexNotPresent)
                return DataType::BACnetList | DataType::BACnetCOVSubscription;
            else
                return DataType::BACnetCOVSubscription;
            //        case (BacnetProperty::SlaveProxyEnable):                return DataType::BACnetArray | DataType::BOOLEAN;
            //        case (BacnetProperty::ManualSlaveAddressBinding):       return DataType::BACnetList | DataType::BACnetAddressBinding;
            //        case (BacnetProperty::AutoSlaveDiscovery):              return DataType::BACnetArray | DataType::BOOLEAN;
            //        case (BacnetProperty::SlaveAddressBinding):             return DataType::BACnetList | DataType::BACnetAddressBinding;
            //        case (BacnetProperty::ProfileName):                     return DataType::CharacterString;
        default:
            return DataType::InvalidType;
        }
        break;
    case (BacnetObjectTypeNS::AnalogInput):
        switch (propertyId)
        {

        case (BacnetPropertyNS::ObjectIdentifier):                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::ObjectName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ObjectType):                      return DataType::BACnetObjectType;
        case (BacnetPropertyNS::PresentValue):                    return DataType::Real;
        case (BacnetPropertyNS::Description):                     return DataType::CharacterString;
        case (BacnetPropertyNS::DeviceType):                      return DataType::CharacterString;
        case (BacnetPropertyNS::StatusFlags):                     return DataType::BitString;
        case (BacnetPropertyNS::EventState):                      return DataType::Enumerated;
        case (BacnetPropertyNS::Reliability):                     return DataType::Enumerated;
        case (BacnetPropertyNS::OutOfService):                    return DataType::BOOLEAN;
        case (BacnetPropertyNS::UpdateInterval):                  return DataType::Unsigned;
        case (BacnetPropertyNS::Units):                           return DataType::Unsigned;
        case (BacnetPropertyNS::MinPresValue):                    return DataType::Real;
        case (BacnetPropertyNS::MaxPresValue):                      return DataType::Real;
        case (BacnetPropertyNS::Resolution):                        return DataType::Real;
        case (BacnetPropertyNS::CovIncrement):                      return DataType::Real;
        case (BacnetPropertyNS::ProfileName):                       return DataType::CharacterString;

        default: return DataType::InvalidType;
        }
        break;
    case (BacnetObjectTypeNS::AnalogOutput):
        switch (propertyId)
        {

        case (BacnetPropertyNS::ObjectIdentifier):                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::ObjectName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ObjectType):                      return DataType::BACnetObjectType;
        case (BacnetPropertyNS::PresentValue):                    return DataType::Real;
        case (BacnetPropertyNS::Description):                     return DataType::CharacterString;
        case (BacnetPropertyNS::DeviceType):                      return DataType::CharacterString;
        case (BacnetPropertyNS::StatusFlags):                     return DataType::BitString;
        case (BacnetPropertyNS::EventState):                      return DataType::Enumerated;
        case (BacnetPropertyNS::Reliability):                     return DataType::Enumerated;
        case (BacnetPropertyNS::OutOfService):                    return DataType::BOOLEAN;
        case (BacnetPropertyNS::Units):                           return DataType::Unsigned;
        case (BacnetPropertyNS::MinPresValue):                    return DataType::Real;
        case (BacnetPropertyNS::MaxPresValue):                      return DataType::Real;
        case (BacnetPropertyNS::Resolution):                        return DataType::Real;
        case (BacnetPropertyNS::CovIncrement):                      return DataType::Real;
        case (BacnetPropertyNS::ProfileName):                       return DataType::CharacterString;

        default: return DataType::InvalidType;
        }
        break;
    case (BacnetObjectTypeNS::BinaryInput):
        switch (propertyId)
        {

        case (BacnetPropertyNS::ObjectIdentifier):                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::ObjectName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ObjectType):                      return DataType::BACnetObjectType;
        case (BacnetPropertyNS::PresentValue):                    return DataType::Enumerated;//this is enumerated!!!! NOT BOOLEAN
        case (BacnetPropertyNS::Description):                     return DataType::CharacterString;
        case (BacnetPropertyNS::DeviceType):                      return DataType::CharacterString;
        case (BacnetPropertyNS::StatusFlags):                     return DataType::BitString;
        case (BacnetPropertyNS::EventState):                      return DataType::Enumerated;
        case (BacnetPropertyNS::Reliability):                     return DataType::Enumerated;
        case (BacnetPropertyNS::OutOfService):                    return DataType::BOOLEAN;
        case (BacnetPropertyNS::Polarity):                          return DataType::Enumerated;
        case (BacnetPropertyNS::InactiveText):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ActionText):                        return DataType::CharacterString;
        case (BacnetPropertyNS::ProfileName):                       return DataType::CharacterString;

        default: return DataType::InvalidType;
        }
        break;
    case (BacnetObjectTypeNS::BinaryOutput):
        switch (propertyId)
        {

        case (BacnetPropertyNS::ObjectIdentifier):                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::ObjectName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ObjectType):                      return DataType::BACnetObjectType;
        case (BacnetPropertyNS::PresentValue):                    return DataType::Enumerated;//this is enumerated!!!! NOT BOOLEAN
        case (BacnetPropertyNS::Description):                     return DataType::CharacterString;
        case (BacnetPropertyNS::DeviceType):                      return DataType::CharacterString;
        case (BacnetPropertyNS::StatusFlags):                     return DataType::BitString;
        case (BacnetPropertyNS::EventState):                      return DataType::Enumerated;
        case (BacnetPropertyNS::Reliability):                     return DataType::Enumerated;
        case (BacnetPropertyNS::OutOfService):                    return DataType::BOOLEAN;
        case (BacnetPropertyNS::Polarity):                          return DataType::Enumerated;
        case (BacnetPropertyNS::InactiveText):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ActionText):                        return DataType::CharacterString;
        case (BacnetPropertyNS::ProfileName):                       return DataType::CharacterString;

        default: return DataType::InvalidType;
        }
        break;
    case (BacnetObjectTypeNS::MultiStateInput):
        switch (propertyId)
        {

        case (BacnetPropertyNS::ObjectIdentifier):                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::ObjectName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ObjectType):                      return DataType::BACnetObjectType;
        case (BacnetPropertyNS::PresentValue):                    return DataType::Unsigned;
        case (BacnetPropertyNS::Description):                     return DataType::CharacterString;
        case (BacnetPropertyNS::DeviceType):                      return DataType::CharacterString;
        case (BacnetPropertyNS::StatusFlags):                     return DataType::BitString;
        case (BacnetPropertyNS::EventState):                      return DataType::Enumerated;
        case (BacnetPropertyNS::Reliability):                     return DataType::Enumerated;
        case (BacnetPropertyNS::OutOfService):                    return DataType::BOOLEAN;
        case (BacnetPropertyNS::NumberOfStates):                    return DataType::Unsigned;
        case (BacnetPropertyNS::ProfileName):                       return DataType::CharacterString;

        default: return DataType::InvalidType;
        }
        break;
    case (BacnetObjectTypeNS::MultiStateOutput):
        switch (propertyId)
        {

        case (BacnetPropertyNS::ObjectIdentifier):                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::ObjectName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ObjectType):                      return DataType::BACnetObjectType;
        case (BacnetPropertyNS::PresentValue):                    return DataType::Unsigned;
        case (BacnetPropertyNS::Description):                     return DataType::CharacterString;
        case (BacnetPropertyNS::DeviceType):                      return DataType::CharacterString;
        case (BacnetPropertyNS::StatusFlags):                     return DataType::BitString;
        case (BacnetPropertyNS::EventState):                      return DataType::Enumerated;
        case (BacnetPropertyNS::Reliability):                     return DataType::Enumerated;
        case (BacnetPropertyNS::OutOfService):                    return DataType::BOOLEAN;
        case (BacnetPropertyNS::NumberOfStates):                    return DataType::Unsigned;
        case (BacnetPropertyNS::ProfileName):                       return DataType::CharacterString;

        default: return DataType::InvalidType;
        }
        break;
    case (BacnetObjectTypeNS::MultiStateValue):
        switch (propertyId)
        {

        case (BacnetPropertyNS::ObjectIdentifier):                return DataType::BACnetObjectIdentifier;
        case (BacnetPropertyNS::ObjectName):                      return DataType::CharacterString;
        case (BacnetPropertyNS::ObjectType):                      return DataType::BACnetObjectType;
        case (BacnetPropertyNS::PresentValue):                    return DataType::Unsigned;
        case (BacnetPropertyNS::Description):                     return DataType::CharacterString;
        case (BacnetPropertyNS::StatusFlags):                     return DataType::BitString;
        case (BacnetPropertyNS::EventState):                      return DataType::Enumerated;
        case (BacnetPropertyNS::Reliability):                     return DataType::Enumerated;
        case (BacnetPropertyNS::OutOfService):                    return DataType::BOOLEAN;
        case (BacnetPropertyNS::NumberOfStates):                    return DataType::Unsigned;
        case (BacnetPropertyNS::ProfileName):                       return DataType::CharacterString;

        default: return DataType::InvalidType;
        }
        break;
    default: return DataType::InvalidType;
    }
}

Bacnet::BacnetDataInterface *BacnetDefaultObject::createDataType(DataType::DataType type)
{
    switch (type)
    {
    case (DataType::Null):                  return new Bacnet::Null();
    case (DataType::BOOLEAN):               return new Bacnet::Boolean();
    case (DataType::Unsigned):              return new Bacnet::UnsignedInteger();
    case (DataType::Signed):                return new Bacnet::SignedInteger();
    case (DataType::Real):                  return new Bacnet::Real();
    case (DataType::Double):                return new Bacnet::Double();
    case (DataType::OctetString):           return new Bacnet::OctetString();
    case (DataType::CharacterString):       return new Bacnet::CharacterString();
    case (DataType::BitString):             return new Bacnet::BitString();
    case (DataType::Enumerated):            return new Bacnet::Enumerated();
    case (DataType::Date):                  return new Bacnet::Date();
    case (DataType::Time):                  return new Bacnet::Time();
    case (DataType::BACnetObjectIdentifier):return new Bacnet::ObjectIdentifier();
    default:
        return new Bacnet::DataAbstract();
    }
}

QList<BacnetPropertyNS::Identifier> Bacnet::BacnetDefaultObject::covProperties(BacnetObjectTypeNS::ObjectType type)
{
    switch (type)
    {
    case (BacnetObjectTypeNS::Device):
        return QList<BacnetPropertyNS::Identifier>() << BacnetPropertyNS::StatusFlags;
    case (BacnetObjectTypeNS::AnalogInput): //fall through
    case (BacnetObjectTypeNS::AnalogOutput): //fall through
    case (BacnetObjectTypeNS::AnalogValue): //fall through
    case (BacnetObjectTypeNS::BinaryInput): //fall through
    case (BacnetObjectTypeNS::BinaryOutput): //fall through
    case (BacnetObjectTypeNS::BinaryValue): //fall through
    case (BacnetObjectTypeNS::MultiStateInput): //fall through
    case (BacnetObjectTypeNS::MultiStateOutput): //fall through
    case (BacnetObjectTypeNS::MultiStateValue):
        return QList<BacnetPropertyNS::Identifier>() << BacnetPropertyNS::StatusFlags <<BacnetPropertyNS::PresentValue;
    default:
        qDebug("%s : CovProperties not set for the object type %d", __PRETTY_FUNCTION__, type);
        Q_ASSERT(false);
        return QList<BacnetPropertyNS::Identifier>();
    }
}

void BacnetDefaultObject::addDefaultProperties(BacnetObjectTypeNS::ObjectType objType, QMap<BacnetPropertyNS::Identifier, BacnetProperty *> &objectProperties)
{
    //if there are already some properties for rhis object, delete them
    if (_properties.contains(objType)) {
        qDeleteAll(_properties[objType]);
    }

    //add new properties
    _properties.insert(objType, objectProperties);
}

BacnetProperty *BacnetDefaultObject::defaultProperty(BacnetObjectTypeNS::ObjectType objType, BacnetPropertyNS::Identifier propId) {
    QMap<BacnetPropertyNS::Identifier, BacnetProperty*> &objDefaultProperties = _properties[objType];
    return objDefaultProperties.value(propId);
}

QMap<BacnetPropertyNS::Identifier, BacnetProperty*> &BacnetDefaultObject::defaultProperties(BacnetObjectTypeNS::ObjectType objType)
{
    return _properties[objType];
}
