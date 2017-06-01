<?php
  /**
 * \file profil/index.php
 * \brief {Permet la gestion de son mot de passe pour tout les membres 
 *        Mais permet également a l'Utilisateur de l'appli de gérer ses contacts
 *        en les ajoutant/supprimant/modifiant}
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */
 

 //! demarrage de la session
  session_start();
  
  $email_user = $_SESSION['pseudo'];
  $type = $_SESSION['type'];
  
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
  
  /**
     * ci-dessous nous allons grâce à un echo créer un formulaire en methode post qui aura pour objectif
     * de donner la possibilité à l'utilisateur de remplir les champs d'informations de son nouveau contact
  */
 ?>
<title>Profil</title>
  <main id = "div_profil" class = "container">
    <div class = "row">
            <div class = "col-md-6">
                 <div class="page-header alert alert-success">   
                    <h1>Modification : mot de passe</h1>
                 </div> 
                    <div class="row" id="errors"></div>
                    <div class="row" id="success"></div>
                  
                    <form class="form-horizontal" action = "" method = "post">
                      <div class="form-group">
                          <div class="input-group">
                              <span class="input-group-addon p_label">Ancien mot de passe
                              <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                              <input type="password" name="ancien_mdp" class="form-control" placeholder="********">
                          </div>
                      </div>
          
                      <div class="form-group">
                          <div class="input-group">
                              <span class="input-group-addon p_label">Nouveau mot de passe
                              <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                              <input type="password" name="nouveau_mdp" class="form-control" placeholder="********">
                          </div>
                      </div>
                      
                      <div class="form-group">
                          <div class="input-group">
                              <span class="input-group-addon p_label">Répetez votre nouveau mot de passe
                              <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                              <input type="password" name="re_mdp" class="form-control" placeholder="********">
                          </div>
                      </div>

                      <div class="form-group">
                          <div class="col-sm-offset-2 col-sm-10">
                              <input type="submit" name="submit" class="btn btn-default" value="Valider !">
                              <button id = "home_dashboard" class = "btn btn-default">Retour</button>
                          </div>
                      </div>
                    </form>
                    
                    <div class="row" id="errors"></div>
                    <div class="row" id="success"></div>

<?php

/**
 * Lorsque que l'utilisateur du site appuie sur le bouton submit alors 
 * il y a une verification du remplissage de tous les champs dans un premier temps
 * avec l'envoie de message d'erreur en cas de non remplissage d'un de ces champs
 * puis une verification que les mots de passes soient bien similaires lorsque l'utilisateur
 * repete celui-ci avec ça precedente elocution
*/

if(isset($_POST['submit'])) {
  
    if(empty($_POST['ancien_mdp'])) {
      echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs correspondant à l\'ancien mot de passe est vide.
                    </div>
                </div>';
    }else if(empty($_POST['nouveau_mdp'])){
      echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champ correspondant au nouveau mot de passe est vide.
                    </div>
                </div>';
    }else if(empty($_POST['re_mdp'])){
      echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs repetez le nouveau mot de passe de l\'utilisateur est vide.
                    </div>
                </div>';
    } else if(($_POST['re_mdp']) === ($_POST['nouveau_mdp'])){

            $ancien_mdp = htmlentities($_POST['ancien_mdp'], ENT_QUOTES, "utf-8");
            $nouveau_mdp = htmlentities($_POST['nouveau_mdp'], ENT_QUOTES, "utf-8");
            $re_mdp = htmlentities($_POST['re_mdp'], ENT_QUOTES, "utf-8");

            /**
             * on procede d'abord a une verification que l'ancien mot de passe correspond bien
             * avec celui du membre
             * pour cela on recupere le mot de passe de l'utilisateur ou du contact selon son type 
             * puis on le compare avec celui saisi ci dessus
            */

        		if ($db != false) {
        		  
        		    if($type != 'contact'){
          		    $request1 = $db->prepare("SELECT password FROM Utilisateur WHERE login_email_user = :email_user");
                  $request1->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                  $request1->execute();
                  
                  $result = $request1->fetch(PDO::FETCH_ASSOC);
  
                  $mdp = $result["password"];
                }else{
                  $request1 = $db->prepare("SELECT password FROM contact WHERE login_email = :email_user");
                  $request1->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                  $request1->execute();
                  
                  $result = $request1->fetch(PDO::FETCH_ASSOC);
                  
                  $mdp = $result["password"];
                }
                
                if ($mdp === $ancien_mdp){
                  
                  /**
                   * Une fois cette verification faite on met à jour le nouveau
                   * mot de passe dans la base de données de l'utilisateur ou bien du contact
                   * selon son type
                  */
                  if($type == 'contact'){
                    
                    $request2 = $db->prepare("UPDATE contact SET password = :nouveau_mdp WHERE login_email = :email_user");
                    $request2->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                    $request2->bindParam(':nouveau_mdp', $nouveau_mdp,PDO::PARAM_INT);
                    $request2->execute();
                    
                  }else{
                    
                    $request = $db->prepare("UPDATE Utilisateur SET password = :nouveau_mdp WHERE login_email_user = :email_user");
                    $request->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                    $request->bindParam(':nouveau_mdp', $nouveau_mdp,PDO::PARAM_INT);
                    $request->execute();
                    
                  }

                  /**
                   * Une fois ces requêtes effectuées l'utilisateur sera redirigé vers la page dashboard
                  */
                  echo '<script type="text/javascript">
                          document.location.href="../dashboard";
                      </script>';
                }else{
                  echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Votre mot de passe n\'est pas correct.
                    </div>
                  </div>';
                }
            }
      }
}

