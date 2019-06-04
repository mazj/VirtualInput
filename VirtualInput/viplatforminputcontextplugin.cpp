#include "viplatforminputcontextplugin.h"
#include "viinputcontext.h"
#include <QDebug>


QPlatformInputContext *VIPlatformInputContextPlugin::create(const QString& system, const QStringList& paramList)
{
    Q_UNUSED(paramList);
    d=0;

    qDebug() << "Plugin: " << system;
    if (system.compare(system, QStringLiteral("virtualinput"), Qt::CaseInsensitive) == 0)
    {
        d = new VIInputContext();
        return d;
    }
    return 0;
}




