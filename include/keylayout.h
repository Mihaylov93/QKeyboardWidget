#ifndef KEYLAYOUT_H
#define KEYLAYOUT_H

#include <QObject>
#include <QVector>

#include <QFile>
#include <QJsonObject>
#include <QJsonValue>
#include <QGridLayout>

#include <QMap>

#include "key.h"

class KeyLayout : public QObject {
    Q_OBJECT
public:
    explicit KeyLayout(const QString &json, QObject *parent = nullptr);
    explicit KeyLayout(QFile &file, QObject *parent = nullptr);
    KeyLayout(const KeyLayout &) = delete;
    ~KeyLayout() override = default;

    QString getLocale();

    // const QVector<QVector<QVector<Key>>> &getLayouts();
    const QVector<QSharedPointer<QGridLayout>> &getLayouts();
    QSharedPointer<QGridLayout> getLayoutAt(const int &iIdx);

private:
    enum Type { Null, String, Array };

    QString _locale;
    QJsonObject _jsonObject;

    void initLayouts();
    void initModifierKeys(const QJsonArray &iModKeysArray);
    QSharedPointer<QGridLayout> initGridLayout(const QJsonArray &iKeysArray);

    QJsonValue getQJsonValue(const QJsonObject &obj, const QString &key, Type type = Type::Null);
    QVector<QString> _layoutNames;

    QMap<QString, QString> _keySpan;
    QVector<QSharedPointer<QGridLayout>> _layouts;
};

#endif    // KEYLAYOUT_H
