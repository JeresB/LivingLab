/**
 * \file Traitement.cpp
 * \brief  Ce fichier permet de démarrer les connexions websockets
 *         Traiter les données reçues par les websockets
 * \version 1
 * \date 24 mai 2017
 * \author {Jeremy B. & Théo D.}
 */
#include "Traitement.hpp"
#include <QDebug>
#include "smtp/SmtpMime"

QT_USE_NAMESPACE
using namespace SimpleMail;

/**
 * \fn Constructeur
 * \brief  Permet de démarrer la connexion à la BDD
 *         Récupère les adresses IP et ouvre les connexions websockets
 *         Récupère les seuils correspondant à chaque chambre
 * \param[in, out] parent(QObject*) : Possibilité de donner en argument le QObject parent en pointeur
 */
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

/**
 * \fn Mail
 * \brief  Permet d'envoyer une alerte par mail
 *
 * \param[in] id(int) : id de la chambre ou du telephone
 * \param[in] objet(QString) : id de la chambre ou du telephone
 * \param[in] message_alerte(QString) : message d'alerte
 * \param[in] type(int) : spécifie si c'est un telephone ou une chambre pour adapter la requete SQL
 */
int Traitement::mail(int id, QString Objet, QString message_alerte, int type) {
  QByteArray result;
  if(type == 1) result = livinglab->requete("SELECT login_email, utilisateur_contact.login_email_user FROM utilisateur_contact, Utilisateur WHERE utilisateur_contact.login_email_user = Utilisateur.login_email_user AND Utilisateur.id_chambre =" + QString::number(id));
  else if(type == 2) result = livinglab->requete("SELECT login_email, utilisateur_contact.login_email_user FROM utilisateur_contact, Utilisateur WHERE utilisateur_contact.login_email_user = Utilisateur.login_email_user AND Utilisateur.id_telephone =" + QString::number(id));
  else qWarning() << "\033[1;43;37m[WARNING] : Récupération des adresses mails : FAILED\033[0;0m";

  Sender smtp(QLatin1String("smtp.isen-ouest.fr"), 465, Sender::SslConnection);

  // We need to set the username (your email address) and password
  // for smtp authentification.

  smtp.setUser(QLatin1String("elevecir2"));
  smtp.setPassword(QLatin1String("Cir2Projet"));

  // Now we create a MimeMessage object. This is the email.

  MimeMessage message;

  EmailAddress sender(QLatin1String("alerte@livinglab.fr"), QLatin1String("LivingLab"));
  message.setSender(sender);

  QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(result);
  QJsonArray jsonArray = jsonDoc.array();

  QJsonValue champ = jsonArray.at(0);
  QJsonObject champObject = champ.toObject();

  QString user = champObject.value(QString{"login_email_user"}).toString();

  EmailAddress to(user, user);
  message.addTo(to);

  for (int i = 0; i < jsonArray.count(); i++) {
    QJsonValue champ = jsonArray.at(i);
    QJsonObject champObject = champ.toObject();

    QString contact = champObject.value(QString{"login_email"}).toString();
    message.addTo(contact);
  }

  message.setSubject(QString(Objet));

  // Now add some text to the email.
  // First we create a MimeText object.

  MimeText text;

  text.setText(QString(message_alerte));

  // Now add it to the mail
  message.addPart(&text);

  // Now we can send the mail
  if (!smtp.sendMail(message)) {
      qDebug() << "Failed to send mail!" << smtp.lastError();
      return -3;
  }

  smtp.quit();

  return true;
}

/**
 * \fn List
 * \brief  Récupère les adresses IP
 *         Appelle les fonctions openConnexionChambre ou openConnexionUser
 *         En fonctions du paramètre d'entrée
 *
 * \param[in] type(QString) : 2 possibilités : room ou user
 * \return false si la requete ou l'ouverture des websockets à échouer
 *         true si l'ouverture des websockets est un succès
 */
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
      int id_telephone =  champObject.value(QString{"id_telephone"}).toInt();
      //QString tel = champObject.value(QString{"numero"}).toString();
      QString IP = champObject.value(QString{"ip_telephone"}).toString();
      int port =  champObject.value(QString{"port_telephone"}).toInt();

      success = openConnexionUser(id_telephone, IP, port);
    }

    if (success == false) return false;
  }

  return success;
}

