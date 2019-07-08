#include "keylayout.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


KeyLayout::KeyLayout(QString json, QObject *parent) : QObject(parent)
{
    Q_ASSERT(!json.isNull() && !json.isEmpty());
    QJsonParseError error;
    jsonObject = QJsonDocument::fromJson(json.toUtf8(),&error).object();

    if (Q_UNLIKELY(error.error != 0))
        qDebug() << error.errorString();

    this->init();
}

KeyLayout::KeyLayout(QFile *file, QObject *parent) : QObject(parent)
{

    QJsonParseError error;
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug() << file->isReadable();
    // Could happen that you open it and its not readable and the assert breaks without closing.
    // This hack prevents that with the same goal.
    if (!file->isReadable())Q_ASSERT(0);

    QByteArray json = file->readAll();
    jsonObject = QJsonDocument::fromJson(json,&error).object();
    file->close();

    if (Q_UNLIKELY(error.error != 0))
        qDebug() << error.errorString();

    this->init();
}

KeyLayout::~KeyLayout()
{
    // layouts;
    //layouts = nullptr;
}

QString KeyLayout::getLocale()
{
    return mLocale;
}

const QVector<QVector< QVector<Key>>>& KeyLayout::getLayouts()
{
    return layouts;
}

QVector< QVector<Key>> KeyLayout::getRows(char layout)
{
    return layouts[layout];
}

QJsonValue KeyLayout::getQJsonValue(QJsonObject obj, QString key, Type type)
{
    Q_ASSERT(!obj.isEmpty());
    QJsonValue value = obj.value(key);
    switch(type)
    {
        case Type::Array : 
            Q_ASSERT(value.isArray());
             break;
        case Type::String : 
            Q_ASSERT(value.isString());
            break;
        default:
            return value;
    }
    
    return value;
        
}

void KeyLayout::init()
{

    mLocale = jsonObject.value(QString("locale")).toString();
    mWidth = getQJsonValue(jsonObject,"width",Type::Null).toString().toInt();
    mHeight = getQJsonValue(jsonObject,"height",Type::Null).toString().toInt();

    QJsonValue value = getQJsonValue(jsonObject,"layouts",Type::Array);
    QJsonArray layouts = value.toArray();

    foreach (const QJsonValue & val, layouts) {
        QJsonObject jsonObj = val.toObject();
        layoutNames.append(getQJsonValue(jsonObj, "name", Type::String).toString());
        
        QJsonValue kbdsVal = getQJsonValue(jsonObj, "keys", Type::Array);




    }
    this->layouts.append(this->initLayouts(value.toArray()));

}

QVector<QVector<Key>> KeyLayout::initLayouts(const QJsonArray &keysArray)
{

    //QVector<Key> keys;
    QVector<QVector<Key>> result;

    foreach (const QJsonValue & val, keysArray) {
        result = QVector<QVector<Key>>();
        //qDebug() << val.toObject().value("keys");
        QJsonArray array = val.toObject().value("keys").toArray();
        QVector<QVector<Key>> rows;
        for (auto it = array.begin(); it != array.end(); ++it) {
            //qDebug() << "ROWS: " << it->toArray();
            QJsonArray jsRows = it->toArray();

            QVector<Key> keys;
            for(auto it = jsRows.begin(); it != jsRows.end(); ++it) {
                qDebug() << "Items: " << it->toString();
                //QJsonArray rows = it->toArray();
                keys.append(Key(it->toString(),mWidth,mHeight));
            }
            rows.append(keys);
        }
        qDebug() << "count: " << array.count();
        result = rows;
    }


    return result;
}





/*int KeyLayout::layoutsCount()
{
   // return layouts->size();
}


QVector<int> KeyLayout::getRowKeyMap()
{
    //return *rowKeyMap;
}

QVector<QString> KeyLayout::getLayoutAt(int n)
{
    //return layouts->at(n);
}

const QVector<QVector<QString> > *KeyLayout::getLayouts()
{

    return const_cast<QVector<QVector<QString> >*>(layouts);
}
*/
