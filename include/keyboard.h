#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QStackedWidget>
#include <QLabel>
#include <QVector>
#include <QString>

enum InputMode { Undefined, Mouse, Keypad, Mixed };

class KeyLayout;
class Key;
class Keyboard : public QStackedWidget {
    Q_OBJECT

public:
    Keyboard(KeyLayout &kl, InputMode mode = InputMode::Undefined, QStackedWidget *parent = nullptr);
    Key *findKeyFromString(const QString &name, const int &layout);

signals:
    void keyPressed(QString t);
    void backspacePressed();
    void returnPressed();

private:
    Key *currentKey;
    char currentindexkeyboard;
    bool uppercase;

    KeyLayout *mKeylayout;
    InputMode mMode = Undefined;
    QPoint mCurKeyPos = QPoint(-1, -1);
};

#endif    // KEYBOARD_H
