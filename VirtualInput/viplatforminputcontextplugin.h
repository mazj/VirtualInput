#ifndef VIPLATFORMINPUTCONTEXTPLUGIN_H
#define VIPLATFORMINPUTCONTEXTPLUGIN_H

#include "virtualinput_global.h"
#include <qpa/qplatforminputcontextplugin_p.h>

class VIRTUALINPUTSHARED_EXPORT VIPlatformInputContextPlugin: public QPlatformInputContextPlugin
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QPlatformInputContextFactoryInterface" FILE "virtualinput.json")
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "virtualinput.json")

public:
    QPlatformInputContext *create(const QString&, const QStringList&);

private:
    QPlatformInputContext * d;
};


#endif // VIPLATFORMINPUTCONTEXTPLUGIN_H
