#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "keyboard.h"
#include "keylayout.h"

Keyboard::Keyboard(KeyLayout &kl, InputMode mode, QWidget *parent) : QWidget (parent)
{
    currentKey = nullptr;
    currentindexkeyboard = 0;
    uppercase = false;

    rows = kl.getRows(currentindexkeyboard);

    mKeylayout = &kl;

    setFocusPolicy(Qt::StrongFocus);
    switch (mode) {

        case InputMode::Keypad :

            setKeyCurrent(0,0);
            Q_FALLTHROUGH();

        case InputMode::Mouse : {
            mMode = mode;
            break;
        }
        case InputMode::Mixed : throw std::logic_error{"Unimplemented mode"};
        default : throw std::logic_error{"Undefined mode, please select a valid mode"};
    }
}

void Keyboard::mousePressEvent(QMouseEvent * e) {

    if (mMode == InputMode::Mouse){
        QPoint pos = e->pos();

        Key *key = findKey(pos);
        if (key != nullptr) setKeyPressed(key);
    }else{
        e->ignore();
    }

}

void Keyboard::mouseMoveEvent(QMouseEvent * e) {

    if (mMode == InputMode::Mouse){
        QPoint pos = e->pos();

        if (currentKey != nullptr && !currentKey->getRect().contains(pos)) {

            currentKey->setPressed(false);
            this->repaint();
        }
        setKeyPressed(findKey(pos));
    }else {
        e->ignore();
    }

 }

void Keyboard::mouseReleaseEvent(QMouseEvent *e) {

    if (mMode == InputMode::Mouse){
        QPoint pos = e->pos();

        Key *k= findKey( pos );
        if (k == nullptr) return; // TODO: FIX
        k->setPressed(false);
        if (mKeylayout->isModifier(k->getText())){
            currentindexkeyboard = mKeylayout->getLayoutIdxFromKey(k->getText());
            rows = mKeylayout->getRows(currentindexkeyboard);
            repaint();
            return;
        }
        this->repaint();
    }else {
        e->ignore();
    }


}

void Keyboard::keyReleaseEvent(QKeyEvent *event)
{
    if (mMode == InputMode::Keypad){
        switch (event->key()) {
            case Qt::Key_Left : qDebug() << "left released";
                if (mCurKeyPos.y() == 0) setKeyCurrent(mCurKeyPos.x(),rows->at(mCurKeyPos.x()).size()-1);
                else setKeyCurrent(mCurKeyPos.x(),mCurKeyPos.y()-1);
                this->repaint();
                break;
            case Qt::Key_Right : qDebug() << "Right released";
                if (mCurKeyPos.y() == rows->at(mCurKeyPos.x()).size()-1) setKeyCurrent(mCurKeyPos.x(),0);
                else setKeyCurrent(mCurKeyPos.x(),mCurKeyPos.y()+1);
                this->repaint();
                break;
            case Qt::Key_Up : qDebug() << "Up released";
                if (mCurKeyPos.x() == 0) setKeyCurrent(rows->size()-1,mCurKeyPos.y());
                else setKeyCurrent(mCurKeyPos.x()-1,mCurKeyPos.y());
                this->repaint();
                break;
            case Qt::Key_Down : qDebug() << "Down released";
                if (mCurKeyPos.x() == rows->size()-1) setKeyCurrent(0,mCurKeyPos.y());
                else setKeyCurrent(mCurKeyPos.x()+1,mCurKeyPos.y());
                this->repaint();
                break;
            default:
                qWarning() << "Unspecified key " << event->key() << "pressed";
        }
    }else{
        event->ignore();
    }

}
Key *Keyboard::findKey(QPoint p)
{

    for (auto keyArrayIt = rows->begin();keyArrayIt != rows->end();++keyArrayIt){
        for (auto it = keyArrayIt->begin();it != keyArrayIt->end(); ++it) {
            qDebug() << it->getRect();
            qDebug() << it->getX() << " , " << it->getY();;
            if (it->getRect().contains(p)){
                qDebug() << "key found";
                return it;
            }
        }
    }

    return nullptr;
}

void Keyboard::setKeyPressed(Key *k)
{
    currentKey = k;


    k->setPressed(true);
    this->repaint();
}

void Keyboard::setKeyCurrent(int row, int col)
{

    // TODO: Manage out of bond
    // Managed externally currently
    if (currentKey != nullptr)currentKey->setCurrent(false);

    mCurKeyPos.setX(row);
    mCurKeyPos.setY(col);

    auto rowIt = rows->begin();
    for (int r = 0;r<row;r++) {
        ++rowIt;
    }

    auto colIt = rowIt->begin();
    for (int c = 0;c<col;c++) {
        ++colIt;
    }

    currentKey = colIt;
    currentKey->setCurrent(true);
    this->repaint();
}

void Keyboard::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    for (auto it = rows->begin();it != rows->end(); ++it) {
        for (auto key = it->begin();key != it->end(); ++key) {
            //qDebug() << "Keyboard::Draw Drawing key << " << key->getText() << "at: "<< key->getRect();
            key->draw(&painter,style());
        }
    }
}
