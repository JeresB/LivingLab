/**
 * \file listCapteur.js
 * \brief Permet le chargement des données des capteurs temps réel
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */

/// Requête Ajax pour afficher les données des capteurs
ajaxRequest('GET', 'php/request.php/Capteur/', loadGlobalCapteur);
/// Requête Ajax pour afficher les données des téléphones
ajaxRequest('GET', 'php/request.php/Telephone/', loadPas);

/// Mise en place de setInterval pour le rafraichissement des données
var refreshPhone = setInterval(ajaxRequest, 10000, 'GET','php/request.php/Telephone/', loadPas);
var refreshGlobal = setInterval(ajaxRequest, 10000, 'GET','php/request.php/Capteur/', loadGlobalCapteur);

/**
 *  \brief loadPas
 *
 *  Affiche les données des pas de l'utilisateur
 *
 *  \param ajaxResponse : données récupérées dans la BDD
 */
function loadPas(ajaxResponse) {
  var data = JSON.parse(ajaxResponse);
  
  var div = document.getElementById('capteur_user');
  var text = '<div class = "col-md-6 col-md-offset-3"><div class= "panel panel-default">';
  text += '<div class = "panel-heading"><h2>Pas</h2></div><div id = "pas" class = "panel-body">';
  
  if((data[0].pas - data[1].pas) >= 0) {
    text += '<div id = "pas" class = "panel-body capteur_vert">' + data[0].pas + '<i class="fa fa-arrow-up pull-right" aria-hidden="true">  ' + (data[0].pas - data[1].pas) + " pas</i>";
  } else {
    text += '<div id = "pas" class = "panel-body capteur_rouge">' + data[0].pas + '<i class="fa fa-arrow-down pull-right" aria-hidden="true">  ' + (data[0].pas - data[1].pas) + " pas</i>";
  }
  
  text += '</div></div></div>';
  div.innerHTML = text;
}

/**
 *  \brief loadGlobalCapteur
 *
 *  Affiche les données des capteurs temps réel
 *
 *  \param ajaxResponse : données récupérées dans la BDD
 */
function loadGlobalCapteur(ajaxResponse) {
  var data = JSON.parse(ajaxResponse);

  var date = document.getElementById('date');
  date.innerHTML = data[0].date_heure;

  var co2 = document.getElementById('co2');
  if((data[0].co2 - data[1].co2) >= 0) {
    co2.className = 'panel-body capteur_rouge';
    co2.innerHTML = data[0].co2 + '<i class="fa fa-arrow-up pull-right" aria-hidden="true">  ' + (data[0].co2 - data[1].co2) + "ppm</i>";
  } else {
    co2.className = 'panel-body capteur_vert';
    co2.innerHTML = data[0].co2 + '<i class="fa fa-arrow-down pull-right" aria-hidden="true">  ' + (data[0].co2 - data[1].co2) + "ppm</i>";
  }
  
  var humidite = document.getElementById('humidite');
  if((data[0].humidite - data[1].humidite) >= 0) {
    humidite.className = 'panel-body capteur_rouge';
    humidite.innerHTML = data[0].humidite + '<i class="fa fa-arrow-up pull-right" aria-hidden="true">  ' + (data[0].humidite - data[1].humidite) + "%</i>";
  } else {
    humidite.className = 'panel-body capteur_vert';
    humidite.innerHTML = data[0].humidite + '<i class="fa fa-arrow-down pull-right" aria-hidden="true">  ' + (data[0].humidite - data[1].humidite) + "%</i>";
  }
  
  var temperature = document.getElementById('temperature');
  if((data[0].temperature - data[1].temperature) >= 0) {
    temperature.className = 'panel-body capteur_rouge';
    temperature.innerHTML = data[0].temperature + '<i class="fa fa-arrow-up pull-right" aria-hidden="true">  ' + (data[0].temperature - data[1].temperature).toFixed(2) + "°C</i>";
  } else {
    temperature.className = 'panel-body capteur_bleu';
    temperature.innerHTML = data[0].temperature + '<i class="fa fa-arrow-down pull-right" aria-hidden="true">  ' + (data[0].temperature - data[1].temperature).toFixed(2) + "°C</i>";
  }
  
  /// Pour les panels CO2, humidité, température : récupération du click
  for (var i = 1; i < 4; i++ ) {
    $('#panel-' + i).unbind('click').click(
      function (event){
        event.preventDefault();
        openGlobalCapteur($(this).attr('id'));
    });
  }
  
  var chute;
  if(parseInt(data[0].chute) == 0) {
    chute = "<span class = 'capteur_vert'>L'utilisateur n'est pas tombé.</span>";
  } else {
    chute = "<span class = 'capteur_rouge'>Attention : l'utilisateur est tombé !!!</span>";
  }
  
  var capteur_secondaire = document.getElementById('capteur_secondaire');
  var text = '<div class = "col-md-4"><div class= "panel panel-default">';
  text += '<div class = "panel-heading"><h2>Chute</h2></div><div id = "chute" class = "panel-body">';
  text += chute;
  text += '</div></div></div>';
  
  var four;
  if(parseInt(data[0].four) == 0) {
    four = "<span class = 'capteur_vert'>Le four est éteint !</span>";
  } else {
    four = "<span class = 'capteur_rouge'>Le four est allumé !</span>";
  }
  
  text += '<div class = "col-md-4"><div class= "panel panel-default">';
  text += '<div class = "panel-heading"><h2>Four</h2></div><div id = "four" class = "panel-body">';
  text += four;
  text += '</div></div></div>';
  
 
  var presence;
  console.log("UTILISATEUR :" + data[0].presence);
  if(data[0].presence == "" || data[0].presence == null){
    presence = "<span class = 'capteur_rouge'>Aucun utilisateur n'est present dans la chambre !</span>";
  } else {
    var presence = "<span class = 'capteur_vert'>L'utilisateur " + data[0].presence + " est present dans la chambre !</span>";
  }
  
  text += '<div class = "col-md-4"><div class= "panel panel-default">';
  text += '<div class = "panel-heading"><h2>Presence</h2></div><div id = "presence" class = "panel-body">';
  text += presence;
  text += '</div></div></div>';
  
  capteur_secondaire.innerHTML = text;
}

/**
 *  \brief openGlobalCapteur
 *
 *  Requête Ajax en fonction de l'identifiant du capteur
 *
 *  \param id : identifiant du capteur sur lequel l'utilisateur a cliqué
 */
function openGlobalCapteur(id) {
  var id = id.substr(6);
  $.cookie('current-id', id);

  ajaxRequest('GET', 'php/request.php/module/Capteur/graphCapteur', loadHtmlAndJs);
}

