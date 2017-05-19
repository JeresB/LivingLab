#include "Traitement.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Traitement::Traitement(QObject *parent) : QObject(parent) {
  bool success = false;
  // Création de la connexion à la base de données
  livinglab = new Database;

  // Fonction de récupération des adresses IP des pièces
  success = List("room");
  if (success == true) {
    qDebug() << "[INFO] : Récupération de la liste des chambres : SUCCESS";
  } else {
    qWarning() << "[WARNING] : Récupération de la liste des chambres : FAILED";
  }

  // Fonction de récupération des adresses IP de l'utilsateur
  success = List("user");
  if (success == true) {
    qDebug() << "[INFO] : Récupération de la liste des telephones : SUCCESS";
  } else {
    qWarning() << "[WARNING] : Récupération de la liste des telephones : FAILED";
  }

  success = roomSeuil();
  if (telephoneSeuil()) qDebug() << "[INFO] : Récupération des seuils des telephones : SUCCESS";
  else qWarning() << "[WARNING] : Récupération des seuils des telephones : FAILED";

}
//! [constructor]

int Traitement::List(QString type) {
  bool success = false;
  QByteArray result;
  qDebug() << "Le type = " << type;

  if(type == "room") result = livinglab->requete("SELECT * FROM chambre");
  else if(type == "user") result = livinglab->requete("SELECT * FROM telephone");

  QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(result);
  QJsonArray jsonArray = jsonDoc.array();

  for (int i = 0; i < jsonArray.count(); i++) {
    QJsonValue champ = jsonArray.at(i);
    QJsonObject champObject = champ.toObject();

    if (type == "room") {
      int id = champObject.value(QString{"id_chambre"}).toInt();
      QString IP = champObject.value(QString{"ip_chambre"}).toString();
      int port =  champObject.value(QString{"port_chambre"}).toInt();

      success = openConnexionChambre(id, IP, port);
    } else if (type == "user") {
      QString tel = champObject.value(QString{"numero"}).toString();
      QString IP = champObject.value(QString{"ip_telephone"}).toString();
      int port =  champObject.value(QString{"port_telephone"}).toInt();

      success = openConnexionUser(tel, IP, port);
    }

    if (success == false) return success;
  }

  return success;
}

int Traitement::roomSeuil() {
  bool success = true;

  // Tableau qui contiendra toutes les valeurs des seuils recueillis
  int v[6];

  QString requete = "SELECT * FROM seuil, chambre WHERE seuil.id_chambre = chambre.id_chambre";
  QByteArray result = livinglab->requete(requete);

  QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(result);

  QJsonArray jsonArray = jsonDoc.array();

  for (int i = 0; i < jsonArray.count(); i++) {
    QJsonValue champ = jsonArray.at(i);
    QJsonObject champObject = champ.toObject();

    v[0] = champObject.value(QString{"humiditymin"}).toInt();
    v[1] = champObject.value(QString{"humiditymax"}).toInt();
    v[2] = champObject.value(QString{"temperaturemin"}).toInt();
    v[3] = champObject.value(QString{"temperaturemax"}).toInt();
    v[4] = champObject.value(QString{"co2moyen"}).toInt();
    v[5] = champObject.value(QString{"co2haut"}).toInt();
    QString v6 = champObject.value(QString{"four"}).toString();

    for (int j = 0; j < vect_chambre.size(); j++) {
      if (vect_chambre[j]->getID() == champObject.value(QString{"id_chambre"}).toInt()) {
        qDebug() << "VERIFICATION ID : " << vect_chambre[j]->getID() << " = " << champObject.value(QString{"id_chambre"}).toInt();
        vect_chambre[j]->setAllSeuil(v[0], v[1], v[2], v[3], v[4], v[5], v6);
      }
    }
  }

  return success;
}

