<?php
/**
 * \file profil/modifier.php
 * \brief Permet la modification d'un contact
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */
 
 //! demarrage de la session
  session_start();
  
  $email_user = $_SESSION['pseudo'];
  
  //! Redirection vers la page principale si l'utilisateur n'est pas connecté
  if (empty($email_user)) {
    header('Location: ../');
  }
  
  /**
    * on appelle nos pages html et php necessaire afin de prendre en compte dans notre page
    * les fonctions css javascript mais aussi la connection à la base de données et les images
  */
  
  require_once('../php/database.php');
  require_once('../template/header.html');
  require_once('../template/navbar.php');
  
    
  //!on se connecte à la base de données:
  $db = dbConnect();
  
  //!on recupere l'attribut transferer en POST lors l'appel de la page
  $email_contact = $_POST['contact'];
  
  
  if ($db != false) {
      
    /**
     * Cette requête aura pour but de prendre les valeurs 
     * du nom et du prenom du contact choisi
    */
    $request1 = $db->prepare("SELECT first_name, last_name FROM contact WHERE login_email = :email_contact");
    $request1->bindParam(':email_contact', $email_contact,PDO::PARAM_STR);
    $request1->execute();
    
    /**
     * Puis on place les valeurs retournées par la requête dans un tableau 'result'
     * Enfin on attribut aux variables correspondantes les valeurs du tableau
    */
    $result = $request1->fetch(PDO::FETCH_ASSOC);

    $first_name_init = $result["first_name"];
    $last_name_init = $result["last_name"];
    
    /**
     * ci-dessous nous allons grâce à un echo créer un formulaire en methode post qui aura pour objectif
     * de donner la possibilité à l'utilisateur de modifier un champs du contact sachant que tous
     * les champs sont préremplis avec les valeurs des seuils actuels
    */

    echo '<title>Modification : Contact</title>

    <div id = "div_dashboard" class = "container">
        <div class = "row">
            <div class = "col-md-6">
                <div class="page-header alert alert-success">
                    <h1>LivingLab Modification des informations d\'un contact : </h1>
                </div>
    
                <!-- Formulaire de modification de contact -->
                <form class="form-horizontal" action = "" method = "post">
                    <input type="hidden" name="email_contact" class="form-control" value="'.$email_contact.'">
                    <div class="form-group">
                        <div class="input-group">
                            <span class="input-group-addon a_label">Prénom du Contact
                            <i class="fa fa-tint pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="first_name" class="form-control" value="'.$first_name_init.'">
                        </div>
                    </div>
                    <div class="form-group">
                        <div class="input-group">
                            <span class="input-group-addon a_label">Nom du Contact
                            <i class="fa fa-tint pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="last_name" class="form-control" value="'.$last_name_init.'">
                        </div>
                    </div
                    <div class="form-group">
                        <div class="col-sm-offset-2 col-sm-10">
                            <input type="submit" name="submit" class="btn btn-default" value="Soumettre">
                            <button id = "home_profil" class = "btn btn-default">Retour</button>
                        </div>
                    </div>
                </form>';
                
        /**
         * Une fois que l'utilisateur a appuyé sur le bouton submit toutes les valeurs des champs sont récupérées
         * via la methode POST pour attribuées à des variables créees ci-dessous
        */
        
        if(isset($_POST['submit'])) { 
    
            $first_name = htmlentities($_POST['first_name'], ENT_QUOTES, "utf-8");
            $last_name = htmlentities($_POST['last_name'], ENT_QUOTES, "utf-8");
            $email_contact = htmlentities($_POST['email_contact'], ENT_QUOTES, "utf-8");
    
            /**
             * Cette requête aura pour but de mettre à jour les valeurs 
             * du nom et du prenom du contact choisi
            */
            
            $statement = $db->prepare('UPDATE contact SET first_name = :first_name, last_name = :last_name WHERE login_email = :email_contact');
            $statement->bindParam(':email_contact', $email_contact,PDO::PARAM_STR);
            $statement->bindParam(':first_name', $first_name,PDO::PARAM_STR);
            $statement->bindParam(':last_name', $last_name,PDO::PARAM_STR);
            $statement->execute();
            
            /**
             * Une fois cette requêtes effectuée l'utilisateur sera redirigé vers la page profil
            */
            echo '<script type="text/javascript">
                    document.location.href="../profil/";
                  </script>';
        }
}

echo '</div></div></div>';

/**
 * Enfin on appelle notre footer codé en html et notre fichier javascript utilisé
 * pour l'affichage des alertes en temps réel
*/
    
require_once('../template/footer.html');
echo '<script src="../js/alert-notif.js"></script>';

?>