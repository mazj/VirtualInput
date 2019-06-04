#include "keyboard.h"
#include "ui_keyboard.h"
#include <QMessageBox>

Keyboard::Keyboard(QWidget *parent) :
    QWidget(0, Qt::Tool | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(),this->height());
    shift=false;
    caps=false;
    keyList=ui->keyholder->children();
    initKeys();
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::initKeys()
{
    QPushButton *button;

    for(int i=0;i<keyList.count();i++)
    {
        button=qobject_cast<QPushButton *>(keyList.at(i));
        if(button != 0)
        {
            if((button->property("btnMode").toInt() == 0) || (button->property("btnMode").toInt() == 1))
            {
                connect(button,SIGNAL(clicked()),this,SLOT(buttonClicked()));
            }
            else if(button->property("btnMode").toInt() == 2)
            {
                if(button->property("btnNormal")=="shift")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(shiftClicked()));
                }
                else if(button->property("btnNormal")=="caps")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(capsClicked()));
                }
                else if(button->property("btnNormal")=="enter")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(enterClicked()));
                }
                else if(button->property("btnNormal")=="ok")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(okClicked()));
                }
                else if(button->property("btnNormal")=="escape")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(escapeClicked()));
                }
                else if(button->property("btnNormal")=="space")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(spaceClicked()));
                }
                else if(button->property("btnNormal")=="clear")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(clearClicked()));
                }
                else if(button->property("btnNormal")=="tab")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(tabClicked()));
                }
                else if(button->property("btnNormal")=="backspace")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(backspaceClicked()));
                }
                else if(button->property("btnNormal")=="left")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(leftClicked()));
                }
                else if(button->property("btnNormal")=="right")
                {
                    connect(button,SIGNAL(clicked()),this,SLOT(rightClicked()));
                }
            }
        }

    }
}

void Keyboard::buttonClicked()
{
    QPushButton *tmp;
    tmp = qobject_cast<QPushButton *>(sender());
    if (tmp->text() == "&&") //stupid exeption & is used for shortkeys
    {
        addText("&");
    }
    else
    {
        addText(tmp->text());
    }
    if(shift == true)
    {
        shift=false;
        morphKeys();
    }
}

void Keyboard::shiftClicked()
{
    shift^=true;
    morphKeys();
}

void Keyboard::capsClicked()
{
    shift=false;
    caps^=true;
    morphKeys();
}

void Keyboard::enterClicked()
{
    if(multiLine)
    {
        addText("\n");;
    }
    else
    {
        popData();
    }
}

void Keyboard::okClicked()
{
    popData();
}


void Keyboard::morphKeys()
{
    QPushButton *button;
    for(int i=0;i<keyList.count();i++)
    {
        button=qobject_cast<QPushButton *>(keyList.at(i));
        if(button != 0)
        {
            if (button->property("btnMode").toInt() == 0)
            {
                if (caps || shift)
                {
                    button->setText(button->property("btnShift").toString());
                }
                else
                {
                    button->setText(button->property("btnNormal").toString());
                }
            }
            if (button->property("btnMode").toInt() == 1)
            {
                if (shift)
                {
                    button->setText(button->property("btnShift").toString());
                }
                else
                {
                    button->setText(button->property("btnNormal").toString());
                }
            }
        }
    }
}

void Keyboard::escapeClicked()
{
    close();
}

void Keyboard::spaceClicked()
{
    addText(" ");
}

void Keyboard::clearClicked()
{
    ui->edValue->clear();
}

void Keyboard::tabClicked()
{
    addText("\t");
}

void Keyboard::backspaceClicked()
{
    int tmpPos=ui->edValue->cursorPosition();
    if(tmpPos >0)
    {
        QString text,left,right;
        text=ui->edValue->text();
        if(tmpPos == 1)
        {
            text=text.right(text.length()-1);
        }
        else if(tmpPos < text.length())
        {
            left = text.left(tmpPos-1);
            right = text.right(text.length()-tmpPos);
            text = left+right;
        }
        else
        {
            text.chop(1);
        }
        ui->edValue->setText(text);
        ui->edValue->setCursorPosition(tmpPos-1);
    }
}

void Keyboard::popData()
{

    emit dataSet(&QVariant(ui->edValue->text()));
    close();
}

void Keyboard::activate(QVariant initValue,int maxChars,bool multiLine)
{
    this->multiLine=multiLine;
    ui->edValue->setMaxLength(maxChars);
    ui->edValue->setText(initValue.toString());
    show();
    //ui->edValue->setFocus();
    //activateWindow();
}

void Keyboard::setEchoMode(QLineEdit::EchoMode echoMode)
{
    ui->edValue->setEchoMode(echoMode);
}

void Keyboard::setValidator(const QValidator *validator)
{
    ui->edValue->setValidator(validator);
}

void Keyboard::addText(QString text)
{
    QString tmpStr;
    int tmpPos;
    tmpStr=ui->edValue->text();
    tmpPos=ui->edValue->cursorPosition();
    tmpStr.insert(tmpPos,text);
    ui->edValue->setText(tmpStr);
    ui->edValue->setCursorPosition(tmpPos+1);
}
void Keyboard::leftClicked()
{
    ui->edValue->cursorBackward(false);
}

void Keyboard::rightClicked()
{
    ui->edValue->cursorForward(false);
}
