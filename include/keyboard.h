#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QString>

enum InputMode { Undefined, Mouse, Keypad, Mixed };

class KeyLayout;
class Key;
class Keyboard : public QWidget {
    Q_OBJECT

    public:
    Keyboard(KeyLayout &kl, InputMode mode = InputMode::Undefined, QWidget *parent = nullptr);
    Key *findKeyFromString(const QString &name, const int &layout);

    signals:
    void keyPressed(QString t);
    void backspacePressed();
    void returnPressed();

    private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    Key *findKey(QPoint p);

    void setKeyPressed(Key *k);
    void setKeyCurrent(int row = -1, int col = -1);

    QVector<QVector<Key>> *rows;

    Key *currentKey;
    char currentindexkeyboard;
    bool uppercase;

    KeyLayout *mKeylayout;
    InputMode mMode = Undefined;
    QPoint mCurKeyPos = QPoint(-1, -1);
};

#endif    // KEYBOARD_H
