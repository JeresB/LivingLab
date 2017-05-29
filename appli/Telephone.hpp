#ifndef TELEPHONE_H
#define TELEPHONE_H

/*!
 * \file Telephone.hpp
 * \brief Ouvre une websocket type Telephone.
 * \author {Jeremy B. & Théo D.}
 * \version 1
 */
#include <QObject>
#include <QWebSocket>

/*! \class Telephone
 * \brief classe representant une connexion websocket type telephone
 *
 *  La classe ouvre une connexion avec un telephone et collect les seuils de ce telephone
 */
class Telephone : public QObject {
    Q_OBJECT
public:
    /**
     *  \brief Constructeur
     *
     *  Constructeur de la classe Telephone
     *
     *  \param url(QUrl) : url(ip + port) d'un telephone
     *  \param id_chambre(int) : identifiant du telephone
     *  \param parent(QObject*) : Possibilité de donner le QObject parent
     */
    explicit Telephone(const QUrl &url, int id_telephone, QObject *parent = Q_NULLPTR);

    // GETTERS
    /**
     * \fn getID()
     * \brief  getter : identifiant du telephone
     *
     * \return m_numero
     */
    int getID();
    /**
     * \fn getPas()
     * \brief  getter : temps d'immobilité maximum
     *
     * \return t_pas
     */
    QString getPas();
    // SETTERS
    /**
     * \fn setAllSeuil()
     * \brief  setter : enregistre le seuil recueilli
     *
     * \param[in] pas(QString) : temps immobile maximum
     */
    int setAllSeuil(QString pas);

Q_SIGNALS:
    /**
     * \fn sendTextToProcess
     * \brief  SIGNAL : envoie les données reçues à la classe Traitement
     *
     * \param[in] timestamp(QDateTime) : date des données
     * \param[in] pas(int) : pas fait par l'utilisateur
     * \param[in] user(QString) : nom de l'utilisateur
     * \param[in] m_numero(QString) : identifiant du telephone
     */
    void sendTextToProcess(QDateTime, int, QString, int);

private Q_SLOTS:
    /**
     * \fn onConnected
     * \brief  Création d'un connect entre le signal textMessageReceived et notre slot onTextMessageReceived
     */
    void onConnected();
    /**
     * \fn closed
     * \brief  SLOT : si la connexion se ferme(erreur de connexion) on la réouvre
     */
    void closed();

public Q_SLOTS:
  /**
   * \fn onTextMessageReceived
   * \brief  SLOT qui récupère le message reçu par le canal websocket
   *
   * \param[in] message(QString) : message récupéré
   *
   * \return emet le signal sendTextToProcess avec les données reçues dans le message
   */
  void onTextMessageReceived(QString message);

private:
    QWebSocket m_Telephone;
    QUrl m_url;
    int id_tel;
    QString t_pas;
};

#endif // Chambre_H
