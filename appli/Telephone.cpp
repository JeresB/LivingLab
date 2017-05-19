#include "Telephone.hpp"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QT_USE_NAMESPACE

// [constructor]
Telephone::Telephone(const QUrl &url, QString numero, QObject *parent) : QObject(parent), m_url(url), m_numero(numero) {
  connect(&m_Telephone, &QWebSocket::connected, this, &Telephone::onConnected);
  connect(&m_Telephone, &QWebSocket::disconnected, this, &Telephone::closed);
  m_Telephone.open(QUrl(url));
}
//! [constructor]

// [onConnected]
void Telephone::onConnected() {
  connect(&m_Telephone, &QWebSocket::textMessageReceived,
    this, &Telephone::onTextMessageReceived);

    //emit textMessageReceived(QString("{\"TIME\":1493740127807,\"USER\":\"identifiant\",\"Pas\":247}"));
}
//! [onConnected]

// [onTextMessageReceived]
void Telephone::onTextMessageReceived(QString message) {
	qDebug() << "MESSAGE VENUE DE TELEPHONE "<< message;

  bool ok;
  QJsonDocument donnees = QJsonDocument::fromJson(message.toUtf8());
  QJsonObject JsonObject = donnees.object();

  QStringList keys = JsonObject.keys();

  for (int i = 0; i < keys.count(); i++) {
    qDebug() << "aaaaaaaaaaaaaaaaaaaaaaaaa" << keys[i];
  }
  QString date_time;
  // On récupère la valeur TimeStamp
  date_time.setNum(JsonObject.value(QString{"TIME"}).toDouble(), 'f', 0);
  date_time.remove(10, 3);
  int unixTime = date_time.toInt(&ok, 10);
  QDateTime timestamp;
  timestamp.setTime_t(unixTime);

  QString date = timestamp.toString(QString("yyyy-MM-dd hh:mm:ss"));

  int pas = JsonObject.value(QString{"STEP"}).toInt();
  qDebug() << "LES PASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS" << pas;
  QString user = JsonObject.value(QString{"USER"}).toString();

  emit sendTextToProcess(date, pas, user, m_numero);
}
//! [onTextMessageReceived]

// [GETTERS]
QString Telephone::getID() {
  return m_numero;
}
//! [GETTERS]

// [SETTERS]
void Telephone::setAllSeuil(QString pas) {
  t_pas = pas;
  qDebug() << "Seuil Telephone = " << t_pas;
}
//! [SETTERS]
