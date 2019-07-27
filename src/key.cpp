#include "key.h"

#include <utility>

Key::Key() : mText(QString())
{
}

Key::Key(QString t, QObject *parent) : QObject(parent), mText(std::move(t))    // TODO: REMOVE
{
    mWidth = mText.length() * 5 + 20;
    mHeight = 25;
}

Key::Key(QString t, int w, int h, int xPos, int yPos, QObject *parent) :
    QObject(parent), mHeight(h), mXPos(xPos), mYPos(yPos), mText(std::move(t))
{
    mWidth = mText.length() * 5 + w;
}

Key::Key(Key &&other) noexcept :
    mWidth(other.mWidth), mHeight(other.mHeight), mXPos(other.mXPos), mYPos(other.mYPos), mText(QString(other.mText)),
    isPressed(other.isPressed), isCurrent(other.isCurrent)
{
    // Leave it in a default state
    other.setParent(nullptr);
    other.mWidth = 25;
    other.mHeight = 25;
    other.mXPos = 0;
    other.mYPos = 0;
    other.mText = QString();
    other.isPressed = false;
    other.isCurrent = false;
}

Key::Key(const Key &other) :
    QObject(other.parent()), mWidth(other.mWidth), mHeight(other.mHeight), mXPos(other.mXPos), mYPos(other.mYPos),
    mText(other.mText), isPressed(other.isPressed), isCurrent(other.isCurrent)
{
}

Key &Key::operator=(const Key &other)
{
    this->setParent(other.parent());
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mXPos = other.mXPos;
    mYPos = other.mYPos;
    mText = other.mText;
    isPressed = other.isPressed;
    isCurrent = other.isCurrent;

    return *this;
}

Key &Key::operator=(Key &&other) noexcept
{
    if (this != &other) {
        this->setParent(other.parent());
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        mXPos = other.mXPos;
        mYPos = other.mYPos;
        mText = other.mText;
        isPressed = other.isPressed;
        isCurrent = other.isCurrent;

        other.setParent(nullptr);
    }

    return *this;
}

QRect Key::getRect()
{
    return {QPoint(mXPos, mYPos), QSize(mWidth, mHeight)};
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

void Key::setIconFile(QString i)
{
    iconFilename = std::move(i);
}

void Key::setPressed(bool b)
{
    isPressed = b;
}

void Key::setCurrent(bool b)
{
    isCurrent = b;
}

void Key::draw(QPainter *p, QStyle *style)
{

    QStyleOptionButton btnStyle;

    // isPressed ? btnStyle.state = btnStyle.state = QStyle::State_Enabled : btnStyle.state = QStyle::State_Active;
    isCurrent ? btnStyle.state = btnStyle.state |= QStyle::State_Enabled | QStyle::State_On
              : btnStyle.state = QStyle::State_Active;

    btnStyle.rect = QRect(QPoint(mXPos, mYPos), QSize(mWidth, mHeight));

    if (iconFilename != "") {
        btnStyle.icon = QIcon(iconFilename);
        btnStyle.iconSize = QSize(16, 16);
    } else
        btnStyle.text = mText;

    // style->drawControl(QStyle::CE_PushButton, &btnStyle, p,this);
    style->drawControl(QStyle::CE_PushButton, &btnStyle, p);
}
