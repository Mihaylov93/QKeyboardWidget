#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QString>
#include <QIcon>
#include <QPainter>
#include <QStyleOptionButton>
#include <QStyle>


class Key : public QObject
{
    Q_OBJECT
public:
    explicit Key();
    explicit Key(QString t,QObject *parent = nullptr); // TODO: REMOVE
    explicit Key(QString text,int width = 25, int height = 25, QObject *parent = nullptr);
    explicit Key(Key&& other); //mctor
    explicit Key(const Key&); //cctor

    QString iconFilename;

    void setX(int);
    void setY(int);
    void setWidth(int w);
    void setHeight(int h);
    void setIconFile(QString );
    void setPressed( bool b);

    int getWidth();
    int getHeight();
    int getX();
    int getY();
    QRect getRect();
    QString getText();

    void draw(QPainter *painter,QStyle *s);

private:
    int mWidth = 25;
    int mHeight = 25;
    int mXPos = 10;
    int mYPos = 10;
    QString mText;
    bool isPressed = false;
};

#endif // KEY_H
