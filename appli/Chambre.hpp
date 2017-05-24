#ifndef CHAMBRE_H
#define CHAMBRE_H

/*!
 * \file Chambre.hpp
 * \brief Ouvre une websocket type chambre.
 * \author {Jeremy B. & Théo D.}
 * \version 1
 */
#include <QObject>
#include <QWebSocket>

/*! \class Chambre
 * \brief classe representant une connexion websocket type chambre
 *
 *  La classe ouvre une connexion avec une chambre et collect les seuils de cette chambre
 */
class Chambre : public QObject {
    Q_OBJECT
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Chambre
     *
     *  \param url(QUrl) : url(ip + port) d'une chambres
     *  \param id_chambre(int) : identifiant de la chambre
     *  \param parent(QObject*) : Possibilité de donner le QObject parent
     */
    explicit Chambre(const QUrl &url, int id_chambre, QObject *parent = Q_NULLPTR);

    /// GETTERS

    /**
     * \fn getID()
     * \brief  getter : identifiant de la chambre
     *
     * \return id_chambre
     */
    int getID();

    /**
     * \fn getCO2_M()
     * \brief  getter : seuil de co2 moyen
     *
     * \return co2moyen
     */
    int getCO2_M();

    /**
     * \fn getCO2_H()
     * \brief  getter : seuil de co2 haut
     *
     * \return co2haut
     */
    int getCO2_H();

    /**
     * \fn getTemp_Max()
     * \brief  getter : seuil de température maximum
     *
     * \return temperaturemax
     */
    int getTemp_Max();

    /**
     * \fn getTemp_Min()
     * \brief  getter : seuil de température minimum
     *
     * \return temperaturemin
     */
    int getTemp_Min();

    /**
     * \fn getHum_Max()
     * \brief  getter : seuil d'humidité maximum
     *
     * \return humiditymax
     */
    int getHum_Max();

    /**
     * \fn getHum_Min()
     * \brief  getter : seuil d'humidité minimum
     *
     * \return humiditymin
     */
    int getHum_Min();

    /**
     * \fn getFour()
     * \brief  getter : seuil temps maximum du four allumé
     *
     * \return four
     */
    QString getFour();

    /// SETTERS

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
    int setAllSeuil(int hmin, int hmax, int tmax, int tmin, int cm, int ch, QString f);

Q_SIGNALS:
   /**
    * \fn sendTextToProcess
    * \brief  SIGNAL : envoie les données reçues à la classe Traitement
    *
    * \param[in] date(QDateTime) : date des données
    * \param[in] co2(int) : CO2 présent dans la chambre
    * \param[in] fall(bool) : Chute de l'utilisateur
    * \param[in] temp(float) : Température de la chambre
    * \param[in] hum(float) : Humidité de la chambre
    * \param[in] oven(bool) : Four allumé ou éteint
    * \param[in] presence(QString) : Nom de l'utilisateur present dans la chambre ou chaine vide
    * \param[in] id(int) : identifiant de la chambre
    */
    void sendTextToProcess(QDateTime, int, bool, float, float, bool, QString, int);

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
   * \param[in] date(QDateTime) : date des données
   *
   * \return emet le signal sendTextToProcess avec les données reçues dans le message
   */
  void onTextMessageReceived(QString message);

private:
    QWebSocket m_Chambre;
    QUrl c_url;
    int c_id_chambre;

    int humiditymin     = 0;
    int humiditymax     = 0;
    int temperaturemin  = 0;
    int temperaturemax  = 0;
    int co2moyen        = 0;
    int co2haut         = 0;
    QString four        = "";
};

#endif // CHAMBRE_H
