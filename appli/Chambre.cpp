#include "Chambre.hpp"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QT_USE_NAMESPACE

// [constructor]
Chambre::Chambre(const QUrl &url, int id_chambre, QObject *parent) : QObject(parent), m_url(url), m_id_chambre(id_chambre) {
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
	qDebug() << message;
  bool ok;
  QJsonDocument donnees = QJsonDocument::fromJson(message.toUtf8());
  QJsonObject JsonObject = donnees.object();

  QString date_time;
  // On récupère la valeur TimeStamp
  date_time.setNum(JsonObject.value(QString{"TIME"}).toDouble(), 'f', 0);
  date_time.remove(10, 3);
  int unixTime = date_time.toInt(&ok, 10);
  QDateTime timestamp;
  timestamp.setTime_t(unixTime);
  qDebug() << "AVANT ajout de 2h" << timestamp;

  qDebug() << "Apres " << timestamp;
  QString date = timestamp.toString(QString("yyyy-MM-dd hh:mm:ss"));

  qDebug() << "CETTE PUTAIN DE DATE VAUT : " << date;
  QString mth02 = JsonObject.value(QString{"MTH02"}).toString();
  QString temp_bin = mth02.left(16);
  float temp = (temp_bin.toInt(&ok, 2) - 400) * 0.1;

  QString hum_bin = mth02.mid(16, 8);
  float hum = hum_bin.toInt(&ok, 2);

  QString user = JsonObject.value(QString{"USER"}).toString();
  double co2 = JsonObject.value(QString{"CO2"}).toInt();
  bool fall = JsonObject.value(QString{"FALL"}).toBool();
  bool oven = JsonObject.value(QString{"OVEN"}).toBool();
  //QString tv = JsonObject.value(QString{"TV"}).toString();

  qDebug() << "LIST VALUE = " << date_time << "----------" << date << user << mth02 << co2 << fall << oven;

  emit sendTextToProcess(date, co2, fall, temp, hum, oven, m_id_chambre);
}
//! [onTextMessageReceived]

// [GETTERS]
int Chambre::getID() {
  return m_id_chambre;
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
//! [GETTERS]

// [SETTERS]
void Chambre::setAllSeuil(int hmin, int hmax, int tmax, int tmin, int cm, int ch, QString f) {
  humiditymin     = hmin;
  humiditymax     = hmax;
  temperaturemin  = tmax;
  temperaturemax  = tmin;
  co2moyen        = cm;
  co2haut         = ch;
  four            = f;

  qDebug() << "TEST SET SEUIL : " << hmin << hmax << tmax << tmin << cm << ch << f;
}
//! [SETTERS]
