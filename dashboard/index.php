<?php
  /**
  * \file dashboard/index.php
  * \brief Page principale une fois connecté / Affiche les données des capteurs
  * \author {Théo D. & Jeremy B.}
  * \version 1
  */

  /// Démarrage de la session
  session_start();
  $email_user = $_SESSION['pseudo'];

  /// Redirection vers la page d'accueil si l'utilisateur n'est pas connecté
  if (empty($email_user)) {
    header('Location: ../');
  }

  /// Inclusion du header et de la barre menu
  require_once('../template/header.html');
  require_once('../template/navbar.php');
?>

<title>Dashboard</title>

  <main id = "div_dashboard">
    <div class="container">
      <div class="page-header alert alert-success">
        <h1><i class="fa fa-tachometer" aria-hidden="true"></i> Living Lab <small>Récupération des données <span id = "date"></span></small></h1>
      </div>

      <!-- Div pour le module capteur temps réel -->
      <div class = "row" id = "listCapteur"></div>

      <!-- Nécessaire pour le bon fonctionnement des graphiques HIGHCHARTS -->
      <script src="../js/highcharts.js"></script>

      <!-- Div pour le module graphique temps réel -->
      <div class = "row" id = "graph"></div>

      <!-- Div pour les capteurs secondaires (chute, four, présence) -->
      <div class = "row" id = "capteur_secondaire"></div>
      <!-- Div pour le capteur de pas du téléphone -->
      <div class = "row" id = "capteur_user"></div>

      <!-- Div pour le module de recherche d'historique (formulaire) -->
      <div class = "row" id = "historique"></div>
      <!-- Div pour le module graphique historique -->
      <div class = "row" id = "graphHistorique"></div>

    </div>

    <!-- jQuery -->
    <script src="../js/jquery.min.js"></script>
    <script src="../js/jquery.cookie.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="../js/bootstrap.min.js"></script>
    <script src="../js/bootstrap-notify.js"></script>

    <!-- jQuery popup alerte -->
    <script src="../js/jquery-confirm.js"></script>

    <!-- My JavaScript -->
    <script src="../js/utils.js"></script> <!-- Fonction Ajax -->
    <script src="../js/loading.js"></script> <!-- Premières requêtes ajax -->
    <script src="../js/index.js"></script> <!-- Controller de redirection -->
    <script src="../js/alert-notif.js"></script> <!-- Notification d'alerte -->
    <script src="../js/setGraph.js"></script> <!-- Fonction pour crée un graphique avec HIGHCHARTS -->

    </main>

  </body>
  </html>
