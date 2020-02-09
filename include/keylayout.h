#ifndef KEYLAYOUT_H
#define KEYLAYOUT_H

#include <QObject>
#include <QVector>

#include <QJsonObject>
#include <QJsonValue>
#include <QGridLayout>

#include <QMap>

#include "key.h"
class QFile;
class KeyLayout : public QObject {
    Q_OBJECT
public:
    explicit KeyLayout(const QString &json, QObject *parent = nullptr);
    explicit KeyLayout(QFile &file, QObject *parent = nullptr);
    KeyLayout(const KeyLayout &) = delete;
    ~KeyLayout() override = default;

    QString getLocale();

    // const QVector<QVector<QVector<Key>>> &getLayouts();
    const QVector<QGridLayout *> &getLayouts();
    QGridLayout *getLayoutAt(const int &iIdx);
    int getLayoutIndex(const QString &iLayoutName) const;
    bool isSwitchKey(const QString &iKey, QString &ioValue) const;
signals:
    void keyPressed(QString key);

private:
    enum Type { Null, String, Array };

    QString _locale;
    QJsonObject _jsonObject;

    void initLayouts();
    void initModifierKeys(const QJsonArray &iModKeysArray);
    QGridLayout *initGridLayout(const QJsonArray &iKeysArray);

    QJsonValue getQJsonValue(const QJsonObject &obj, const QString &key, Type type = Type::Null);
    QVector<QString> _layoutNames;

    QMap<QString, QString> _keySpanMap;
    QMap<QString, QString> _keyIconMap;
    QMap<QString, QString> _keySwitchMap;
    QVector<QGridLayout *> _layouts;
};

#endif    // KEYLAYOUT_H
