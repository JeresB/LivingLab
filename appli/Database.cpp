/**
 * \file Database.cpp
 * \brief  Connexion avec la base de données
 * \version 1
 * \date 24 mai 2017
 * \author {Jeremy B. & Théo D.}
 */

#include "Database.hpp"
#include <QDebug>

QT_USE_NAMESPACE

/**
 *  \brief Constructeur
 *
 *  Constructeur de la classe Database
 *
 *  \param parent(QObject*) : Possibilité de donner le QObject parent
 */
Database::Database(QObject *parent) : QObject(parent) {
  db = QSqlDatabase::addDatabase("QMYSQL");

  QFile fichier("bdd.conf");
  fichier.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream flux(&fichier);

  QStringList ligne;

  while(! flux.atEnd()) {
    ligne << flux.readLine();
  }

  db.setHostName(ligne[0]);
  db.setUserName(ligne[1]);
  db.setPassword(ligne[2]);
  db.setDatabaseName(ligne[3]);

  if(db.open()) {
    qDebug() << "\033[1;42;37m[INFO] : Connexion vers" << db.hostName() << ": SUCCESS\033[0;0m";
  } else {
    qWarning() << "\033[1;43;37m[WARNING] : Connexion vers" << db.hostName() << ": FAILED\033[0;0m";
  }
}

/**
 *  \brief Requete
 *
 *  Méthode requete : permet de faire des requetes de type SELECT
 *
 *  \param sqlquery(QString &) : requete de type select
 */
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

/**
 *  \brief insertCapteurs
 *
 *  Méthode insertCapteurs : permet de faire des requetes de type INSERT INTO
 *
 *  \param requete(QString) : requete de type insert into
 */
void Database::insertCapteurs( QString requete) {
  QSqlQuery query;
  qDebug() << "\033[1;45;37m[REQUETE] :" << requete << "\033[0;0m";

  if(query.exec(requete)) qDebug() << "\033[1;42;37m[INFO] : Requete d'insertion dans la BDD : SUCCESS\033[0;0m";
  else qWarning() << "\033[1;43;37m[WARNING] : Requete d'insertion dans la BDD : FAILED\033[0;0m";
}
