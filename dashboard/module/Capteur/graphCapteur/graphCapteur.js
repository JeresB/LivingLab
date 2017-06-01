/**
 * \file graphCapteur.js
 * \brief Permet le chargement d'un graphique temps réel
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */

'use strict';

/// Récupération du graphique utilisé
var sensorID = $.cookie('current-id');
var refreshResults;

/// Requête Ajax d'un graphique temps réel
ajaxRequest('GET','php/request.php/OneSensor/'+ sensorID, loadPollResults);

/// Si on demande un autre graphique on clear interval en premier
clearInterval(refreshResults);
/// Mise en place d'un setInterval pour le rafraichissement des données
refreshResults = setInterval(ajaxRequest, 10000, 'GET','php/request.php/OneSensor/'+ sensorID, loadPollResults);

/**
 *  \brief loadPollResults
 *
 *  Crée les variables nécessaire à la création d'un graphique et parse les données
 *
 *  \param ajaxResponse : données récupérées dans la BDD
 */
function loadPollResults(ajaxResponse){
  var response = JSON.parse(ajaxResponse);
  var value = [];
  var date = [];
  var name = "";
  var nameSerie = "";
  
  /// Enregistrement des données voulues dans des tableaux
  for (var i = 0; i < response.length; i++) {
    if(sensorID == 1) {
      value.push(parseInt(response[i].co2));
      date.push(response[i].date_heure.substr(11));
      
    } else if(sensorID == 2) {
      value.push(parseInt(response[i].humidite));
      date.push(response[i].date_heure.substr(11));
      
    } else if(sensorID == 3) {
      value.push(parseInt(response[i].temperature));
      date.push(response[i].date_heure.substr(11));
    }
  }
  
  /// Inversement pour avoir les données récentes à droite
  value.reverse();
  date.reverse();
  
  /// En fonction du type de capteur demandé
  /// On récupère les seuils correspondants
  /// On appel la fonction qui crée les graphiques
  if (sensorID == 1) {
      var seuil1 = parseInt(response[0].co2moyen);
      var seuil2 = parseInt(response[0].co2haut);
      setGraph("graph", "Taux de CO2", "CO2", date, value, seuil1, seuil2);
  } else if (sensorID == 2) {
      var seuil1 = parseInt(response[0].humiditymin);
      var seuil2 = parseInt(response[0].humiditymax);
      setGraph("graph", "Pourcentage d'humidité present dans la chambre", "Humidité", date, value, seuil1, seuil2);
  } else if (sensorID == 3) {
      var seuil1 = parseInt(response[0].temperaturemin);
      var seuil2 = parseInt(response[0].temperaturemax);
      setGraph("graph", "Température ambiante de la chambre", "Température", date, value, seuil1, seuil2);
  }
  
}

