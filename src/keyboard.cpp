#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "key.h"
#include "keylayout.h"
#include "keyboard.h"

Keyboard::Keyboard(KeyLayout &kl, InputMode mode, QStackedWidget *parent) : QStackedWidget(parent)
{
    currentKey = nullptr;
    currentindexkeyboard = 0;

    // mLayouts = kl.getLayoutAt(currentindexkeyboard);

    mKeylayout = &kl;

    setFocusPolicy(Qt::StrongFocus);
    switch (mode) {

        case InputMode::Keypad:

            // setKeyCurrent(0, 0);
            Q_FALLTHROUGH();

        case InputMode::Mouse: {
            mMode = mode;
            break;
        }
        case InputMode::Mixed:
            throw std::logic_error{"Unimplemented mode"};
        default:
            throw std::logic_error{"Undefined mode, please select a valid mode"};
    }
}
