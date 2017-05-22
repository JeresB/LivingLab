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
    qDebug() << "\033[1;42;37m[INFO] : Connexion vers" << db.hostName() << ": SUCCESS\033[0;0m";
  } else {
    qWarning() << "\033[1;43;37m[WARNING] : Connexion vers" << db.hostName() << ": FAILED\033[0;0m";
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

  //qDebug() << json.toJson() << "----------" << json;
  return json.toBinaryData();
}
//! [fonction public requete]


void Database::insertCapteurs( QString requete) {
  QSqlQuery query;
  qDebug() << "\033[1;45;37m[REQUETE] :" << requete << "\033[0;0m";

  if(query.exec(requete)) qDebug() << "\033[1;42;37m[INFO] : Requete d'insertion dans la BDD : SUCCESS\033[0;0m";
  else qWarning() << "\033[1;43;37m[WARNING] : Requete d'insertion dans la BDD : FAILED\033[0;0m";
}
