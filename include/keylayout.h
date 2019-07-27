#ifndef KEYLAYOUT_H
#define KEYLAYOUT_H

#include <QObject>
#include <QVector>

#include <QFile>
#include <QJsonObject>
#include <QJsonValue>
//#include <initializer_list>

#include "key.h"

class KeyLayout : public QObject {
    Q_OBJECT
    public:
    explicit KeyLayout(const QString &json, QObject *parent = nullptr);
    explicit KeyLayout(QFile *file, QObject *parent = nullptr);
    KeyLayout(const KeyLayout &) = delete;
    ~KeyLayout() override = default;

    QString getLocale();

    const QVector<QVector<QVector<Key>>> &getLayouts();
    QVector<QVector<Key>> *getRows(char layout);
    bool isModifier(const QString &keyText);
    char getLayoutIdxFromKey(const QString &keyText);

    private:
    enum Type { Null, String, Array };

    QString mLocale;
    int mWidth = 0;
    int mHeight = 0;
    QJsonObject jsonObject;

    void initLayouts();
    void initModKeys(const QJsonArray &modKeysArray);

    QJsonValue getQJsonValue(const QJsonObject &obj, const QString &key, Type type = Type::Null);
    QVector<QString> layoutNames;
    QVector<QVector<QVector<Key>>> layouts;
    QVector<QVector<Key>> initRows(const QJsonArray &keysArray);

    QMap<QString, QString> modKeys;
};

#endif    // KEYLAYOUT_H
