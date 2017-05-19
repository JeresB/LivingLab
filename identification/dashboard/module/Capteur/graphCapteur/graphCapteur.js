'use strict';
var cookieId = $.cookie('current-id');

 ajaxRequest('GET','php/request.php/Capteur/'+cookieId, loadPollResults);
 var refreshResults = setInterval(ajaxRequest, 10000, 'GET','php/request.php/Capteur/'+cookieId, loadPollResults);


function loadPollResults(ajaxResponse){
  var response;
  var array = new Array(60);
  response = JSON.parse(ajaxResponse);

  for (var i = 0; i < response.length; i++) {
    array[i] = response[i].co2;
  }
}
$("#erase").click(function() {
  $('#panelGraphicCapteur').hide();
  $.cookie('current-id', 0);
//  ajaxRequest('GET', 'php/request.php/module/commentaire/listComm', loadHtmlAndJs);
});
