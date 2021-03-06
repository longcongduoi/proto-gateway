#ifndef COVSUPPORT_H
#define COVSUPPORT_H

#include "bacnetcovsubscription.h"


namespace Bacnet {
    class BacnetObject;
    class BacnetDeviceObject;
    class Error;

    typedef QSharedPointer<Bacnet::CovSubscription> CovSubscriptionShared;

class CovSupport
{
public:
    //so far this is not compulsory. Function returns 0 on default, if not supported.
    virtual const QList<BacnetPropertyNS::Identifier> covProperties() = 0;

public:
    CovSupport();
    ~CovSupport();

    void addOrUpdateCovSubscription(Bacnet::SubscribeCOVServiceData &covData, BacnetAddress &requester, Bacnet::Error *error);
    void rmCovSubscription(quint32 processId, BacnetAddress &requester, Bacnet::ObjectIdentifier &monitoredObjectId, Bacnet::PropertyReference &propReference, Bacnet::Error *error);
    QList<CovSubscriptionShared> &covSubscriptions();

    //! \note If the value is of real type, increment handler visits it to check if notification of subscribers is needed. Otherwise, notification is needed (because CDM invokes other functions
    //  only if change occured.
//    bool valueChanged(BacnetPropertyNS::Identifier propId, BacnetDataInterface *value);

    //! Adds new increment handler. The ownership is transferred to this class!
    void addCovIncrementHandler(BacnetPropertyNS::Identifier propId, CovRealIcnrementHandler *incrementHandler);
    //! Returns increment handler for given property. If not present - returns 0. This class still owns the increment handler.
    CovRealIcnrementHandler *covIncrementHandler(BacnetPropertyNS::Identifier propId);
    //! Returns increment handler for given property. If not present - returns 0. This method transfers ownership to the caller!
    CovRealIcnrementHandler *takeCovIncrementHandler(BacnetPropertyNS::Identifier propId);
    //! Remove increment handler. Returns true, if the property had increment handler. Otherwise false.
    void remvoeCovIncrementHandler(BacnetPropertyNS::Identifier propId);

    void propertyChanged(BacnetPropertyNS::Identifier propId, quint32 propArrayIdx, BacnetObject *notifyingObject, BacnetDeviceObject *deviceToNotify);

    /** Method to execute time dependant operations, like unsubscription of unused elements. Returns true, if instance still needs time dependant invocations, otherwise false.
        If returned false, then to be timely invoked again, instance has to subscribe with CovSupportTimeHandler using its addCovSupporter() method.
      */
    bool timeout(quint32 timePassed_s);

private:
    void updateWithTimeHandlerHelper();
    bool hasTimeVariantSubscription();

protected:
    QList<CovSubscriptionShared> _subscriptions;
    QHash<BacnetPropertyNS::Identifier, CovRealIcnrementHandler*> _incrementHandlers;
};




//    /////////////////////////////////////////////////////
//    ///////////////CovSupport interface//////////////////
//    /////////////////////////////////////////////////////
//    class CovSupport
//    {
//    public:
//        virtual bool hasChangeOccured(QVariant &actualValue) = 0;
//        virtual void setCovIncrement(BacnetDataInterface *newIncrement) = 0;
//        virtual BacnetDataInterface *covIncrement() = 0;
//    };

//    /////////////////////////////////////////////////////
//    ///////////////////ConcreteCovSupport//////////////////
//    /////////////////////////////////////////////////////
//    template <typename T, class T2>
//            class ConcreteCovSupport:
//            public CovSupport
//    {
//    public:
//        ConcreteCovSupport(T covIncrement, T lastValue = 0);
//        void setCovIncrement(T covIncrement);

//    public://overriden from CovSupport
//        virtual bool hasChangeOccured(QVariant &actualValue);
//        virtual void setCovIncrement(BacnetDataInterface *newIncrement);
//        virtual BacnetDataInterface *covIncrement();

//    private:
//        T _lastValue;
//        T2 _covIncrement;
//    };

//    template <typename T>
//            T toT(QVariant v, bool *ok)
//    {
//        Q_ASSERT_X(false, "covsupport.h", "Not implemented concretization");
//        return T();
//    };

//    //specialized functions
//    template <> inline
//            float toT<float>(QVariant v, bool *ok) {return v.toFloat(ok);}

//    template <> inline
//            double toT<double>(QVariant v, bool *ok) {return v.toDouble(ok);}


//    typedef ConcreteCovSupport<float, Bacnet::Real> RealCovSupport;
//    typedef ConcreteCovSupport<double, Bacnet::Double> DoubleCovSupport;
}
#endif // COVSUPPORT_H
