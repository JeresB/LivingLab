#include "Chambre.hpp"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QT_USE_NAMESPACE

// [constructor]
Chambre::Chambre(const QUrl &url, int id_chambre, QObject *parent) : QObject(parent), c_url(url), c_id_chambre(id_chambre) {
  connect(&m_Chambre, &QWebSocket::connected, this, &Chambre::onConnected);
  connect(&m_Chambre, &QWebSocket::disconnected, this, &Chambre::closed);
  m_Chambre.open(QUrl(url));
}
//! [constructor]

// [onConnected]
void Chambre::onConnected() {
  connect(&m_Chambre, &QWebSocket::textMessageReceived,
    this, &Chambre::onTextMessageReceived);
}
//! [onConnected]

// [onTextMessageReceived]
void Chambre::onTextMessageReceived(QString message) {
  bool ok;

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
  emit sendTextToProcess(timestamp, co2, fall, temp, hum, oven, c_id_chambre);
}
//! [onTextMessageReceived]

// [GETTERS]
int Chambre::getID() {
  return c_id_chambre;
}

int Chambre::getCO2_M() {
  return co2moyen;
}

int Chambre::getCO2_H() {
  return co2haut;
}

int Chambre::getTemp_Max() {
  return temperaturemax;
}

int Chambre::getTemp_Min() {
  return temperaturemin;
}

int Chambre::getHum_Max() {
  return humiditymax;
}

int Chambre::getHum_Min() {
  return humiditymin;
}

QString Chambre::getFour() {
  return four;
}
//! [GETTERS]

// [SETTERS]
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
