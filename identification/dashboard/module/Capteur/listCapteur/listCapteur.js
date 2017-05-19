ajaxRequest('GET', 'php/request.php/Capteur/', loadGlobalCapteur);

refreshGlobal = setInterval(ajaxRequest, 10000, 'GET','php/request.php/Capteur/', loadGlobalCapteur);

function loadGlobalCapteur(ajaxResponse) {
  var data = JSON.parse(ajaxResponse);
  var capteur = document.getElementById('listCapteur');
  capteur.innerHTML = '';

  for (var i = 0; i < data.length; i++) {
    var text;
    var element;
    var id = data[i].co2;
    text = "<table border='1' cellpadding='10' cellspacing='1' width='50%''>";
    text += "<tr><td><h2>date et heure</h2></td>";
    text += "<td>" +data[i].date_heure + "</td></tr>";

    text += "<tr><td><h2>co2</h2></td>";
    text += "<td>" +id + "</td></tr>";

    text += "</table>";

    //text += "<tr><td><h2>Chute</h2></td>";
    // text += "<td>" +data[i].chute + "</td></tr>";
    //
    // text += "<tr><td><h2>Temperature</h2></td>";
    // text += "<td>" +data[i].temperature + "</td></tr>";
    //
    // text += "<tr><td><h2>Humidité</h2></td>";
    // text += "<td>" +data[i].humidite + "</td></tr>";
    //
    // text += "<tr><td><h2>Four</h2></td>";
    // text += "<td>" +data[i].four + "</td></tr>";


    element = document.createElement('a');
    element.className = 'col-md-4';
    element.setAttribute("id", "lien-" + id);
    element.innerHTML = text;
    capteur.appendChild(element);

    $('#lien-' + id).unbind('click').click(
      function (event){
        event.preventDefault();
        openGlobalCapteur(event.target.id);
    });
  }

  function openGlobalCapteur(id) {
    var id = id.substr(5);

    $.cookie('current-id', id);

    ajaxRequest('GET', 'php/request.php/module/Capteur/graphCapteur', loadHtmlAndJs);
    // ajaxRequest('GET', 'php/request.php/module/commentaire/listComm', loadHtmlAndJs);
  }

}
