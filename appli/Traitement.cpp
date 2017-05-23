#include "Traitement.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Traitement::Traitement(QObject *parent) : QObject(parent) {
  // Création de la connexion à la base de données
  livinglab = new Database;

  matin = QTime(7, 0);
  soir = QTime(23, 0);


  // Fonction de récupération des adresses IP des pièces
  if (List("room")) qDebug() << "\033[1;42;37m[INFO] : Récupération de la liste des chambres : SUCCESS\033[0;0m";
  else qWarning() << "\033[1;43;37m[WARNING] : Récupération de la liste des chambres : FAILED\033[0;0m";

  // Fonction de récupération des adresses IP de l'utilsateur
  if (List("user")) qDebug() << "\033[1;42;37m[INFO] : Récupération de la liste des telephones : SUCCESS\033[0;0m";
  else qWarning() << "\033[1;43;37m[WARNING] : Récupération de la liste des telephones : FAILED\033[0;0m";

  if (roomSeuil()) qDebug() << "\033[1;42;37m[INFO] : Récupération des seuils des chambres : SUCCESS\033[0;0m";
  else qWarning() << "\033[1;43;37m[WARNING] : Récupération des seuils des chambres : FAILED\033[0;0m";

  if (telephoneSeuil()) qDebug() << "\033[1;42;37m[INFO] : Récupération des seuils des telephones : SUCCESS\033[0;0m";
  else qWarning() << "\033[1;43;37m[WARNING] : Récupération des seuils des telephones : FAILED\033[0;0m";

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
    connect(vect_chambre.last(), SIGNAL(sendTextToProcess(QDateTime, int, bool, float, float, bool, QString, int)),
     this, SLOT(saveDataRoomToProcess(QDateTime, int, bool, float, float, bool, QString, int)));

    qDebug() << "\033[1;42;37m[INFO] : Connexion à l'adresse :" << url << ": établie !\033[0;0m";
    return true;
  } catch(...) {
    return false;
  }
}

