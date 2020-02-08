#include "key.h"
#include <QFont>
#include <QResizeEvent>
Key::Key(const QString &iText, const QString &iIcon, const int &iMinWidth, const int &iMinHeight, QWidget *iParent) :
    QPushButton(iParent)
{

    this->setObjectName(iText);

    if (iIcon.size()) {
        this->setIcon(QIcon(QPixmap(iIcon)));
    } else {
        this->setText(iText);
    }

    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setMinimumSize(iMinWidth, iMinHeight);
    this->resize(iMinWidth, iMinHeight);
    connect(this, &QPushButton::clicked, this, &Key::on_clicked);
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

void Key::resizeEvent(QResizeEvent *iEvent)
{
    QPushButton::resizeEvent(iEvent);

    computeNewFontSize(*this);
}

void Key::computeNewFontSize(Key &ioKey)
{
    QFont mFont;

    qreal mOldFontSize; qreal mNewFontSize;

    mOldFontSize = ioKey.font().pointSizeF();

    const int h = ioKey.rect().height() - 8;
    const int w = ioKey.rect().width() - 8;
    qreal step = 0.5;
    for (int i = 0; i < 2; i++) {
        QRect textRect = ioKey.fontMetrics().boundingRect(ioKey.text());

        if (textRect.height() < h && textRect.width() < w) {
            mNewFontSize = mOldFontSize += step;
            if (mNewFontSize > 0) mFont.setPointSizeF(mNewFontSize);
            ioKey.setFont(mFont);
            mOldFontSize = mNewFontSize;
        }
    }
    mOldFontSize -= step;    // use the size before we didnt fit
    mFont.setPointSizeF(mOldFontSize);
    ioKey.setFont(mFont);
}
