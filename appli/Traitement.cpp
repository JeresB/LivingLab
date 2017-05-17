#include "Traitement.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Traitement::Traitement(QObject *parent) : QObject(parent) {
  bool success = false;
  // Création de la connexion à la base de données
  livinglab = new Database;

  // Fonction de récupération des adresses IP des pièces
  success = roomList();

}
//! [constructor]

int Traitement::roomList() {
  QByteArray result = livinglab->requete("SELECT * FROM chambre");

  QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(result);

  QJsonArray jsonArray = jsonDoc.array();

  QJsonValue champ = jsonArray.at(0);
  QjsonObject champObject = champ.toObject();
  qDebug() << jsonArray.at(0);
  qDebug() << champObject.value(QString{"ip_chambre"}).toString();
}
