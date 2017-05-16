#include "Database.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Database::Database(QObject *parent) : QObject(parent) {
  db = QSqlDatabase::addDatabase("QMYSQL");

  db.setHostName("localhost");
  db.setUserName("livinglab");
  db.setPassword("livinglab");
  db.setDatabaseName("livinglab");

  if(db.open()) {
    qDebug() << "Vous êtes maintenant connecté à " << db.hostName();
  } else {
    qDebug() << "La connexion a échouée, désolé";
  }
}
//! [constructor]

// [fonction public requete]
QByteArray Database::requete(const QString & sqlquery) {
QSqlQuery query;
QByteArray jsonDocBinaire;
  query.setForwardOnly(true);
  if (!query.exec(sqlquery))return jsonDocBinaire;

  QJsonDocument  json;
  QJsonArray     recordsArray;

  while(query.next())
  {
     QJsonObject recordObject;
        for(int x=0; x < query.record().count(); x++)
        {
        recordObject.insert( query.record().fieldName(x),QJsonValue::fromVariant(query.value(x)) );
        }
     recordsArray.push_back(recordObject);
  }
  json.setArray(recordsArray);

  qDebug() << json.toJson() << "----------" << json << "-----------" << json.toBinaryData();
  return json.toBinaryData();
}
//! [fonction public requete]
