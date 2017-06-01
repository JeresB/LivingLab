<?php
/**
 * \file profil/ajouter.php
 * \brief Permet l'ajout d'un contact
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */

/**
 * on appelle nos pages html et php necessaire afin de prendre en compte dans notre page
 * les fonctions css javascript mais aussi la connection à la base de données et les images
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
  
    /**
     * ci-dessous nous allons grâce à un echo créer un formulaire en methode post qui aura pour objectif
     * de donner la possibilité à l'utilisateur de remplir les champs d'informations de son nouveau contact
    */
  
  echo '<title>Ajout : Contact</title>

        <div id = "div_dashboard" class = "container">
          <div class = "row">
            <div class = "col-md-6">
                <div class="page-header alert alert-success">
                    <h1>LivingLab Ajout d\'un contact : </h1>
                </div>
                <form class="form-horizontal" action = "" method = "post">
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Email Utilisateur
                            <i class="fa fa-envelope pull-right" aria-hidden="true"></i></span>
                            <input type="email" name="mail" class="form-control" placeholder="utilisateur@livinglab.com">
                        </div>
                    </div>
                </div>
        
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Nom Utilisateur
                            <i class="fa fa-user pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="nom" class="form-control" placeholder="Doe">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Prenom Utilisateur
                            <i class="fa fa-user pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="prenom" class="form-control" placeholder="John">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Mot de passe Contact
                            <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                            <input type="password" name="mdp" class="form-control" placeholder="********">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Confirmer le mot de passe
                            <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                            <input type="password" name="re_mdp" class="form-control" placeholder="********">
                        </div>
                    </div>
                </div>
                <div class="form-group">
                    <div class="col-sm-offset-2 col-sm-10">
                        <input type="submit" name="submit" class="btn btn-default" value="Ajouter !">
                        <button id = "home_profil" class = "btn btn-default">Retour</button>
                    </div>
                </div>
            </form>';
        
    /**
     * Lorsque que l'utilisateur du site appuie sur le bouton submit alors 
     * il y a une verification du remplissage de tous les champs dans un premier temps
     * avec l'envoie de message d'erreur en cas de non remplissage d'un de ces champs
     * puis une verification que les mots de passes soient bien similaires en comparant lorsque l'utilisateur
     * repete celui-ci avec ça precedente elocution
    */
    
  if(isset($_POST['submit'])) { 

    if(empty($_POST['mail'])) {
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs email du contact est vide.
                    </div>
                </div>';
    }else if(empty($_POST['nom'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs nom du contact est vide.
                    </div>
                </div>';
    }else if(empty($_POST['prenom'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs prenom du contact est vide.
                    </div>
                </div>';
    } else if(empty($_POST['mdp'])) {
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champ Mot de passe du contact est vide.
                    </div>
                </div>';
    }else if(empty($_POST['re_mdp'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs repetez le mot de passe du contact est vide.
                    </div>
                </div>';
    }else if(($_POST['re_mdp']) === ($_POST['mdp'])){
    
      //! les champs sont bien posté et pas vide, on sécurise les données entrées par l'utilisateur:
      $mail = htmlentities($_POST['mail'], ENT_QUOTES, "utf-8");
      $nom = htmlentities($_POST['nom'], ENT_QUOTES, "utf-8");
      $prenom = htmlentities($_POST['prenom'], ENT_QUOTES, "utf-8");
      $mdp = htmlentities($_POST['mdp'], ENT_QUOTES, "utf-8");
      
      //!on se connecte à la base de données:
      $db = dbConnect();
      
      if ($db != false) {
          
        /**
         * Dans un second temps on va inserer toutes ces données entrées dans
         * les differentes table de la base de donnée
        */
          
        $request = $db->prepare("INSERT INTO contact (login_email, password, first_name, last_name) VALUES (:mail, :mdp, :prenom, :nom)");
        $request->bindParam(':mail', $mail,PDO::PARAM_INT);
        $request->bindParam(':prenom', $prenom,PDO::PARAM_INT);
        $request->bindParam(':nom', $nom,PDO::PARAM_INT);
        $request->bindParam(':mdp', $mdp,PDO::PARAM_INT);
        $request->execute();
        
        $request1 = $db->prepare("INSERT INTO utilisateur_contact (login_email, login_email_user) VALUES (:email_contact, :email_user)");
        $request1->bindParam(':email_user', $email_user,PDO::PARAM_INT);
        $request1->bindParam(':email_contact', $mail,PDO::PARAM_INT);
        $request1->execute();
        
        /**
         * Une fois ces requêtes effectuées l'utilisateur sera redirigé vers la page profil
        */
        
         echo '<script type="text/javascript">
                          document.location.href="../profil";
               </script>';
      }
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