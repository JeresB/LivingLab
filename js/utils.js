'use strict';

// Fonction traitant toutes les requêtes Ajax
function ajaxRequest(type, request, callback, data = null) {
  // Objet de requête Ajax
  var xhr = new XMLHttpRequest();

  // Si le type de la requête est GET et que les données ne sont pas vide.
  // On ajoute les données à la fin de la requête
  if (type == 'GET' && data !== null)
    request += '?' + data;

  // On ouvre une requête Ajax
  xhr.open(type, request, true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');

  // Si l'état de la requête change
  xhr.onreadystatechange = function(){
    // On atteint que le retour de la requête soit prêt
    if (xhr.readyState != 4) {
      return;
    }

    // On check le status de la requête
    switch (xhr.status) {
      case 200:
        console.log(xhr.responseText);
        callback(xhr.responseText);
        break;
      default:
        httpErrors(xhr.status);
    }
  };

  var dataXhr = null;

  // Si la requête est de type POST et que les données ne sont pas vide
  if (type == 'POST' && data !== null)
    dataXhr = data;

  // On envoie la requête Ajax
  xhr.send(dataXhr);
}

function callback(response) {
  var divSuccess = document.getElementById('success');

  var text = '<div class = "alert alert-success" role="alert">';
  text += '<strong>' + response + '</strong></div>';
  divSuccess.innerHTML = text;
}


function httpErrors(errorNumber) {
  var divErrors = document.getElementById('errors');

  var text = '<div id = "errors" class = "alert alert-danger" role = "alert">';
  text += '<span class = "glyphicon glyphicon-exclamation-sign"></span>';

  switch (errorNumber) {
    case 400:
      text += '<strong> Requête incorrecte</strong>';
      break;
    case 401:
      text += '<strong> Authentifiez vous</strong>';
      break;
    case 403:
      text += '<strong> Accès refusé</strong>';
      break;
    case 404:
      text += '<strong> Page non trouvé</strong>';
      break;
    case 500:
      text += '<strong> Erreur interne du serveur</strong>';
      break;
    case 503:
      text += '<strong> Service indisponible</strong>';
      break;
    default:
      text += '<strong> HTTP erreur : ' + errorNumber + '</strong>';
      break;
  }

  text += '</div>';
  divErrors.innerHTML = text;
}

function loadHtmlAndJs(ajaxResponse) {
  var response = JSON.parse(ajaxResponse);

  $('#'+response.divId).load(response.html);
  $.getScript(response.js);
}
