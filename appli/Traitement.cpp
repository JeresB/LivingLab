#include "Traitement.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Traitement::Traitement(QObject *parent) : QObject(parent) {
  // Création de la connexion à la base de données
  livinglab = new Database;

  // Fonction de récupération des adresses IP des pièces
  if (List("room")) qDebug() << "[INFO] : Récupération de la liste des chambres : SUCCESS";
  else qWarning() << "[WARNING] : Récupération de la liste des chambres : FAILED";

  // Fonction de récupération des adresses IP de l'utilsateur
  if (List("user")) qDebug() << "[INFO] : Récupération de la liste des telephones : SUCCESS";
  else qWarning() << "[WARNING] : Récupération de la liste des telephones : FAILED";

  if (roomSeuil()) qDebug() << "[INFO] : Récupération des seuils des chambres : SUCCESS";
  else qWarning() << "[WARNING] : Récupération des seuils des chambres : FAILED";

  if (telephoneSeuil()) qDebug() << "[INFO] : Récupération des seuils des telephones : SUCCESS";
  else qWarning() << "[WARNING] : Récupération des seuils des telephones : FAILED";

}
//! [constructor]

int Traitement::List(QString type) {
  bool success = false;
  QByteArray result;

  if(type == "room") result = livinglab->requete("SELECT * FROM chambre");
  else if(type == "user") result = livinglab->requete("SELECT * FROM telephone");
  else return false;

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

    if (success == false) return false;
  }

  return success;
}

int Traitement::roomSeuil() {
  bool success = false;

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
        success = vect_chambre[j]->setAllSeuil(v[0], v[1], v[2], v[3], v[4], v[5], v6);
      }
    }
  }

  return success;
}

int Traitement::openConnexionChambre(int id, QString IP, int port) {
  QString url = "ws://" + IP + ":" + QString::number(port);

  try {
    vect_chambre << new Chambre(QUrl(url), id);
    vect_four_allume << QTime(0, 0, 0, 0);
    connect(vect_chambre.last(), SIGNAL(sendTextToProcess(QDateTime, int, bool, float, float, bool, int)),
     this, SLOT(saveDataRoomToProcess(QDateTime, int, bool, float, float, bool, int)));

    qDebug() << "[INFO] : Connexion à l'adresse :" << url << ": établie !";
    return true;
  } catch(...) {
    return false;
  }
}