/**
 *Dans une second partie reservé a l'utilisateur on s'occupe
 *de la gestion des contact de chaque utilisateur
 * 
*/
if($type == "utilisateur") {
    if ($db != false) {
      
      /**
       * Dans une premiere requête on selectionne tout les contacts d'un utilisateur
       * pour les afficher dans une liste grâce a un formulaire html placé dans un echo
       * et grâce a une boucle for qui lis les valeur de la requête
       * recupéré dans un tableau 'result' 
      */
      $request1 = $db->prepare('SELECT contact.login_email, contact.first_name, contact.last_name FROM contact, utilisateur_contact, Utilisateur WHERE contact.login_email = utilisateur_contact.login_email AND utilisateur_contact.login_email_user = Utilisateur.login_email_user AND Utilisateur.login_email_user = :email_user');
      $request1->bindParam(':email_user', $email_user,PDO::PARAM_INT);
      $request1->execute();
      
      echo '<div class="page-header alert alert-success">   
                <h1>CONTACTS : </h1>
            </div>
            <div class = "panel panel-default>
            <div class = "panel-body">
            <table class="table table-striped">
              <thead>
                <tr>
                  <th>Prénom</th>
                  <th>Nom</th>
                  <th>Modifier</th>
                  <th>Supprimer</th>
                </tr>
              </thead>
              <tbody>';
      
      for ($i = 0; $result = $request1->fetch(PDO::FETCH_ASSOC); $i++){
        
        $mail_contact = $result["login_email"];
        $prenom = $result["first_name"];
        $nom = $result["last_name"];
        
        /**
         * Le formulaire ci-dessous a pour but d'afficher les nom et prénom d'un contact afin de les differencié
         * mais il comprend également 3 boutons qui permettent la redirection vers les page 
         * ajouter.php pour le bouton ajouter
         * modifier.php pour le bouton modifier
         * et supprimer.php pour le bouton supprimer
        */
        
        echo '<tr><td>'.$prenom.'</td>
                  <td>'.$nom.'</td>
              <form method=POST action=modifier.php>
                <input type="hidden" name="contact" value="'.$mail_contact.'"></input>
                <td><input class = "btn btn-primary" type="submit" value="Modifier" /></td>
              </form>
              <form method=POST action=supprimer.php>
                <input type="hidden" name="contact" value="'.$mail_contact.'"></input>
                <td><input class = "btn btn-danger" type="submit" value="Supprimer" /></td>
              </form>';

      }
    }
    
    echo '</tbody></table>';
    echo '<button type="button" id="ajouter_contact" class="btn btn-block btn-info">Ajouter</button>';
  }   
    echo '</div></div></div></div></main>';

/**
 * Enfin on appelle notre footer codé en html et notre fichier javascript utilisé
 * pour l'affichage des alertes en temps réel
*/
    
require_once('../template/footer.html');
echo '<script src="../js/alert-notif.js"></script>';
?>