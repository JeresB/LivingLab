ajaxRequest('GET', 'php/request.php/listCapteur/', loadGlobalCapteur);

refreshGlobal = setInterval(ajaxRequest, 10000, 'GET','php/request.php/listCapteur/', loadGlobalCapteur);
console.log('Hello World!');
function loadGlobalCapteur(ajaxResponse) {
  var data = JSON.parse(ajaxResponse);
  var capteur = document.getElementById('listCapteur');
  capteur.innerHTML = '';

  for (var i = 0; i < data.length; i++) {
    var text;
    var element;
    text = "<table border='1' cellpadding='10' cellspacing='1' width='50%''>";
    text += "<tr><td><h2>date et heure</h2></td>";
    text += "<td>" +data[i].date_heure + "</td></tr>";

    text += "<tr><td><h2>co2</h2></td>";
    text += "<td>" +data[i].co2 + "</td></tr>";

    text += "<tr><td><h2>Chute</h2></td>";
    text += "<td>" +data[i].chute + "</td></tr>";

    text += "<tr><td><h2>Temperature</h2></td>";
    text += "<td>" +data[i].temperature + "</td></tr>";

    text += "<tr><td><h2>Humidité</h2></td>";
    text += "<td>" +data[i].humidite + "</td></tr>";

    text += "<tr><td><h2>Four</h2></td>";
    text += "<td>" +data[i].four + "</td></tr>";

    element = document.createElement('div');
    element.className = 'col-md-4';
    element.innerHTML = text;
    capteur.appendChild(element);
  }


}
