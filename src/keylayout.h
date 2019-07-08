#ifndef KEYLAYOUT_H
#define KEYLAYOUT_H

#include <QObject>
#include <QVector>

#include <QFile>
#include <QJsonObject>
#include <QJsonValue>
//#include <initializer_list>


#include "key.h"

class KeyLayout : public QObject
{
    Q_OBJECT
public:

    explicit KeyLayout(QString json,QObject *parent = nullptr);
    explicit KeyLayout(QFile *file,QObject *parent = nullptr);
    ~KeyLayout();
    QString getLocale();
    int layoutsCount();

    const QVector<QVector<QVector<Key>>>& getLayouts();
    QVector< QVector<Key>> getRows(char layout);


private:
    enum Type { Null, String, Array };
    
    QString mLocale;
    int mWidth = 0;
    int mHeight = 0;
    QJsonObject jsonObject;
    QJsonValue getQJsonValue(QJsonObject obj, QString key,Type type = Type::Null);

    QVector<QString> layoutNames;
    QVector< QVector< QVector< Key > > > layouts;



    void init();
    QVector<QVector<Key>> initLayouts(const QJsonArray &keysArray);
};

#endif // KEYLAYOUT_H
