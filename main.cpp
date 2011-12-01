#include <QtCore/QCoreApplication>
#include <QDomDocument>

#include "bacnetvirtuallinklayer.h"
#include "bacnetudptransportlayer.h"
#include "bacnetbiptransportlayer.h"
#include "bacnetnetworklayer.h"
#include "bacnetapplicationlayer.h"

#include "networklayerconfigurator.h"
#include "transportlayerconfigurator.h"
#include "bacnetconfigurator.h" // configures application layer only

#define MAIN_BACNET
#ifdef MAIN_BACNET

static const char *MainConfigFile       = "bacnet-test-config.xml";

static const char *TransportLayerTag    = "transportLayer";
static const char *NetworkLayerTag      = "networkLayer";
static const char *AppLayerTag          = "appLayer";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile f(MainConfigFile);
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug("Can't open a config file %s!", MainConfigFile);
        return 1;
    }
    QDomDocument doc;
    if (!doc.setContent(&f)) {
        qDebug("Main config (%s) is malformed", MainConfigFile);
        return 2;
    }

    //start CMD initialization

    QDomElement mainElement = doc.documentElement();
    QDomElement element;

    //configure network layer
    element = mainElement.firstChildElement(NetworkLayerTag);
    BacnetNetworkLayerHandler *networkLayer = Bacnet::NetworkLayerConfigurator::createNetworkLayer(element);
    Q_CHECK_PTR(networkLayer);
    if (0 == networkLayer) {
        qDebug("Network layer was not created, terminate!");
        return 3;
    }

    element = mainElement.firstChildElement(TransportLayerTag);
    BacnetTransportLayerHandler *transportBipLayer = Bacnet::TransportLayerConfigurator::createTransportLayer(networkLayer, element);
    if (0 == transportBipLayer) {
        qDebug("Transport layer was not created, terminate!");
        return 3;
    }
    Q_CHECK_PTR(transportBipLayer);

    element = mainElement.firstChildElement(AppLayerTag);
    Bacnet::BacnetApplicationLayerHandler *appLayer = Bacnet::BacnetConfigurator::createApplicationLayer(networkLayer, element);
    if (0 == appLayer) {
        qDebug("Application layer was not created, terminate!");
        return 3;
    }
    Q_CHECK_PTR(appLayer);

    //finish CDM initialization

    return a.exec();
}

#endif
