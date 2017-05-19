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
    qDebug() << "[INFO] : Connexion vers" << db.hostName() << ": SUCCESS";
  } else {
    qWarning() << "[WARNING] : Connexion vers" << db.hostName() << ": FAILED";
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

int Database::insertCapteurs( QString values) {
  QSqlQuery query;

  QString insert = "INSERT INTO `capteur`(`date_heure`, `co2`, `chute`, `temperature`, `humidite`, `four`, `detection_alerte`, `id_chambre`) VALUES ";
  QString requete = insert + values;

  qDebug() << requete;
  if(query.exec(requete)) {
    qDebug() << "La requete à bien été effectuée !!!";
  } else qDebug() << "Une erreur s'est produite. :(";
}

int Database::insertCapteursUser( QString values) {
  QSqlQuery query;

  QString insert = "INSERT INTO `capteurUser` (`temps`, `pas`, `user`, `numero`) VALUES ";
  QString requete = insert + values;

  qDebug() << requete;
  if(query.exec(requete)) {
    qDebug() << "La requete à bien été effectuée !!!";
  } else qDebug() << "Une erreur s'est produite. :(";
}
