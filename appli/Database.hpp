#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

class Database : public QObject {
    Q_OBJECT
public:
    explicit Database();
    int requete(QString requete);

Q_SIGNALS:


private Q_SLOTS:


private:
  QSqlDatabase db;
  QSqlQuery query;
  QSqlRecord record;
};

#endif // DATABASE_H