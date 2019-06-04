#ifndef VIINPUTCONTEXT_H
#define VIINPUTCONTEXT_H
#include <QRectF>
#include <qpa/qplatforminputcontext.h>
#include "numpad.h"
#include "keyboard.h"

class VIInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    VIInputContext();
    ~VIInputContext();

    bool isValid() const;
    QRectF keyboardRect() const;
    void showInputPanel();
    void hideInputPanel();
    bool isInputPanelVisible() const;
    void setFocusObject(QObject *object);

private:
    QObject * focusObj;
    Numpad * m_numpad;
    Keyboard * m_keyboard;
    QWidget * m_activePanel;
    QString getText();
    void setText(QString);
    void handleInputObject(QObject *obj);
    void updatePosition();

private slots:
    void dataSet(QVariant * data);

};

#endif // VIINPUTCONTEXT_H