/**
 * \fn roomSeuil
 * \brief  Récupère les seuils des chambres
 *         Enregistre les seuils dans les attributs de la chambre correspondante avec la méthode setAllSeuil
 *
 * \return false si l'enregistrement des seuils à échouer
 *         true si les seuils ont bien été enregistrer
 */
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

/**
 * \fn openConnexionChambre
 * \brief  Ouvre une connexion websocket lié à une chambre
 *
 * \param[in] id(int) : id de la chambre
 * \param[in] IP(QString) : IP de la chambre
 * \param[in] port(int) : port de la chambre
 *
 * \return false si l'ouverture websocket de la chambre à échouer
 *         true si l'ouverture websocket est un succès
 */
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

/**
 * \fn saveDataRoomToProcess
 * \brief  SLOT qui récupère les données émisent depuis les websockets chambres ouvertes
 *         Traite les données reçues
 *
 * Toutes les données reçues
 * \param[in] date(QDateTime) : date des données
 * \param[in] co2(int) : CO2 présent dans la chambre
 * \param[in] fall(bool) : Chute de l'utilisateur
 * \param[in] temp(float) : Température de la chambre
 * \param[in] hum(float) : Humidité de la chambre
 * \param[in] oven(bool) : Four allumé ou éteint
 * \param[in] presence(QString) : Nom de l'utilisateur present dans la chambre ou chaine vide
 * \param[in] id(int) : identifiant de la chambre
 *
 * \return Appel de la méthode insertCapteurs de la classe Database
 *         On lui envoie en paramètre la requete d'insertion contenant les données reçues
 */
