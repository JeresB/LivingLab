/**
 * \file Chambre.cpp
 * \brief  Ouvre une websocket type chambre.
 * \version 1
 * \date 24 mai 2017
 * \author {Jeremy B. & Théo D.}
 */

#include "Chambre.hpp"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QT_USE_NAMESPACE

/**
 *  \brief Constructeur
 *
 *  Constructeur de la classe Chambre
 *
 *  \param url(QUrl) : url(ip + port) d'une chambres
 *  \param id_chambre(int) : identifiant de la chambre
 *  \param parent(QObject*) : Possibilité de donner le QObject parent
 */
Chambre::Chambre(const QUrl &url, int id_chambre, QObject *parent) : QObject(parent), c_url(url), c_id_chambre(id_chambre) {
  connect(&m_Chambre, &QWebSocket::connected, this, &Chambre::onConnected);
  connect(&m_Chambre, &QWebSocket::disconnected, this, &Chambre::closed);
  m_Chambre.open(QUrl(url));
}

/**
 * \fn onConnected
 * \brief  Création d'un connect entre le signal textMessageReceived et notre slot onTextMessageReceived
 */
void Chambre::onConnected() {
  connect(&m_Chambre, &QWebSocket::textMessageReceived,
    this, &Chambre::onTextMessageReceived);
}

/**
 * \fn closed
 * \brief  SLOT : si la connexion se ferme(erreur de connexion) on la réouvre
 */
void Chambre::closed() {
  qDebug() << "\033[1;41;37m[ERROR] : Connexion avec l'adresse :" << c_url << "perdue !!!\033[0;0m";
  m_Chambre.open(QUrl(c_url));
  qDebug() << "\033[1;42;37m[INFO] : Reconnexion à l'adresse :" << c_url << ": SUCCESS\033[0;0m";
}

/**
 * \fn onTextMessageReceived
 * \brief  SLOT qui récupère le message reçu par le canal websocket
 *
 * \param[in] message(QString) : message récupéré
 *
 * \return emet le signal sendTextToProcess avec les données reçues dans le message
 */
void Chambre::onTextMessageReceived(QString message) {
  bool ok;
  // qDebug() << "[MESSAGE] : " << message;
  // Récupération des données dans un QJsonDocument
  QJsonDocument donnees = QJsonDocument::fromJson(message.toUtf8());
  // Conversion du QJsonDocument en QJsonObject
  QJsonObject JsonObject = donnees.object();

  QString date_time;
  // On récupère la valeur TimeStamp
  date_time.setNum(JsonObject.value(QString{"TIME"}).toDouble(), 'f', 0);
  // On retire les millisecondes qui ne nous servent pas
  date_time.remove(10, 3);

  int unixTime = date_time.toInt(&ok, 10);
  QDateTime timestamp;
  timestamp.setTime_t(unixTime);
  QString date = timestamp.toString(QString("yyyy-MM-dd hh:mm:ss"));

  // On recupère la valeur binaire du capteur MTH02
  QString mth02 = JsonObject.value(QString{"MTH02"}).toString();

  // Les 16 premiers bits concernent la température
  QString temp_bin = mth02.left(16);
  // On converti la valeur de température binaire en entier
  float temp = (temp_bin.toInt(&ok, 2) - 400) * 0.1;

  // Les 8 bits suivants la température concernent l'humidité
  QString hum_bin = mth02.mid(16, 8);
  // On converti la valeur binaire de l'humidité en entier
  float hum = hum_bin.toInt(&ok, 2);

  // On récupère le reste des données
  QString user = JsonObject.value(QString{"USER"}).toString();
  double co2 = JsonObject.value(QString{"CO2"}).toInt();
  bool fall = JsonObject.value(QString{"FALL"}).toBool();
  bool oven = JsonObject.value(QString{"OVEN"}).toBool();

  // Emission des données à traiter
  emit sendTextToProcess(timestamp, co2, fall, temp, hum, oven, user, c_id_chambre);
}

// [GETTERS]
/**
 * \fn getID()
 * \brief  getter : identifiant de la chambre
 *
 * \return id_chambre
 */
int Chambre::getID() {
  return c_id_chambre;
}

/**
 * \fn getCO2_M()
 * \brief  getter : seuil de co2 moyen
 *
 * \return co2moyen
 */
int Chambre::getCO2_M() {
  return co2moyen;
}

/**
 * \fn getCO2_H()
 * \brief  getter : seuil de co2 haut
 *
 * \return co2haut
 */
int Chambre::getCO2_H() {
  return co2haut;
}

/**
 * \fn getTemp_Max()
 * \brief  getter : seuil de température maximum
 *
 * \return temperaturemax
 */
int Chambre::getTemp_Max() {
  return temperaturemax;
}

/**
 * \fn getTemp_Min()
 * \brief  getter : seuil de température minimum
 *
 * \return temperaturemin
 */
int Chambre::getTemp_Min() {
  return temperaturemin;
}

/**
 * \fn getHum_Max()
 * \brief  getter : seuil d'humidité maximum
 *
 * \return humiditymax
 */
int Chambre::getHum_Max() {
  return humiditymax;
}

/**
 * \fn getHum_Min()
 * \brief  getter : seuil d'humidité minimum
 *
 * \return humiditymin
 */
int Chambre::getHum_Min() {
  return humiditymin;
}

/**
 * \fn getFour()
 * \brief  getter : seuil temps maximum du four allumé
 *
 * \return four
 */
QString Chambre::getFour() {
  return four;
}
//! [GETTERS]

// [SETTERS]
/**
 * \fn setAllSeuil()
 * \brief  setter : enregistre les seuils recueillis
 *
 * \param[in] hmin(int) : humidité minimum
 * \param[in] hmax(int) : humidité maximum
 * \param[in] tmax(int) : température maximum
 * \param[in] tmin(int) : température minimum
 * \param[in] cm(int) : taux de co2 moyen
 * \param[in] ch(int) : taux de co2 haut
 * \param[in] f(QString) : temps max d'allumage du four
 */
int Chambre::setAllSeuil(int hmin, int hmax, int tmax, int tmin, int cm, int ch, QString f) {
  humiditymin     = hmin;
  humiditymax     = hmax;
  temperaturemin  = tmax;
  temperaturemax  = tmin;
  co2moyen        = cm;
  co2haut         = ch;
  four            = f;

  return true;
}
//! [SETTERS]
