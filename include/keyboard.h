#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QStackedWidget>
#include <QString>
#include <QFile>
enum InputMode { Undefined, Mouse, Keypad, Mixed };

class KeyLayout;
// class Key;
class Keyboard : public QStackedWidget {
    Q_OBJECT

public:
    explicit Keyboard(QFile &iJsonFile, InputMode iInputMode = InputMode::Undefined, QWidget *iParent = nullptr);

    // Key *findKeyFromString(const QString &name, const int &layout);

    /*protected:
        void mouseMoveEvent(QMouseEvent *e) override;*/
signals:

    void keyPressed(QString t);
    void backspacePressed();
    void returnPressed();

private slots:
    void onKeyPressed(const QString &iKey);

private:
    // Key *currentKey;
    // char currentindexkeyboard;

    KeyLayout *_keylayout;
    InputMode _inputMode = Undefined;
};

#endif    // KEYBOARD_H
