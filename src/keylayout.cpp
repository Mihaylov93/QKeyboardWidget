#include "keylayout.h"

#include <QDebug>
#include <QJsonDocument>
//#include <QJsonObject>
#include <QJsonArray>

#include <QFile>

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

int KeyLayout::getLayoutIndex(const QString &iLayoutName) const
{
    return _layoutNames.indexOf(iLayoutName);
}

bool KeyLayout::isSwitchKey(const QString &iKey, QString &ioValue) const
{
    ioValue = _keySwitchMap.value(iKey);
    return _keySwitchMap.contains(iKey);
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

    const QJsonArray mLayouts = getQJsonValue(_jsonObject, "layouts", Type::Array).toArray();
    // initialize keys modifiers
    const QJsonValue mModifiers = getQJsonValue(_jsonObject, "modifiers", Type::Array);
    if (mModifiers.isArray()) {
        initModifierKeys(mModifiers.toArray());
    }
    // Initialize layouts
    foreach (const QJsonValue &val, mLayouts) {
        const QJsonObject jsonObj = val.toObject();
        _layoutNames.append(getQJsonValue(jsonObj, "name", Type::String).toString());

        const QJsonValue kbdsVal = getQJsonValue(jsonObj, "keys", Type::Array);
        // Initialize rows
        _layouts.append(initGridLayout(kbdsVal.toArray()));
    }
}

void KeyLayout::initModifierKeys(const QJsonArray &iModKeysArray)
{
    foreach (const QJsonValue &modType, iModKeysArray) {
        QJsonObject mJsonObj = modType.toObject();

        if (mJsonObj.contains("keyspan")) {
            _keySpanMap.insert(getQJsonValue(modType.toObject(), "keyspan", Type::String).toString(),
                               getQJsonValue(modType.toObject(), "span", Type::String).toString());
        }

        if (mJsonObj.contains("icon")) {
            _keyIconMap.insert(getQJsonValue(modType.toObject(), "icon", Type::String).toString(),
                               getQJsonValue(modType.toObject(), "path", Type::String).toString());
        }

        if (mJsonObj.contains("switchkey")) {
            _keySwitchMap.insert(getQJsonValue(modType.toObject(), "switchkey", Type::String).toString(),
                                 getQJsonValue(modType.toObject(), "layout", Type::String).toString());
        }
    }
}

QGridLayout *KeyLayout::initGridLayout(const QJsonArray &iKeysArray)
{

    int mRow = 0;
    auto *rows = new QGridLayout();
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
            QString mIconPath;
            if (_keySpanMap.contains(mText)) {

                mKeySpan = _keySpanMap.value(mText).toInt();
            }

            if (_keyIconMap.contains(mText)) {

                mIconPath = _keyIconMap.value(mText);
            }

            mLastColumn = mLastColumn + mLastSpan;
            // When you add a widget to a layout it parents them
            Key *mKey = new Key(mText, mIconPath);
            Q_ASSERT(this->connect(mKey, &Key::keyPressed, [mKey, this]() {
                emit this->keyPressed(mKey->objectName());
                qDebug() << mKey->objectName();
            }));

            rows->addWidget(mKey, mRow, mLastColumn, 1, mKeySpan);
            mLastSpan = mKeySpan;
        }
        mRow++;
    }
    return rows;
}
