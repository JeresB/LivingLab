/**
 * \file index.js
 * \brief Gère les redirections javascript
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */
 
/// Boutons LOG IN de la page d'accueil amène vers identification
$(".log-in").click(function() {
    document.location.href="identification/";
});

/// Boutons SIGN UP de la page d'accueil amène vers inscription
$(".sign-up").click(function() {
    document.location.href="inscription/";
});

/// Boutons RETOUR de la page d'identification et de la page d'inscription amène vers l'accueil
$("#home").unbind('click').click(function(event) {
    event.preventDefault();
    document.location.href="../";
});

/// Boutons RETOUR de la page d'alerte et de la page de profil amène vers le dashboard
$("#home_dashboard").unbind('click').click(function(event) {
    event.preventDefault();
    document.location.href="../dashboard/";
});

/// Boutons RETOUR de la page ajouter et de la page modifier dans le dossier Profil amène vers la page principale du dossier profil
$("#home_profil").unbind('click').click(function(event) {
    event.preventDefault();
    document.location.href="index.php";
});

/// Boutons LOG OUT dans le menu amène vers la page déconnexion
$("#deconnexion").unbind('click').click(function(event) {
    event.preventDefault();
    document.location.href="../deconnexion";
});

/// Boutons LOG OUT de la page d'accueil amène vers la page déconnexion
$("#deconnexion-home").unbind('click').click(function(event) {
    event.preventDefault();
    document.location.href="deconnexion";
});

/// Boutons AJOUTER de la page index dans le dossier profil amène vers la page ajouter
$("#ajouter_contact").unbind('click').click(function(event) {
    event.preventDefault();
    document.location.href="ajouter.php";
});
