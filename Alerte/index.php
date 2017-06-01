<?php
/**
 * \file alert-notif.js
 * \brief {Cette page a pour but d'Afficher sous forme de formulaire les different seuil
 *        de la chambre et du telephone afin que l'utilisateur puisse modifier les seuils
 *        qu'il souhaite, en étant bien au courant des valeurs de ceux-ci.
 *        Dans un second* temps cette page aura également pour but d'afficher un historique
 *        des notification d'alertes afin que contact et utilisateur puissent tous être
 *        au courant d'alerte qu'ils ont peut-être louper sur le site.}
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */


//! demarrage de la session
  session_start();
  $email_user = $_SESSION['pseudo'];
  $type = $_SESSION['type'];
  $id_chambre = $_SESSION['chambre'];
  $id_telephone = $_SESSION['telephone'];

//!Redirection vers la page d'accueil si l'utilisateur du site n'est pas connecté
  if (empty($email_user)) {
    header('Location: ../');
  }
/**
 * on appelle nos pages html et php necessaire afin de prendre en compte dans notre page
 * les fonctions css javascript mais aussi la connection à la base de données et les images
*/
  require_once('../template/header.html');
  require_once('../template/navbar.php');
  require_once('../php/database.php');
  //!on se connecte à la base de données:
  $db = dbConnect();

  /** 
  * Avant de faire les differentes requêtes on verifie que l'utilisateur du site
  * ne soit pas un contact, donc qu'il soit l'Utilisateur de l'application
  */
  if ($db != false && $type != 'contact') {
    /**
     * La requête suivante a pour but de récupérer les seuils actuel de la chambre
     * de l'utilisateur présent sur le site
    */ 
    $request1 = $db->prepare("SELECT humiditymin, humiditymax, temperaturemin, temperaturemax, co2moyen, co2haut, four FROM seuil, chambre, Utilisateur WHERE seuil.id_chambre = chambre.id_chambre AND chambre.id_chambre = Utilisateur.id_chambre AND Utilisateur.id_chambre = :chambre");
    $request1->bindParam(':chambre', $id_chambre,PDO::PARAM_INT);
    $request1->execute();
    
    /**
     * grâce à la fonction fetch on récupere les valeurs retournés par la requête sql
     * pour les placer dans un tableau 'result'
    */
    $result = $request1->fetch(PDO::FETCH_ASSOC);

    /**
     * on déclare et initialise differentes variables en leur donnant
     * les valeurs correspondantes récuperer grâce au tableau 'result'
    */
    $humiditemin_init = $result["humiditymin"];
    $humiditemax_init = $result["humiditymax"];
    $temperaturemin_init = $result["temperaturemin"];
    $temperaturemax_init = $result["temperaturemax"];
    $co2moyen_init = $result["co2moyen"];
    $co2haut_init = $result["co2haut"];
    $fourmax_init = $result["four"];

    /**
     * La requête sql suivante va servir a returner lee seuil du capteur du telephone
     * de l'utilisateur présent sur le site
    */

    $request2 = $db->prepare("SELECT deplacement FROM seuil_user, telephone, Utilisateur WHERE seuil_user.id_telephone = telephone.id_telephone AND telephone.id_telephone = Utilisateur.id_telephone AND Utilisateur.id_telephone = :id_telephone");
    $request2->bindParam(':id_telephone', $id_telephone,PDO::PARAM_INT);
    $request2->execute();
    
    /**
     * Puis comme précédemment on place la valeur retournée par la requête dans un tableau 'result2'
    */
    $result2 = $request2->fetch(PDO::FETCH_ASSOC);

    /**
     * on déclare et initialise une variable en leur donnant
     * la valeur correspondante récuperer grâce au tableau 'result2'
    */
    $deplacement = $result2["deplacement"];

/**
 * ci-dessous nous allons grâce à un echo créer un formulaire en methode post qui aura pour objectif
 * de donner la possibilité à l'utilisateur de modifier un champs sachant que tous
 * les champs sont préremplis avec les valeurs des seuils actuels
*/
echo '<title>Seuil d\'alerte</title>

    <div id = "div_dashboard" class = "container">
        <div class = "row">
            <div class = "col-md-6">
                <div class="page-header alert alert-success">
                    <h1>LivingLab Modification des seuils de la chambre : </h1>
                </div>

                <form class="form-horizontal" action = "" method = "post">
                    <div class="form-group">

                            <div class="input-group">
                                <span class="input-group-addon a_label">Humidité minimale en %
                                <i class="fa fa-tint pull-right" aria-hidden="true"></i></span>
                                <input type="number" name="humiditymin" class="form-control" value="'.$humiditemin_init.'">
                            </div>

                    </div>

                    <div class="form-group">

                            <div class="input-group">
                                <span class="input-group-addon a_label">Humidité maximal en %
                                <i class="fa fa-tint pull-right" aria-hidden="true"></i></span>
                                <input type="number" name="humiditymax" class="form-control" value="'.$humiditemax_init.'">
                            </div>

                    </div>

                    <div class="form-group">

                            <div class="input-group">
                                <span class="input-group-addon a_label">Temperature minimale en degrès celsius
                                <i class="fa fa-thermometer-quarter pull-right" aria-hidden="true"></i></span>
                                <input type="number" name="temperaturemin" class="form-control" value="'.$temperaturemin_init.'">
                            </div>

                    </div>

                    <div class="form-group">

                            <div class="input-group">
                                <span class="a_label input-group-addon">Temperature maximale en degrès celsius
                                <i class="fa fa-thermometer-three-quarters pull-right" aria-hidden="true"></i></span>
                                <input type="number" name="temperaturemax" class="form-control" value="'.$temperaturemax_init.'">
                            </div>

                    </div>

                    <div class="form-group">

                            <div class="input-group">
                                <span class="input-group-addon a_label">Taux de CO2 moyen en PPM (parties pour million)
                                <i class="fa fa-fire pull-right" aria-hidden="true"></i></span>
                                <input type="number" name="CO2moy" class="form-control" value="'.$co2moyen_init.'">
                            </div>

                    </div>

                    <div class="form-group">

                            <div class="input-group">
                                <span class="input-group-addon a_label">Taux de CO2 maximal en PPM (parties pour million)
                                <i class="fa fa-fire pull-right" aria-hidden="true"></i></span>
                                <input type="number" name="CO2max" class="form-control" value="'.$co2haut_init.'">
                            </div>

                    </div>

                    <div class="form-group">

                            <div class="input-group">
                                <span class="input-group-addon a_label">Temps max d\'allumage du four
                                <i class="fa fa-free-code-camp pull-right" aria-hidden="true"></i></span>
                                <input type="text" name="fourmax" class="form-control" value="'.$fourmax_init.'">
                            </div>

                    </div>

                    <div class="form-group">

                            <div class="input-group">
                                <span class="input-group-addon a_label">Temps d\'immobilité maximum autorisé
                                <i class="fa fa-free-code-camp pull-right" aria-hidden="true"></i></span>
                                <input type="text" name="deplacement" class="form-control" value="'.$deplacement.'">
                            </div>

                    </div>

                    <div class="form-group">
                        <div class="col-sm-offset-2 col-sm-10">
                            <input type="submit" name="submit" class="btn btn-default" value="Soumettre">
                            <button id = "home_dashboard" class = "btn btn-default">Retour</button>
                        </div>
                    </div>
                </form>';


/**
 * Une fois que l'utilisateur à appuyé sur le bouton submit toutes les valeurs des champs sont récupérées
 * via la methode POST pour attribuées à des variables créees ci-dessous
*/

if(isset($_POST['submit'])) {

    $humiditemax = htmlentities($_POST['humiditymax'], ENT_QUOTES, "utf-8"); // le htmlentities() passera les guillemets en entités HTML, ce qui empêchera les injections SQL
    $humiditemin = htmlentities($_POST['humiditymin'], ENT_QUOTES, "utf-8");
    $tempmin = htmlentities($_POST['temperaturemin'], ENT_QUOTES, "utf-8");
    $tempmax = htmlentities($_POST['temperaturemax'], ENT_QUOTES, "utf-8");
    $CO2moy = htmlentities($_POST['CO2moy'], ENT_QUOTES, "utf-8");
    $CO2haut = htmlentities($_POST['CO2max'], ENT_QUOTES, "utf-8");
    $fourmax = htmlentities($_POST['fourmax'], ENT_QUOTES, "utf-8");
    $deplacement = htmlentities($_POST['deplacement'], ENT_QUOTES, "utf-8");

    /**
     * La requête sql suivante aura pour but de remplacer dans la bases de données
     * les ancien seuils de la chambre de l'utilisateur connecté 
     * par les valeurs récupérer precedemment par le formulaire
    */

    $statement = $db->prepare('UPDATE seuil, chambre SET humiditymin = :humiditemin, humiditymax = :humiditemax, temperaturemax = :tempmax, temperaturemin = :tempmin, co2moyen = :CO2moy, co2haut = :CO2haut, four = :fourmax WHERE seuil.id_chambre = chambre.id_chambre AND chambre.id_chambre = :id_chambre');

    $statement->bindParam(':id_chambre', $id_chambre,PDO::PARAM_INT);
    $statement->bindParam(':humiditemin', $humiditemin,PDO::PARAM_INT);
    $statement->bindParam(':humiditemax', $humiditemax,PDO::PARAM_INT);
    $statement->bindParam(':tempmax', $tempmax,PDO::PARAM_INT);
    $statement->bindParam(':tempmin', $tempmin,PDO::PARAM_INT);
    $statement->bindParam(':CO2moy', $CO2moy,PDO::PARAM_INT);
    $statement->bindParam(':CO2haut', $CO2haut,PDO::PARAM_INT);
    $statement->bindParam(':fourmax', $fourmax,PDO::PARAM_INT);
    $statement->execute();

    /**
     * Cette requête elle devra de remplacer dans la bases de données
     * l'ancien seuils du telephone de l'utilisateur connecté 
     * par la valeur récupérer par le formulaire
    */
    
    $statement1 = $db->prepare('UPDATE seuil_user, telephone, Utilisateur SET deplacement = :deplacement WHERE seuil_user.id_telephone = telephone.id_telephone AND telephone.id_telephone = Utilisateur.id_telephone AND Utilisateur.id_telephone = :id_telephone');

    $statement1->bindParam(':id_telephone', $id_telephone,PDO::PARAM_INT);
    $statement1->bindParam(':deplacement', $deplacement,PDO::PARAM_INT);
    $statement1->execute();

    /**
     * Une fois ces requêtes effectuées l'utilisateur sera redirigé vers la page dashboard
    */
    echo '<script type="text/javascript">
                        document.location.href="../dashboard";
                        </script>';
    }
}