int Traitement::openConnexionChambre(int id, QString IP, int port) {
  QString url = "ws://" + IP + ":" + QString::number(port);

  try {
    vect_chambre << new Chambre(QUrl(url), id);
    connect(vect_chambre.last(), SIGNAL(sendTextToProcess(QString, int, bool, float, float, bool, int)), this, SLOT(saveDataRoomToProcess(QString, int, bool, float, float, bool, int)));


    return true;
  } catch(...) {
    return false;
  }
}

void Traitement::saveDataRoomToProcess(QString date, int co2, bool fall, float temp, float hum, bool oven, int id) {
  qDebug() << "DATA SAVING = " << date;
  bool alerte = false;

  for (int i = 0; i < vect_chambre.size(); i++) {
    if (vect_chambre[i]->getID() == id) {
      if (co2 > vect_chambre[i]->getCO2_M()) {
        if (co2 > vect_chambre[i]->getCO2_H()) {
          // alerte SMS, le co2 dépasse le seuil haut
          alerte = true;
        }
        // alerte mail, le co2 dépasse le seuil moyen
        alerte = true;
      }

      if (fall) {
        // alerte l'utilsateur est tombé
        alerte = true;
      }

      if (temp > vect_chambre[i]->getTemp_Max() || temp < vect_chambre[i]->getTemp_Min()) {
        // alerte la temperature ne respecte pas l'interval demandé
        alerte = true;
      }

      if (hum > vect_chambre[i]->getHum_Max() || hum < vect_chambre[i]->getHum_Min()) {
        // alerte l'humidité ne respecte pas l'interval demandé
        alerte = true;
      }

      QString tempo;
      QString valeur = "('" + date + "', '" + tempo.setNum(co2) + "', '" + QString::number(fall) + "', '" + QString::number(temp) + "', '" + QString::number(hum) + "', '" + QString::number(oven) + "', '" + QString::number(alerte) + "', '" + QString::number(id) + "')";
      qDebug() << "VALEUR ----------" << valeur;
      livinglab->insertCapteurs(valeur);
    }
  }
}

int Traitement::telephoneSeuil() {
  bool success = true;
  qDebug() << "Fonction telephoneSeuil()";
  // Tableau qui contiendra toutes les valeurs des seuils recueillis

  QString requete = "SELECT * FROM seuil_user, telephone WHERE seuil_user.numero = telephone.numero";
  QByteArray result = livinglab->requete(requete);

  QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(result);
  qDebug() << "json doc = " << jsonDoc;
  QJsonArray jsonArray = jsonDoc.array();

  for (int i = 0; i < jsonArray.count(); i++) {
    QJsonValue champ = jsonArray.at(i);
    QJsonObject champObject = champ.toObject();

    QString pas = champObject.value(QString{"deplacement"}).toString();

    for (int j = 0; j < vect_user.size(); j++) {
      if (vect_user[j]->getID() == champObject.value(QString{"numero"}).toString()) {
        qDebug() << "VERIFICATION ID : " << vect_user[j]->getID() << " = " << champObject.value(QString{"numero"}).toString();
        vect_user[j]->setAllSeuil(pas);
      }
    }
  }

  return success;
}

int Traitement::openConnexionUser(QString numero, QString IP, int port) {
  QString url = "ws://" + IP + ":" + QString::number(port);
  qDebug() << url;

  try {
    vect_user << new Telephone(QUrl(url), numero);
    connect(vect_user.last(), SIGNAL(sendTextToProcess(QString, int, QString, QString)), this, SLOT(saveDataUserToProcess(QString, int, QString, QString)));

    return true;
  } catch(...) {
    return false;
  }
}

void Traitement::saveDataUserToProcess(QString date, int pas, QString user, QString numero) {
  bool alerte = false;

  QString tempo;
  QString valeur = "('" + date + "', '" + QString::number(pas) + "', '" + user + "', '" + numero + "')";
  qDebug() << "VALEUR ----------" << valeur;
  livinglab->insertCapteursUser(valeur);

}
