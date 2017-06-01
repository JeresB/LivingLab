/**
 * \file historique.js
 * \brief Permet le chargement d'un graphique d'historique
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */

'use strict';

/// Quand le document est prêt
$( document ).ready(function() {
    /// Si l'utilisateur appuie sur le bouton rechercher
    $("#recherche").unbind('click').click(function(event) {
        /// On stop l'event par defaut
        event.preventDefault();
        
        /// Variable de type Regex pour le format des dates
        var regexDate = /^[0-9]{4,4}\/[0-9]{2,2}\/[0-9]{2,2} [0-9]{2,2}:[0-9]{2,2}:[0-9]{2,2}$/;
        
        /// Récupération des varaibles du formulaire
        var debut = $("#debut").val();
        var fin = $("#fin").val();
        var type = $("#type").val();
        
        
        if(regexDate.test(debut)) {}
        /// Si la date de début n'est pas valide on indique à l'utilisateur le bon format
        else {
            $.confirm({
                title: 'Format Invalide !',
                content: 'Format pour la date de <strong>début</strong> non valide -> YYYY/MM/DD hh:mm:ss',
                type: 'red',
                typeAnimated: true,
                theme: 'supervan',
                buttons: {
                    tryAgain: {
                        text: 'Réessayer',
                        btnClass: 'btn-red',
                    },
                    close: function () {
                    }
                }
            });
            exit;
        }
        
        if(regexDate.test(fin)) {}
        /// Si la date de fin n'est pas valide on indique à l'utilisateur le bon format
        else {
            $.confirm({
                title: 'Format Invalide !',
                content: 'Format pour la date de <strong>fin</strong> non valide -> YYYY/MM/DD hh:mm:ss',
                type: 'red',
                typeAnimated: true,
                theme: 'supervan',
                buttons: {
                    tryAgain: {
                        text: 'Réessayer',
                        btnClass: 'btn-red',
                    },
                    close: function () {
                    }
                }
            });
            exit;
        } 
        
        /// On remplace les / par des x pour le bon fonctionnement de la requete (/ etant le caractère de séparation)
        var debut = debut.replace("/", "x");
        var debut = debut.replace("/", "x");
        var fin = fin.replace("/", "x");
        var fin = fin.replace("/", "x");
        
        /// Requête Ajax pour charger l'historique
        ajaxRequest('GET','php/request.php/historique/'+ type + '/' + debut + '/' + fin, loadHistorique);
    });
});

/**
 *  \brief loadHistorique
 *
 *  Crée les variables nécessaire à la création d'un graphique et parse les données
 *
 *  \param ajaxResponse : données récupérées dans la BDD
 */
function loadHistorique(ajaxResponse) {
    var response = JSON.parse(ajaxResponse);
    var value = [];
    var date = [];
    var name = "";
    var nameSerie = "";
    var sensorID;
 
    /// On détermine quel type de capteur est demandé
    if (typeof response[0].co2 != "undefined") {
        sensorID = 1;
    } else if (typeof response[0].humidite != "undefined") {
        sensorID = 2;
    } else if (typeof response[0].temperature != "undefined") {
        sensorID = 3;
    }
    
    /// Enregistrement des données voulues dans des tableaux
    for (var i = 0; i < response.length; i++) {
        if(sensorID == 1) {
            value.push(parseInt(response[i].co2));
            date.push(response[i].date_heure.substr(8));
        } else if(sensorID == 2) {
            value.push(parseInt(response[i].humidite));
            date.push(response[i].date_heure.substr(8));
        } else if(sensorID == 3) {
            value.push(parseInt(response[i].temperature));
            date.push(response[i].date_heure.substr(8));
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
        setGraph("graphHistorique", "Taux de CO2", "CO2", date, value, seuil1, seuil2);
    } else if (sensorID == 2) {
        var seuil1 = parseInt(response[0].humiditymin);
        var seuil2 = parseInt(response[0].humiditymax);
        setGraph("graphHistorique", "Pourcentage d'humidité present dans la chambre", "Humidité", date, value, seuil1, seuil2);
    } else if (sensorID == 3) {
        var seuil1 = parseInt(response[0].temperaturemin);
        var seuil2 = parseInt(response[0].temperaturemax);
        setGraph("graphHistorique", "Température ambiante de la chambre", "Température", date, value, seuil1, seuil2);
    }
}