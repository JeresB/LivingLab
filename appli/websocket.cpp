#include "Websocket.hpp"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QT_USE_NAMESPACE

//! [constructor]
WebSocket::WebSocket(const QUrl &url, QObject *parent) : QObject(parent), m_url(url) {
  connect(&m_webSocket, &QWebSocket::connected, this, &WebSocket::onConnected);
  connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocket::closed);
  m_webSocket.open(QUrl(url));
}
//! [constructor]

//! [onConnected]
void WebSocket::onConnected() {
  connect(&m_webSocket, &QWebSocket::textMessageReceived,
    this, &WebSocket::onTextMessageReceived);
}
//! [onConnected]

//! [onTextMessageReceived]
void WebSocket::onTextMessageReceived(QString message) {
	qDebug() << message;

  QJsonDocument donnees = QJsonDocument::fromJson(message.toUtf8());
  QJsonObject JsonObject = donnees.object();

  qDebug() << JsonObject.value(QString{"USER"});
  qDebug() << JsonObject.value(QString{"MTH02"});
  qDebug() << JsonObject.value(QString{"CO2"});
  qDebug() << JsonObject.value(QString{"FALL"});
  qDebug() << JsonObject.value(QString{"OVEN"});
  qDebug() << JsonObject.value(QString{"TV"});
}
//! [onTextMessageReceived]