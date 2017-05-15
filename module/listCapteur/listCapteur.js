// ajaxRequest('GET', 'php/request.php/polls/', loadGlobalCapteur);
//
// refreshGlobal = setInterval(ajaxRequest, 10000, 'GET','php/request.php/polls/', loadGlobalPolls);
console.log('Hello World!');
function loadGlobalCapteur(ajaxResponse) {
  var response = JSON.parse(ajaxResponse);
}