void Traitement::saveDataRoomToProcess(QDateTime date, int co2, bool fall, float temp, float hum, bool oven, int id) {
  bool alerte = false;


  for (int i = 0; i < vect_chambre.size(); i++) {
    if (vect_chambre[i]->getID() == id) {

      QTime seuil_four = QTime::fromString(vect_chambre[i]->getFour(), "hh:mm:ss");

      if (!oven) {
        vect_four_allume[i] = vect_four_allume[i].addSecs(60);
      } else {
        vect_four_allume[i].setHMS(0, 0, 0);
      }

      QString fa = vect_four_allume[i].toString(QString("hh:mm:ss"));
      QString sf = seuil_four.toString(QString("hh:mm:ss"));
      if (vect_four_allume[i] > seuil_four) {
        qWarning() << "[WARNING] : Four allumé depuis :" << fa << " Temps de fonctionnement réglementaire :" << sf;
      } else qWarning() << "[INFO] : Four allumé depuis :" << fa << " Temps de fonctionnement réglementaire :" << sf;



      if (co2 > vect_chambre[i]->getCO2_M()) {
        if (co2 > vect_chambre[i]->getCO2_H()) {
          // alerte SMS, le co2 dépasse le seuil haut
          alerte = true;
          qWarning() << "[DANGER] : Le co2 a dépassé le seuil dangereux :" << vect_chambre[i]->getCO2_H() << "il vaut actuellement : " << co2 << "ppm";
        } else {
          // alerte mail, le co2 dépasse le seuil moyen
          alerte = true;
          qWarning() << "[WARNING] : Le co2 a dépassé le seuil d'avertissement :" << vect_chambre[i]->getCO2_M() << "il vaut actuellement : " << co2 << "ppm";
        }
      }

      if (fall) {
        // alerte l'utilsateur est tombé
        alerte = true;
        qWarning() << "[DANGER] : L'utilisateur est tombé !!!";
      }

      if (temp > vect_chambre[i]->getTemp_Max() || temp < vect_chambre[i]->getTemp_Min()) {
        // alerte la temperature ne respecte pas l'interval demandé
        alerte = true;
        qWarning() << "[WARNING] : La température est de :" << temp << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getTemp_Min() << ", " << vect_chambre[i]->getTemp_Max() << "]";
      }

      if (hum > vect_chambre[i]->getHum_Max() || hum < vect_chambre[i]->getHum_Min()) {
        // alerte l'humidité ne respecte pas l'interval demandé
        alerte = true;
        qWarning() << "[WARNING] : L'humidité est de :" << hum << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getHum_Min() << ", " << vect_chambre[i]->getHum_Max() << "]";
      }

      // QUrl url("http://localhost/test.php");
      // QNetworkAccessManager nam;
      // QNetworkReply* reply = nam.get(QNetworkRequest(url));

      QString date_s = date.toString(QString("yyyy-MM-dd hh:mm:ss"));

      QString insert = "INSERT INTO `capteur`(`date_heure`, `co2`, `chute`, `temperature`, `humidite`, `four`, `detection_alerte`, `id_chambre`) VALUES ";
      QString valeur = "('" + date_s + "', '" + QString::number(co2) + "', '" + QString::number(fall) + "', '" + QString::number(temp) + "', '" + QString::number(hum) + "', '" + QString::number(oven) + "', '" + QString::number(alerte) + "', '" + QString::number(id) + "')";

      QString requete = insert + valeur;

      qDebug() << "[INFO] : Demande d'insertion des données de la chambre n° :" << id;
      livinglab->insertCapteurs(requete);
    }
  }
}

int Traitement::telephoneSeuil() {
  bool success = false;

  QString requete = "SELECT * FROM seuil_user, telephone WHERE seuil_user.numero = telephone.numero";
  QByteArray result = livinglab->requete(requete);

  QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(result);
  QJsonArray jsonArray = jsonDoc.array();

  for (int i = 0; i < jsonArray.count(); i++) {
    QJsonValue champ = jsonArray.at(i);
    QJsonObject champObject = champ.toObject();

    QString pas = champObject.value(QString{"deplacement"}).toString();

    for (int j = 0; j < vect_user.size(); j++) {
      if (vect_user[j]->getID() == champObject.value(QString{"numero"}).toString()) {
        success = vect_user[j]->setAllSeuil(pas);
      }
    }
  }

  return success;
}

int Traitement::openConnexionUser(QString numero, QString IP, int port) {
  QString url = "ws://" + IP + ":" + QString::number(port);

  try {
    vect_user << new Telephone(QUrl(url), numero);
    connect(vect_user.last(), SIGNAL(sendTextToProcess(QString, int, QString, QString)),
     this, SLOT(saveDataUserToProcess(QString, int, QString, QString)));
    qDebug() << "[INFO] : Connexion à l'adresse :" << url << ": établie !";
    return true;
  } catch(...) {
    return false;
  }
}

void Traitement::saveDataUserToProcess(QString date, int pas, QString user, QString numero) {
  bool alerte = false;

  QString insert = "INSERT INTO `capteurUser` (`temps`, `pas`, `user`, `numero`) VALUES ";
  QString valeur = "('" + date + "', '" + QString::number(pas) + "', '" + user + "', '" + numero + "')";

  QString requete = insert + valeur;

  qDebug() << "[INFO] : Demande d'insertion des données du telephone n° :" << numero;
  livinglab->insertCapteurs(requete);
}
