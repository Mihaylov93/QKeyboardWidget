#include "key.h"

Key::Key() : mWidth(25),mHeight(25),
    mXPos(10), mText(QString()), isPressed(false)
{

}

Key::Key(QString t,QObject *parent) : QObject(parent) ,mText(t) //TODO: REMOVE
{
  mWidth = mText.length()*5 + 20;
  mHeight = 25;
}

Key::Key(QString t, int w, int h, QObject *parent) : QObject(parent), mHeight(h), mText(t)
{
    mWidth = mText.length()+w;
}

Key::Key(Key && other)
    : mWidth(other.mWidth),mHeight(other.mHeight), mXPos(other.mXPos), mText(other.mText), isPressed(other.isPressed)
{
    //Leave it in a default state
    other.mWidth = 25;
    other.mHeight = 25;
    other.mXPos = 10;
    other.mYPos = 10;
    other.mText = QString();
    other.isPressed = false;
}

Key::Key(const Key &other )
    : QObject(nullptr), mWidth(other.mWidth),mHeight(other.mHeight),
    mXPos(other.mXPos), mText(other.mText), isPressed(other.isPressed)
{

}

QRect Key::getRect()
{
    return QRect(mXPos,mYPos,mWidth,mHeight);
}

void Key::setWidth(int w)
{
    mWidth = w;
}

void Key::setHeight(int h)
{
    mHeight = h;
}

int Key::getWidth()
{
    return mWidth;
}

int Key::getHeight()
{
    return mHeight;
}

int Key::getX()
{
    return mXPos;
}

int Key::getY()
{
    return mYPos;
}

QString Key::getText()
{
    return mText;
}

void Key::setX(int x)
{
  mXPos = x;
}


void Key::setY(int y)
{
  mYPos = y;
}


void Key::setIconFile(QString i )
{
  iconFilename = i;
  //mWidth = 25;
}

void Key::setPressed( bool b)
{
   isPressed = b;
}

void Key::draw(QPainter *p,QStyle *style) {

    QStyleOptionButton btnStyle;


    isPressed ? btnStyle.state = QStyle::State_Enabled : btnStyle.state = QStyle::State_Active;

    btnStyle.rect = QRect(mXPos, mYPos, mWidth, mHeight);

    if ( iconFilename !="" )
    {
        btnStyle.icon = QIcon(iconFilename);
        btnStyle.iconSize=QSize(16,16);
    }
    else
        btnStyle.text = mText;

    style->drawControl(QStyle::CE_PushButton, &btnStyle, p);

}