void Traitement::saveDataRoomToProcess(QDateTime date, int co2, bool fall, float temp, float hum, bool oven, QString presence, int id) {
  if (roomSeuil()) {}
  else qWarning() << "\033[1;43;37m[WARNING] : Récupération des seuils des chambres : FAILED\033[0;0m";

  QString alerte = "";


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
        alerte += "Four allumé depuis trop longtemps, veuillez l'éteindre !!! ";
        qWarning() << "\033[1;43;37m[WARNING] : Four allumé depuis :" << fa << " Temps de fonctionnement réglementaire :" << sf << "\033[0;0m";
      } else qDebug() << "\033[1;42;37m[INFO] : Four allumé depuis :" << fa << " Temps de fonctionnement réglementaire :" << sf << "\033[0;0m";



      if (co2 > vect_chambre[i]->getCO2_M()) {
        if (co2 > vect_chambre[i]->getCO2_H()) {
          // alerte SMS, le co2 dépasse le seuil haut
          alerte += "Le co2 a atteint un niveau critique !!! ";
          qWarning() << "\033[1;41;37m[DANGER] : Le co2 a dépassé le seuil dangereux :" << vect_chambre[i]->getCO2_H() << "il vaut actuellement : " << co2 << "ppm\033[0;0m";
        } else {
          // alerte mail, le co2 dépasse le seuil moyen
          alerte += "Le co2 a atteint un niveau dangereux !!! ";
          qWarning() << "\033[1;43;37m[WARNING] : Le co2 a dépassé le seuil d'avertissement :" << vect_chambre[i]->getCO2_M() << "il vaut actuellement : " << co2 << "ppm\033[0;0m";
        }
      }

      if (fall) {
        // alerte l'utilsateur est tombé
        alerte += "L'utilisateur est tombé !!! ";
        qWarning() << "[DANGER] : L'utilisateur est tombé !!!";
      }

      if (temperature_save.size() >= 5) {
        temperature_save << temp;
        // supprimer le premier
        temperature_save.removeFirst();
        // comparer premier et dernier
        int diff = temperature_save.last() - temperature_save.first();
        if(diff >= diff_temp) {
          alerte += "La température a évoluée dangereusement pendant les 5 dernières minutes !!! ";
          qWarning() << "\033[1;43;37m[WARNING] : La température a augmentée de " << diff << "°C sur les 5 dernières minutes\033[0;0m";
        } else {
          qDebug() << "\033[1;42;37m[INFO] : La température a évoluée de " << diff << "°C sur les 5 dernières minutes\033[0;0m";
        }
      } else {
        temperature_save << temp;
      }

      if (temp > vect_chambre[i]->getTemp_Max()) {
        // alerte la temperature ne respecte pas l'interval demandé
        alerte += "La température est trop élevée !!! ";
        qWarning() << "\033[1;43;37m[WARNING] : La température est de :" << temp << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getTemp_Min() << ", " << vect_chambre[i]->getTemp_Max() << "]\033[0;0m";
      }

      if (temp < vect_chambre[i]->getTemp_Min()) {
        // alerte la temperature ne respecte pas l'interval demandé
        alerte += "La température est trop basse !!! ";
        qWarning() << "\033[1;43;37m[WARNING] : La température est de :" << temp << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getTemp_Min() << ", " << vect_chambre[i]->getTemp_Max() << "]\033[0;0m";
      }

      if (hum > vect_chambre[i]->getHum_Max()) {
        // alerte l'humidité ne respecte pas l'interval demandé
        alerte += "Humidité supérieur au seuil autorisé !!! ";
        qWarning() << "\033[1;43;37m[WARNING] : L'humidité est de :" << hum << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getHum_Min() << ", " << vect_chambre[i]->getHum_Max() << "]\033[0;0m";
      }

      if (hum < vect_chambre[i]->getHum_Min()) {
        // alerte l'humidité ne respecte pas l'interval demandé
        alerte += "Humidité inférieur au seuil autorisé !!! ";
        qWarning() << "\033[1;43;37m[WARNING] : L'humidité est de :" << hum << ", elle a dépassée l'interval autorisé [" << vect_chambre[i]->getHum_Min() << ", " << vect_chambre[i]->getHum_Max() << "]\033[0;0m";
      }

      // QUrl url("http://localhost/test.php");
      // QNetworkAccessManager nam;
      // QNetworkReply* reply = nam.get(QNetworkRequest(url));

      if (alerte != "") {
        mail(id, "Attention Alerte", alerte, 1);
      }

      QString date_s = date.toString(QString("yyyy-MM-dd hh:mm:ss"));

      QString insert = "INSERT INTO `capteur`(`date_heure`, `co2`, `chute`, `temperature`, `humidite`, `four`, `presence`, `detection_alerte`, `id_chambre`) VALUES ";
      QString valeur = "('" + date_s + "', '" + QString::number(co2) + "', '" + QString::number(fall) + "', '" + QString::number(temp) + "', '" + QString::number(hum) + "', '" + QString::number(oven) + "', '" + presence + "', '" + alerte + "', '" + QString::number(id) + "')";

      QString requete = insert + valeur;

      qDebug() << "\033[1;42;37m[INFO] : Demande d'insertion des données de la chambre n° :" << id << "\033[0;0m";
      livinglab->insertCapteurs(requete);
    }
  }
}

/**
 * \fn telephoneSeuil
 * \brief  Récupère les seuils des telephones
 *         Enregistre les seuils dans les attributs du telephone correspondanteavec la méthode setAllSeuil
 *
 * \return false si l'enregistrement des seuils à échouer
 *         true si les seuils ont bien été enregistrer
 */
