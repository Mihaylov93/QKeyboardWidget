#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "keylayout.h"
#include "keyboard.h"

Keyboard::Keyboard(QFile &iJsonFile, InputMode iInputMode, QWidget *iParent) : QStackedWidget(iParent)
{
    // currentKey = nullptr;
    // currentindexkeyboard = 0;

    _keylayout = new KeyLayout(iJsonFile, this);

    foreach (QGridLayout *mLayout, _keylayout->getLayouts()) {
        QWidget *mWidget = new QWidget(this);
        mWidget->setLayout(mLayout->layout());
        this->addWidget(mWidget);
    }
    this->setCurrentIndex(0);
    setFocusPolicy(Qt::StrongFocus);

    this->show();

    switch (iInputMode) {

        case InputMode::Keypad:

            // setKeyCurrent(0, 0);
            Q_FALLTHROUGH();

        case InputMode::Mouse: {
            _inputMode = iInputMode;
            break;
        }
        case InputMode::Mixed:
            throw std::logic_error{"Unimplemented mode"};
        default:
            throw std::logic_error{"Undefined mode, please select a valid mode"};
    }

    Keyboard::connect(_keylayout, SIGNAL(keyPressed(QString)), this, SLOT(onKeyPressed(QString)));
}

void Keyboard::onKeyPressed(const QString &iKey)
{
    QString mLayoutName;
    if (_keylayout->isSwitchKey(iKey, mLayoutName)) {
        this->currentWidget()->hide();
        int idx = _keylayout->getLayoutIndex(mLayoutName);
        setCurrentIndex(idx);

        this->currentWidget()->show();
    }
}
