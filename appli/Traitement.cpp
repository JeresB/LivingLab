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
  QByteArray result;
  QJsonDocument json;
  result = livinglab->requete("SELECT * FROM chambre");

  json = QJsonDocument::fromBinaryData(result);

  QJsonObject JsonObject = json.object();
  qDebug() << JsonObject << "rogifvovji";

  qDebug() << JsonObject.value(QString{"ip_chambre"});
}
