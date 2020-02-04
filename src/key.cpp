#include "key.h"

Key::Key(const QString &iText, const QString &iIcon, const int &iMinWidth, const int &iMinHeight, QWidget *iParent) :
    QPushButton(iParent)
{
    this->setText(iText);
    this->setObjectName(iText);

    if (iIcon.size()) {
        this->setIcon(QIcon(QPixmap(iIcon)));
    }

    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setMinimumSize(iMinWidth, iMinHeight);
    this->resize(iMinWidth, iMinHeight);
    QObject::connect(this, &QPushButton::clicked, this, &Key::on_clicked);
}

const bool &Key::isPressed() const
{
    return _isPressed;
}

void Key::setPressed(const bool &iState)
{
    _isPressed = iState;
}

const bool &Key::isCurrent() const
{
    return _isCurrent;
}

void Key::setCurrent(const bool &iState)
{
    _isCurrent = iState;
}

int Key::getWidth() const
{
    return this->QWidget::width();
}

void Key::setWidth(const int &iWidth)
{
    this->resize(iWidth, this->QWidget::height());
}

int Key::getHeight() const
{
    return this->QWidget::height();
}

void Key::setHeight(const int &iHeight)
{
    this->resize(this->QWidget::width(), iHeight);
}
