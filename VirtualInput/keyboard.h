#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QtDesigner/QDesignerExportWidget>
#include <QDialog>
#include <QLineEdit>

namespace Ui {
    class Keyboard;
}

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget *parent = 0);
    ~Keyboard();

    void activate(QVariant initValue,int maxChars,bool multiLine=false);
    void setEchoMode(QLineEdit::EchoMode);
    void setValidator(const QValidator *);
private slots:
    void buttonClicked();
    void shiftClicked();
    void capsClicked();
    void enterClicked();
    void okClicked();
    void escapeClicked();
    void spaceClicked();
    void clearClicked();
    void tabClicked();
    void backspaceClicked();
    void leftClicked();
    void rightClicked();
private:
    Ui::Keyboard *ui;
    QObjectList keyList;
    bool shift,caps, multiLine;
    void initKeys();
    void popData();
    void morphKeys();
    void addText(QString text);

signals:
    void dataSet(QVariant *);
};

#endif // KEYBOARD_H
