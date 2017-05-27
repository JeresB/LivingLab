#ifndef TRAITEMENT_H
#define TRAITEMENT_H

/*!
 * \file Traitement.hpp
 * \brief Traitement des websockets et des données
 * \author {Jeremy B. & Théo D.}
 * \version 1
 */
#include <QObject>
#include <QByteArray>
#include <cmath>
#include "Database.hpp"
#include "Chambre.hpp"
#include "Telephone.hpp"

/*! \class Traitement
 * \brief classe representant le traitement du programme
 *
 *  La classe gère les connexions websockets et les données reçues
 */
class Traitement : public QObject {
  Q_OBJECT
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Traitement
     *
     *  \param parent : Possibilité de donner le QObject parent
     */
    Traitement(QObject *parent = Q_NULLPTR);
    int mail(int id, QString objet, QString message_alerte);
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
    int List(QString);
    /**
     * \fn roomSeuil
     * \brief  Récupère les seuils des chambres
     *         Enregistre les seuils dans les attributs de la chambre correspondante avec la méthode setAllSeuil
     *
     * \return false si l'enregistrement des seuils à échouer
     *         true si les seuils ont bien été enregistrer
     */
    int roomSeuil();
    /**
     * \fn telephoneSeuil
     * \brief  Récupère les seuils des telephones
     *         Enregistre les seuils dans les attributs du telephone correspondanteavec la méthode setAllSeuil
     *
     * \return false si l'enregistrement des seuils à échouer
     *         true si les seuils ont bien été enregistrer
     */
    int telephoneSeuil();
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
    int openConnexionChambre(int id, QString IP, int port);
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
    int openConnexionUser(QString numero, QString IP, int port);

Q_SIGNALS:

private Q_SLOTS:
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
  void saveDataRoomToProcess(QDateTime, int, bool, float, float, bool, QString, int);
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
  void saveDataUserToProcess(QDateTime, int, QString, QString);

private:
  Database *livinglab;
  QVector<Chambre *> vect_chambre;
  QVector<Telephone *> vect_user;

  QVector<int> temperature_save;

  QVector<QTime> vect_four_allume;
  QVector<QTime> vect_deplacement;

  QTime matin;
  QTime soir;

  int diff_temp = 3;
};

#endif // TRAITEMENT_H