int Traitement::telephoneSeuil() {
  bool success = false;

  QString requete = "SELECT * FROM seuil_user, telephone WHERE seuil_user.id_telephone = telephone.id_telephone";
  QByteArray result = livinglab->requete(requete);

  QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(result);
  QJsonArray jsonArray = jsonDoc.array();

  for (int i = 0; i < jsonArray.count(); i++) {
    QJsonValue champ = jsonArray.at(i);
    QJsonObject champObject = champ.toObject();

    QString pas = champObject.value(QString{"deplacement"}).toString();

    for (int j = 0; j < vect_user.size(); j++) {
      if (vect_user[j]->getID() == champObject.value(QString{"id_telephone"}).toInt()) {
        success = vect_user[j]->setAllSeuil(pas);
      }
    }
  }

  return success;
}

/**
 * \fn openConnexionUser
 * \brief  Ouvre une connexion websocket lié à un telephone
 *
 * \param[in] numero(QString) : id du telephone
 * \param[in] IP(QString) : IP du telephone
 * \param[in] port(int) : port du telephone
 *
 * \return false si l'ouverture websocket du telephone à échouer
 *         true si l'ouverture websocket est un succès
 */
int Traitement::openConnexionUser(int id_telephone, QString IP, int port) {
  QString url = "ws://" + IP + ":" + QString::number(port);

  try {
    vect_user << new Telephone(QUrl(url), id_telephone);
    vect_deplacement << QTime(0, 0, 0, 0);
    connect(vect_user.last(), SIGNAL(sendTextToProcess(QDateTime, int, QString, int)),
     this, SLOT(saveDataUserToProcess(QDateTime, int, QString, int)));
    qDebug() << "\033[1;42;37m[INFO] : Connexion à l'adresse :" << url << ": établie !\033[0;0m";
    return true;
  } catch(...) {
    return false;
  }
}

/**
 * \fn saveDataUserToProcess
 * \brief  SLOT qui récupère les données émisent depuis les websockets telephones ouverts
 *         Traite les données reçues
 *
 * Toutes les données reçues
 * \param[in] timestamp(QDateTime) : date des données
 * \param[in] pas(int) : nombre de pas fait par l'utilisateur
 * \param[in] user(QString) : utilisateur du telephone
 * \param[in] numero(QString) : numero du telephone
 *
 * \return Appel de la méthode insertCapteurs de la classe Database
 *         On lui envoie en paramètre la requete d'insertion contenant les données reçues
 */
void Traitement::saveDataUserToProcess(QDateTime timestamp, int pas, QString user, int id_telephone) {
  if (telephoneSeuil()) {}
  else qWarning() << "\033[1;43;37m[WARNING] : Récupération des seuils des telephones : FAILED\033[0;0m";

  QString alerte = "";

  QString date = timestamp.toString(QString("yyyy-MM-dd hh:mm:ss"));
  QString heure_s = timestamp.toString(QString("hh:mm:ss"));

  for (int i = 0; i < vect_user.size(); i++) {
    if (vect_user[i]->getID() == id_telephone) {
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
          alerte += "L'utilisateur est immobile depuis trop longtemps !!!";
          qWarning() << "\033[1;43;37m[WARNING] : L'utilisateur n'a pas bougé depuis :" << move << "heures. Temps immobile maximum autorisé :" << sp << "\033[0;0m";
        } else qDebug() << "\033[1;42;37m[INFO] : L'utilisateur n'a pas bougé depuis :" << move << "heures. Temps immobile maximum autorisé :" << sp << "\033[0;0m";

      } else qDebug() << "L'utilisateur dort,  il est " << heure_actuel;
    }
  }

  if (alerte != "") {
    mail(id_telephone, "Attention Alerte", alerte, 2);
  }

  QString insert = "INSERT INTO `capteurUser` (`temps`, `pas`, `user`, `detection_alerte_user`, `id_telephone`) VALUES ";
  QString valeur = "('" + date + "', '" + QString::number(pas) + "', '" + user + "', '" + alerte + "', '" + QString::number(id_telephone) + "')";

  QString requete = insert + valeur;

  qDebug() << "\033[1;42;37m[INFO] : Demande d'insertion des données du telephone n° :" << id_telephone << "\033[0;0m";
  livinglab->insertCapteurs(requete);
}