void Traitement::saveDataRoomToProcess(QDateTime date, int co2, bool fall, float temp, float hum, bool oven, QString presence, int id) {
  QString alerte = "false";


  for (int i = 0; i < vect_chambre.size(); i++) {
    if (vect_chambre[i]->getID() == id) {

      QTime seuil_four = QTime::fromString(vect_chambre[i]->getFour(), "hh:mm:ss");

      if (oven) {
        vect_four_allume[i] = vect_four_allume[i].addSecs(60);
      } else {
        vect_four_allume[i].setHMS(0, 0, 0);
      }

      QString fa = vect_four_allume[i].toString(QString("hh:mm:ss"));
      QString sf = seuil_four.toString(QString("hh:mm:ss"));
      if (vect_four_allume[i] > seuil_four) {
        alerte = "Four allumé depuis trop longtemps, veuillez l'éteindre !!!";
        qWarning() << "\033[1;43;37m[WARNING] : Four allumé depuis :" << fa << " Temps de fonctionnement réglementaire :" << sf << "\033[0;0m";
      } else qDebug() << "\033[1;42;37m[INFO] : Four allumé depuis :" << fa << " Temps de fonctionnement réglementaire :" << sf << "\033[0;0m";



      if (co2 > vect_chambre[i]->getCO2_M()) {
        if (co2 > vect_chambre[i]->getCO2_H()) {
          // alerte SMS, le co2 dépasse le seuil haut
          alerte = "Le co2 a atteint un niveau critique !!!";
          qWarning() << "\033[1;41;37m[DANGER] : Le co2 a dépassé le seuil dangereux :" << vect_chambre[i]->getCO2_H() << "il vaut actuellement : " << co2 << "ppm\033[0;0m";
        } else {
          // alerte mail, le co2 dépasse le seuil moyen
          alerte = "Le co2 a atteint un niveau dangereux !!!";
          qWarning() << "\033[1;43;37m[WARNING] : Le co2 a dépassé le seuil d'avertissement :" << vect_chambre[i]->getCO2_M() << "il vaut actuellement : " << co2 << "ppm\033[0;0m";
        }
      }

      if (fall) {
        // alerte l'utilsateur est tombé
        alerte = "L'utilisateur est tombé !!!";
        qWarning() << "[DANGER] : L'utilisateur est tombé !!!";
      }

      if (temperature_save.size() >= 5) {
        temperature_save << temp;
        // supprimer le premier
        temperature_save.removeFirst();
        // comparer premier et dernier
        int diff = temperature_save.last() - temperature_save.first();
        if(diff > diff_temp) {
          alerte = "La température a évoluée dangereusement pendant les 5 dernières minutes !!!";
          qWarning() << "\033[1;43;37m[WARNING] : La température a augmentée de " << diff << "°C sur les 5 dernières minutes\033[0;0m";
        } else {
          qDebug() << "\033[1;42;37m[INFO] : La température a évoluée de " << diff << "°C sur les 5 dernières minutes\033[0;0m";
        }
      } else {
        temperature_save << temp;
      }

      if (temp > vect_chambre[i]->getTemp_Max()) {
        // alerte la temperature ne respecte pas l'interval demandé
        alerte = "La température est trop élevée !!!";
        qWarning() << "\033[1;43;37m[WARNING] : La température est de :" << temp << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getTemp_Min() << ", " << vect_chambre[i]->getTemp_Max() << "]\033[0;0m";
      }

      if (temp < vect_chambre[i]->getTemp_Min()) {
        // alerte la temperature ne respecte pas l'interval demandé
        alerte = "La température est trop basse !!!";
        qWarning() << "\033[1;43;37m[WARNING] : La température est de :" << temp << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getTemp_Min() << ", " << vect_chambre[i]->getTemp_Max() << "]\033[0;0m";
      }

      if (hum > vect_chambre[i]->getHum_Max()) {
        // alerte l'humidité ne respecte pas l'interval demandé
        alerte = "L'humidité à dépassée le seuil autorisé !!!";
        qWarning() << "\033[1;43;37m[WARNING] : L'humidité est de :" << hum << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getHum_Min() << ", " << vect_chambre[i]->getHum_Max() << "]\033[0;0m";
      }

      if (hum < vect_chambre[i]->getHum_Min()) {
        // alerte l'humidité ne respecte pas l'interval demandé
        alerte = "L'humidité n'atteint pas le niveau minimum demandé !!!";
        qWarning() << "\033[1;43;37m[WARNING] : L'humidité est de :" << hum << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getHum_Min() << ", " << vect_chambre[i]->getHum_Max() << "]\033[0;0m";
      }

      // QUrl url("http://localhost/test.php");
      // QNetworkAccessManager nam;
      // QNetworkReply* reply = nam.get(QNetworkRequest(url));

      QString date_s = date.toString(QString("yyyy-MM-dd hh:mm:ss"));

      QString insert = "INSERT INTO `capteur`(`date_heure`, `co2`, `chute`, `temperature`, `humidite`, `four`, `presence`, `detection_alerte`, `id_chambre`) VALUES ";
      QString valeur = "('" + date_s + "', '" + QString::number(co2) + "', '" + QString::number(fall) + "', '" + QString::number(temp) + "', '" + QString::number(hum) + "', '" + QString::number(oven) + "', '" + presence + "', '" + alerte + "', '" + QString::number(id) + "')";

      QString requete = insert + valeur;

      qDebug() << "\033[1;42;37m[INFO] : Demande d'insertion des données de la chambre n° :" << id << "\033[0;0m";
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
    vect_deplacement << QTime(0, 0, 0, 0);
    connect(vect_user.last(), SIGNAL(sendTextToProcess(QDateTime, int, QString, QString)),
     this, SLOT(saveDataUserToProcess(QDateTime, int, QString, QString)));
    qDebug() << "\033[1;42;37m[INFO] : Connexion à l'adresse :" << url << ": établie !\033[0;0m";
    return true;
  } catch(...) {
    return false;
  }
}

void Traitement::saveDataUserToProcess(QDateTime timestamp, int pas, QString user, QString numero) {
  QString alerte = "false";

  QString date = timestamp.toString(QString("yyyy-MM-dd hh:mm:ss"));
  QString heure_s = timestamp.toString(QString("hh:mm:ss"));

  for (int i = 0; i < vect_user.size(); i++) {
    if (vect_user[i]->getID() == numero) {
      QTime seuil_pas = QTime::fromString(vect_user[i]->getPas(), "hh:mm:ss");
      QTime heure_time = QTime::fromString(heure_s, "hh:mm:ss");
      QString heure_actuel = heure_time.toString(QString("hh:mm:ss"));
      //qDebug() << "HEURE :" << heure << "DATE :" << date << "HEURE_ACTUEL :" << heure_actuel;

      if (heure_time > matin && heure_time < soir) {
        if (pas > 0) {
          vect_deplacement[i].setHMS(0, 0, 0);
        } else {
          vect_deplacement[i] = vect_deplacement[i].addSecs(3600);
        }

        QString move = vect_deplacement[i].toString(QString("hh:mm:ss"));
        QString sp = seuil_pas.toString(QString("hh:mm:ss"));
        if (vect_deplacement[i] > seuil_pas) {
          alerte = "L'utilisateur est immobile depuis trop longtemps !!!";
          qWarning() << "\033[1;43;37m[WARNING] : L'utilisateur n'a pas bougé depuis :" << move << "heures. Temps immobile maximum autorisé :" << sp << "\033[0;0m";
        } else qDebug() << "\033[1;42;37m[INFO] : L'utilisateur n'a pas bougé depuis :" << move << "heures. Temps immobile maximum autorisé :" << sp << "\033[0;0m";

      } else qDebug() << "L'utilisateur dort,  il est " << heure_actuel;
    }
  }

  QString insert = "INSERT INTO `capteurUser` (`temps`, `pas`, `user`, `detection_alerte_user`, `numero`) VALUES ";
  QString valeur = "('" + date + "', '" + QString::number(pas) + "', '" + user + "', '" + alerte + "', '" + numero + "')";

  QString requete = insert + valeur;

  qDebug() << "\033[1;42;37m[INFO] : Demande d'insertion des données du telephone n° :" << numero << "\033[0;0m";
  livinglab->insertCapteurs(requete);
}
