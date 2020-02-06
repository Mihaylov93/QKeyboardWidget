#include "keylayout.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QSharedPointer>

KeyLayout::KeyLayout(const QString &json, QObject *parent) : QObject(parent)
{
    Q_ASSERT(!json.isNull() && !json.isEmpty());
    QJsonParseError error{};
    _jsonObject = QJsonDocument::fromJson(json.toUtf8(), &error).object();

    if (Q_UNLIKELY(error.error != 0)) qDebug() << error.errorString();

    this->initLayouts();
}

KeyLayout::KeyLayout(QFile &file, QObject *parent) : QObject(parent)
{

    QJsonParseError error{};
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug() << "File isReadable() : " << file.isReadable();
    // Could happen that you open it and its not readable and the assert breaks without closing.
    // This hack prevents that with the same goal.
    if (!file.isReadable()) Q_ASSERT(0);

    QByteArray json = file.readAll();
    _jsonObject = QJsonDocument::fromJson(json, &error).object();
    file.close();

    if (Q_UNLIKELY(error.error != 0)) qDebug() << error.errorString();

    this->initLayouts();
}

QString KeyLayout::getLocale()
{
    return _locale;
}

const QVector<QGridLayout *> &KeyLayout::getLayouts()
{
    return _layouts;
}

QGridLayout *KeyLayout::getLayoutAt(const int &iIdx)
{
    qDebug() << this->_layouts;
    return _layouts.at(iIdx);
}

QJsonValue KeyLayout::getQJsonValue(const QJsonObject &obj, const QString &key, Type type)
{
    Q_ASSERT(!obj.isEmpty());
    QJsonValue value = obj.value(key);
    switch (type) {
        case Type::Array:
            Q_ASSERT(value.isArray());
            break;
        case Type::String:
            Q_ASSERT(value.isString());
            break;
        default:
            return value;
    }
    return value;
}

void KeyLayout::initLayouts()
{

    _locale = _jsonObject.value(QString("locale")).toString();

    QJsonValue value = getQJsonValue(_jsonObject, "layouts", Type::Array);
    QJsonArray layouts = value.toArray();

    foreach (const QJsonValue &val, layouts) {
        QJsonObject jsonObj = val.toObject();
        _layoutNames.append(getQJsonValue(jsonObj, "name", Type::String).toString());

        QJsonValue kbdsVal = getQJsonValue(jsonObj, "keys", Type::Array);

        // initialize keys modifiers

        qDebug() << jsonObj.value("modifiers").toArray();
        QJsonValue mJsonValue = getQJsonValue(jsonObj, "modifiers");
        if (mJsonValue.isArray()) {
            initModifierKeys(mJsonValue.toArray());
        }

        // initialize rows
        qDebug() << _layouts;

        _layouts.append(initGridLayout(kbdsVal.toArray()));
        qDebug() << _layouts[0];
    }
}

void KeyLayout::initModifierKeys(const QJsonArray &iModKeysArray)
{
    foreach (const QJsonValue &modType, iModKeysArray) {
        QJsonObject mJsonObj = modType.toObject();
        /*if (jsonObj.contains("modkey")) {
            mModKeys.insert(getQJsonValue(modType.toObject(), "modkey", Type::String).toString(),
                            getQJsonValue(modType.toObject(), "switchto", Type::String).toString());
        }*/

        if (mJsonObj.contains("keyspan")) {
            _keySpan.insert(getQJsonValue(modType.toObject(), "keyspan", Type::String).toString(),
                            getQJsonValue(modType.toObject(), "span", Type::String).toString());
        }
    }
    qDebug() << _keySpan;
}

QGridLayout *KeyLayout::initGridLayout(const QJsonArray &iKeysArray)
{

    int mRow = 0;
    QGridLayout *rows = new QGridLayout();
    QString mText;
    // Each row vector aka ROWS
    foreach (const QJsonValue &rowKeys, iKeysArray) {
        qDebug() << "RowKeys: " << rowKeys.toArray();
        QJsonArray mArray = rowKeys.toArray();

        int mLastColumn = 0;
        int mLastSpan = 0;
        // Each item of row aka COLUMNS
        for (auto it = mArray.begin(); it != mArray.end(); ++it) {

            mText = it->toString();
            int mKeySpan = 1;

            if (_keySpan.contains(mText)) {

                mKeySpan = _keySpan.value(mText).toInt();
            }

            mLastColumn = mLastColumn + mLastSpan;
            // When you add a widget to a layout it parents them
            rows->addWidget(new Key(mText), mRow, mLastColumn, 1, mKeySpan);
            mLastSpan = mKeySpan;
        }
        mRow++;
    }
    return rows;
}
