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
QString Database::requete(QString requete) {
  QString retour = "";
  if (db.isOpen()) {
    query  = db.exec(requete);
    record = query.record();
    qDebug() << "Selection réussi :)";

    QJsonArray recordsArray;

    while(query.next()) {
      QJsonObject recordObject;
      for(int i = 0; i < record.count(); i++) {
        recordObject.insert( query.record().fieldName(i),QJsonValue::fromVariant(query.value(i)) );
      }

      recordsArray.push_back(recordObject);
    }

    QJsonDocument json = QJsonDocument(recordsArray);
  } else {
    qDebug() << "La requete n'a pas abouti, la base de données est fermée !";
  }

  retour = json.toJson();
  return retour;
}
//! [fonction public requete]
