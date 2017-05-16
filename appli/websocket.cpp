#include "websocket.hpp"
#include <QDebug>

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
}
//! [onTextMessageReceived]
