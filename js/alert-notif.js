/**
 * \file alert-notif.js
 * \brief Gère les notifications d'alertes
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */

/// Requête Ajax pour le chargement des notifications d'alertes
ajaxRequest('GET', '../php/request.php/Notif/', loadNotif);

/// Requête Ajax pour le chargement des notifications d'alertes scpécifiques aux téléphones
ajaxRequest('GET', '../php/request.php/NotifUser/', loadNotifUser);

/// Requêtes des notifications en boucle
var refreshNotif = setInterval(ajaxRequest, 10000, 'GET','../php/request.php/Notif/', loadNotif);
var refreshNotif = setInterval(ajaxRequest, 10000, 'GET','../php/request.php/NotifUser/', loadNotifUser);


function vu(ajaxResponse) {}

/**
 *  \brief NotifVue
 *
 *  Pour savoir si les notifications ont été vues et ne pas les réafficher constamment
 *  J'ajoute une * devant le message d'alerte dans la BDD
 *  Cette distinction permet de faire la différence entre une notification vue par l'utilisateur et une notification non vue
 *
 *  \param id : clé primaire pour les alertes (date_heure de l'alerte)
 *  \param text : text contenant le message d'alerte
 */
function NotifVue(id, text) {
	/// Ajout de la distinction
	text = '*' + text;

	/// Requête Ajax d'update dans la BDD
	ajaxRequest('PUT', '../php/request.php/Notif/' + id + '/' + text, vu);
}

/**
 *  \brief loadNotif
 *
 *  Pour chaque alerte lié aux chambres, cette fonction affiche une notification
 *
 *  \param ajaxResponse : données récupérées dans la BDD avec une requête Ajax
 */
function loadNotif(ajaxResponse) {
  /// On parse les données
  var notif = JSON.parse(ajaxResponse);

  var text = '';

  /// Pour chaque donnée de capteurs
  for (var i = 0; i < notif.length; i++ ) {
	/// On stocke dans une variable le message de la notification qui contiendra
	/// la date de l'alerte ainsi que le message d'alerte
  	text = "Date : " + notif[i].date_heure + " " + notif[i].detection_alerte;

	/// Si les données des capteurs ont déclenché une alertes ou si l'alerte n'a pas déjà été vue
  	if(notif[i].detection_alerte != "" && text.indexOf('*') == -1) {
		/// Fonction qui crée une notification
		$.notify({
			title: 'Alerte',
			message: text,
			onClose: NotifVue(notif[i].date_heure, notif[i].detection_alerte),
			newest_on_top: true,
			allow_dismiss: true,
			animate: {
				enter: 'animated fadeInRight',
				exit: 'animated fadeOutRight'
			}
		},{
 			type: 'danger',
			delay: 0
		});
    }
  }
}

/**
 *  \brief NotifUserVue
 *
 *  Pour savoir si les notifications ont été vues et ne pas les réafficher constamment
 *  J'ajoute une * devant le message d'alerte dans la BDD
 *  Cette distinction permet de faire la différence entre une notification vue par l'utilisateur et une notification non vue
 *
 *  \param id : clé primaire pour les alertes (date_heure de l'alerte)
 *  \param text : text contenant le message d'alerte
 */
function NotifUserVue(id, text) {
	/// Ajout de la distinction
	text = '*' + text;
	
	/// Requête Ajax d'update dans la BDD
	ajaxRequest('PUT', '../php/request.php/NotifUser/' + id + '/' + text, vu);
}

/**
 *  \brief loadNotifUser
 *
 *  Pour chaque alerte lié aux téléphones, cette fonction affiche une notification
 *
 *  \param ajaxResponse : données récupérées dans la BDD avec une requête Ajax
 */
function loadNotifUser(ajaxResponse) {
  /// On parse les données
  var notif = JSON.parse(ajaxResponse);

  var text = '';

  /// Pour chaque donnée du téléphone
  for (var i = 0; i < notif.length; i++ ) {
	/// On stocke dans une variable le message de la notification qui contiendra
	/// la date de l'alerte ainsi que le message d'alerte
	text = "Date : " + notif[i].temps + " " + notif[i].detection_alerte_user;

	/// Si les données des capteurs ont déclenché une alertes ou si l'alerte n'a pas déjà été vue
  	if(notif[i].detection_alerte_user != "" && text.indexOf('*') == -1) {
		/// Fonction qui crée une notification
  		$.notify({
			title: 'Alerte',
			message: text,
			onClose: NotifUserVue(notif[i].temps, notif[i].detection_alerte_user),
			newest_on_top: true,
			allow_dismiss: true,
			animate: {
				enter: 'animated fadeInRight',
				exit: 'animated fadeOutRight'
			}
		},{
			type: 'danger',
			delay: 0
		});
    }
  }
}
