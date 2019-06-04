#include "VIInputContext.h"
#include <QDebug>
#include <QEvent>
#include <QGuiApplication>
#include <QDebug>
#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>
#include <QValidator>
#include <QApplication>
#include <QDesktopWidget>

//#include "mockupkeyeventdispatcher.h"


VIInputContext::VIInputContext() :
    QPlatformInputContext()
{
    qDebug() << "created";
    m_keyboard = 0;
    m_numpad = 0;
    m_activePanel = 0;
}

VIInputContext::~VIInputContext()
{
    if(m_numpad)
        delete m_numpad;
    if(m_keyboard)
        delete m_keyboard;
}

bool VIInputContext::isValid() const
{
    return true;
}

QRectF VIInputContext::keyboardRect() const
{
    if(m_activePanel)
        return QRectF(m_activePanel->geometry());
    else
        return QRectF();
}

void VIInputContext::showInputPanel()
{
    qDebug() << "show";
    if(!m_numpad)
    {
        m_numpad = new Numpad();
        connect(m_numpad,SIGNAL(dataSet(QVariant*)),this,SLOT(dataSet(QVariant *)));
    }
    if(!m_keyboard)
    {
        m_keyboard = new Keyboard();
        connect(m_keyboard,SIGNAL(dataSet(QVariant*)),this,SLOT(dataSet(QVariant *)));
    }
    handleInputObject(focusObj);
}

void VIInputContext::hideInputPanel()
{
    if(m_numpad)
        m_numpad->hide();
    if(m_keyboard)
        m_keyboard->hide();
}

bool VIInputContext::isInputPanelVisible() const
{
    return m_keyboard->isVisible() | m_numpad->isVisible();
}


void VIInputContext::setFocusObject(QObject *object)
{
    focusObj = object;

    QWidget * tmp = qobject_cast<QWidget *>(object);
    if(tmp)
    {
        qDebug() << tmp->inputMethodQuery(Qt::ImSurroundingText);
        qDebug() << tmp->inputMethodHints();
    }



    //qDebug() << object->metaObject()->className();
    //d->keyEventDispatcher.setFocusItem(object);
}

QString VIInputContext::getText()
{

    if (dynamic_cast<QLineEdit *>(focusObj))
    {
        return dynamic_cast<QLineEdit *>(focusObj)->text();
    }
    else
    {
        return "";
    }
}

void VIInputContext::setText(QString text)
{
    if (dynamic_cast<QLineEdit *>(focusObj))
    {
        dynamic_cast<QLineEdit *>(focusObj)->setText(text);
    }
}

void VIInputContext::handleInputObject(QObject *obj)
{
    if (obj != NULL)
    {
        if (obj->property("enabled").toBool())
        {
            if (obj->property("keyboard").toBool())
            {
                if (dynamic_cast<QLineEdit *>(obj))
                {
                    const QValidator * tmpValidator = dynamic_cast<QLineEdit *>(obj)->validator();
                    if (qobject_cast<const QDoubleValidator *>(tmpValidator) || qobject_cast<const QIntValidator *>(tmpValidator))
                    {
                        updatePosition();
                        m_numpad->activate(getText(),static_cast<QLineEdit *>(obj)->validator());
                        m_numpad->setEchoMode(dynamic_cast<QLineEdit *>(obj)->echoMode());
                    }
                    else
                    {
                        updatePosition();
                        m_keyboard->activate(getText(),obj->property("maxLength").toInt(),false);
                        m_keyboard->setEchoMode(dynamic_cast<QLineEdit *>(obj)->echoMode());
                        m_keyboard->setValidator(dynamic_cast<QLineEdit *>(obj)->validator());
                    }
                }
            }
        }
    }
}

void VIInputContext::dataSet(QVariant * data)
{
    setText(data->toString());
}


void VIInputContext::updatePosition()
{
    QRect screenGeo = QApplication::desktop()->screenGeometry();
    QRect keyGeo = m_keyboard->geometry();
    QRect numGeo = m_numpad->geometry();


    m_keyboard->move(QPoint((screenGeo.width()/2)-(keyGeo.width()/2),(screenGeo.height()/2)-(keyGeo.height()/2)));
    m_numpad->move(QPoint((screenGeo.width()/2)-(numGeo.width()/2),(screenGeo.height()/2)-(numGeo.height()/2)));
}
