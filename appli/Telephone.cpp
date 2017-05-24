/**
 * \file Telephone.cpp
 * \brief  Ouvre une websocket type Telephone.
 * \version 1
 * \date 24 mai 2017
 * \author {Jeremy B. & Théo D.}
 */

#include "Telephone.hpp"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QT_USE_NAMESPACE

/**
 *  \brief Constructeur
 *
 *  Constructeur de la classe Telephone
 *
 *  \param url(QUrl) : url(ip + port) d'un telephone
 *  \param id_chambre(int) : identifiant du telephone
 *  \param parent(QObject*) : Possibilité de donner le QObject parent
 */
Telephone::Telephone(const QUrl &url, QString numero, QObject *parent) : QObject(parent), m_url(url), m_numero(numero) {
  connect(&m_Telephone, &QWebSocket::connected, this, &Telephone::onConnected);
  connect(&m_Telephone, &QWebSocket::disconnected, this, &Telephone::closed);
  m_Telephone.open(QUrl(url));
}

/**
 * \fn onConnected
 * \brief  Création d'un connect entre le signal textMessageReceived et notre slot onTextMessageReceived
 */
void Telephone::onConnected() {
  connect(&m_Telephone, &QWebSocket::textMessageReceived,
    this, &Telephone::onTextMessageReceived);
}

/**
 * \fn closed
 * \brief  SLOT : si la connexion se ferme(erreur de connexion) on la réouvre
 */
void Telephone::closed() {
  qDebug() << "\033[1;41;37m[ERROR] : Connexion avec l'adresse :" << m_url << "perdue !!!\033[0;0m";
  m_Telephone.open(QUrl(m_url));
  qDebug() << "\033[1;42;37m[INFO] : Reconnexion à l'adresse :" << m_url << ": SUCCESS\033[0;0m";
}

/**
 * \fn onTextMessageReceived
 * \brief  SLOT qui récupère le message reçu par le canal websocket
 *
 * \param[in] message(QString) : message récupéré
 *
 * \return emet le signal sendTextToProcess avec les données reçues dans le message
 */
void Telephone::onTextMessageReceived(QString message) {
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

  //QString date = timestamp.toString(QString("yyyy-MM-dd hh:mm:ss"));


  int pas = JsonObject.value(QString{"STEP"}).toInt();
  QString user = JsonObject.value(QString{"USER"}).toString();

  emit sendTextToProcess(timestamp, pas, user, m_numero);
}


// [GETTERS]
/**
 * \fn getID()
 * \brief  getter : identifiant du telephone
 *
 * \return m_numero
 */
QString Telephone::getID() {
  return m_numero;
}

/**
 * \fn getPas()
 * \brief  getter : temps d'immobilité maximum
 *
 * \return t_pas
 */
QString Telephone::getPas() {
  return t_pas;
}

//! [GETTERS]

// [SETTERS]
/**
 * \fn setAllSeuil()
 * \brief  setter : enregistre le seuil recueilli
 *
 * \param[in] pas(QString) : temps immobile maximum
 */
int Telephone::setAllSeuil(QString pas) {
  t_pas = pas;

  return true;
}
//! [SETTERS]
