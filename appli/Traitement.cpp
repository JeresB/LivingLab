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

  QJsonArray JsonObject = json.array();
  qDebug() << json << "rogifvovji";
  qDebug() << JsonObject << "rogifvovji";

  QJsonValue value_ip = JsonObject.at(0);
  QJsonObject object = value_ip.toObject();
  qDebug() << JsonObject.at(0);
  qDebug() << object.value(QString{"ip_chambre"});
}