/**
 * La seconde partie de cette page étant accéssible a tous (contact et utlisateur connectés)
 * devra afficher toutes les alertes passées afin que tous soit au courant d'alertes qu'ils ont peut-être loupé
*/

if ($db != false) {
    
/**
 * on commence par s'occuper des alertes des capteurs de la chambre
*/
echo '</div><div class = "col-md-6">
        <div class="page-header alert alert-warning">
          <h1>Notification de la chambre n°'.$id_chambre.'</h1>
        </div>
          <ul class="list-group">';
          
/**
 * Cette requête aura pour but de selectionner certaines informations
 * des capteurs de la chambre de l'utilisateur depuis 24heures
*/

$requestNotif = $db->prepare('SELECT date_heure, detection_alerte, capteur.id_chambre FROM capteur, chambre WHERE capteur.id_chambre = chambre.id_chambre AND chambre.id_chambre = :chambre ORDER BY date_heure DESC LIMIT 0,1440');
$requestNotif->bindParam(':chambre', $id_chambre, PDO::PARAM_INT);
$requestNotif->execute();

/**
 * Puis on place les valeurs retournées par la requête dans un tableau 'result'
 * lui même étant dans une boucle for afin de trier toutes les valeurs du tableau
 * En effet si les valeurs récuperer contiennent des alertes elles sont alors afficher
 * en liste grâce a un echo et du langage html
*/

for ($i = 0; $result = $requestNotif->fetch(PDO::FETCH_ASSOC); $i++){
  $date = $result["date_heure"];
  $alerte = $result["detection_alerte"];

  if ($alerte != "") {
    $alerte = substr($alerte, 1);
    echo '<li class="list-group-item list-group-item-warning"><strong>Date :</strong> '.$date.' <strong>Message :</strong> '.$alerte.'</li>';
  }
}

/**
 * Dans un second temps on repete les me operations que ci-dessus en prenans 
 * maintenant uniquement les capteur du telephone en compte
*/
echo '</ul>
      <div class="page-header alert alert-warning">
        <h1>Notification du telephone n°'.$id_telephone.'</h1>
      </div>
      <ul class="list-group">';
      
      /**
        * Cette requête aura pour but de selectionner certaines informations
        * du capteur du telephone de l'utilisateur depuis 24 heures
      */

      $requestNotifUser = $db->prepare('SELECT temps, detection_alerte_user, capteurUser.id_telephone FROM capteurUser, telephone WHERE capteurUser.id_telephone = telephone.id_telephone AND telephone.id_telephone = :telephone ORDER BY temps DESC');
      $requestNotifUser->bindParam(':telephone', $id_telephone, PDO::PARAM_INT);
      $requestNotifUser->execute();
      
      /**
        * Puis on place les valeurs retournées par la requête dans un tableau 'result'
        * lui même étant dans une boucle for afin de trier toutes les valeurs du tableau
        * En effet si les valeurs récuperer contiennent des alertes elles sont alors afficher
        * en liste grâce a un echo et du langage html
      */

      for ($i = 0; $result = $requestNotifUser->fetch(PDO::FETCH_ASSOC); $i++){
        $date = $result["temps"];
        $alerte = $result["detection_alerte_user"];

        if ($alerte != "") {
          $alerte = substr($alerte, 1);
          echo '<li class="list-group-item list-group-item-warning"><strong>Date :</strong> '.$date.' <strong>Message :</strong> '.$alerte.'</li>';
        }
      }
      echo '</ul></div>';
}
echo '</div></div>'; 

/**
 * Enfin on appelle notre footer codé en html et notre fichier javascript utilisé
 * pour l'affichage des alertes en temps réel
*/

require_once('../template/footer.html');
echo '<script src="../js/alert-notif.js"></script>';
?>
