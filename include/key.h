#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QString>
#include <QIcon>
#include <QPainter>
#include <QStyleOptionButton>
#include <QStyle>
#include <QPushButton>

class Key : public QObject {
    Q_OBJECT
    public:
    explicit Key();
    explicit Key(QString t, QObject *parent = nullptr);    // TODO: REMOVE
    explicit Key(QString text, int width = 25, int height = 25, int xPos = 0, int yPos = 0, QObject *parent = nullptr);
    explicit Key(Key &&other) noexcept;    // mctor
    explicit Key(const Key &);             // cctor

    ~Key() override = default;

    Key &operator=(const Key &other);
    Key &operator=(Key &&other) noexcept;

    void setX(int);
    void setY(int);
    void setWidth(int w);
    void setHeight(int h);
    void setIconFile(QString);
    void setPressed(bool b);
    void setCurrent(bool b);

    int getWidth();
    int getHeight();
    int getX();
    int getY();
    QRect getRect();
    QString getText();

    void draw(QPainter *painter, QStyle *s);

    private:
    int mWidth = 25;
    int mHeight = 25;
    int mXPos = 0;
    int mYPos = 0;
    QString mText;
    bool isPressed = false;
    bool isCurrent = false;
    QString iconFilename;
};

#endif    // KEY_H
