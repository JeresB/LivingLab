<?php
/**
 * \file identification/index.php
 * \brief Permet l'identification d'un utilisateur ou d'un contact
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */
 
 //! demarrage de la session
  session_start();

/**
 * on appelle nos pages html et php necessaire afin de prendre en compte dans notre page
 * les fonctions css javascript mais aussi la connection à la base de données et les images
*/
  require_once('../php/database.php');
  require_once('../template/header.html');
  
/**
 * ci-dessous nous allons créer un formulaire en methode post qui aura pour objectif
 * de donner la possibilité à l'utilisateur d'éditer un champs avec ses identifiant
*/
 ?>
<title>Connexion LivingLab</title>

    <div class = "container">
        <div class = "row">
            <div class = "col-md-6">
                <div class="col-sm-10">
                    <div class="page-header alert alert-success"> 
                    <h1>LivingLab connexion : </h1>
                    </div>
                </div>
                <div class="row" id="errors"></div>
                <div class="row" id="success"></div>
    
                <form class="form-horizontal" action = "" method = "post">
                    <div class="form-group">
                        <div class="col-sm-10">
                            <div class="input-group">
                                <span class="input-group-addon c_label">Login
                                <i class="fa fa-user pull-right" aria-hidden="true"></i></span>
                                <input type="email" name="pseudo" class="form-control" placeholder="Login Mail">
                            </div>
                        </div>
                    </div>
        
                    <div class="form-group">
                        <div class="col-sm-10">
                            <div class="input-group">
                                <span class="input-group-addon c_label">Password
                                <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                                <input type="password" name="mot_de_passe" class="form-control" placeholder="Password">
                            </div>
                        </div>
                    </div>

                    <div class="form-group">
                        <div class="col-sm-offset-2 col-sm-10">
                            <input type="submit" name="submit" class="btn btn-default" value="Se connecter !">
                            <button id = "home" class = "btn btn-default">Retour</button>
                        </div>
                    </div>
                </form>

<?php
/**
 * Lorsque que l'utilisateur du site appuie sur le bouton submit alors 
 * il y a une verification du remplissage de tous les champs dans un premier temps
 * avec l'envoie de message d'erreur en cas de non remplissage d'un de ces champs
*/

if(isset($_POST['submit'])) {
    if(empty($_POST['pseudo'])) {
        echo '<div class="col-sm-10">
                <div class="alert alert-danger">
                    <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                    Le champ Pseudo est vide.
                </div>
            </div>';
    } else {

        if(empty($_POST['mot_de_passe'])) {
            echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champ Mot de passe est vide.
                    </div>
                </div>';
        } else {
            //! les champs sont bien posté et pas vide, on sécurise les données entrées par le membre:
            $Pseudo = htmlentities($_POST['pseudo'], ENT_QUOTES, "utf-8"); //! le htmlentities() passera les guillemets en entités HTML, ce qui empêchera les injections SQL
            $MotDePasse = htmlentities($_POST['mot_de_passe'], ENT_QUOTES, "utf-8");
            //!on se connecte à la base de données
            
            /**
             * Puis dans un second temps on compare les identifiants de connexion
             * (login et mot de passe) avec ceux présent dans la base de données 
            */
            $db = dbConnect();

        		if ($db != false) {
                //! pour cela on fait maintenant la requête dans la base de données pour rechercher si ces données existent et correspondent:
                $request = $db->prepare('SELECT * FROM Utilisateur, contact WHERE login_email_user = "'.$Pseudo.'" AND Utilisateur.password = "'.$MotDePasse.'" OR login_email = "'.$Pseudo.'" AND contact.password = "'.$MotDePasse.'"');
                $request->execute();
                
                $result = $request->fetch();
                
                

                //! on compte les ligne reçu pour verifier si l'authentification est correct
                if($request->rowCount() == 0) {
                    echo '<div class="col-sm-10">
                            <div class="alert alert-danger">
                                <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                                Le pseudo ou le mot de passe est incorrect, le compte n\'a pas été trouvé.
                            </div>
                        </div>';
                        
                /**
                 * Une fois cette connexion confirmée on créer differentes sessions
                 * (selon si l'utilisateur qui ce connecte est un contact ou un Utilisateur de l'appli)
                 * utilie pour les futures pages et fonctions a venir 
                */
                } else {
                    echo "Vous êtes à présent connecté !";
                    if($Pseudo == $result["login_email_user"]){
                     $_SESSION['type'] = 'utilisateur';
                     $_SESSION['chambre'] = $result["id_chambre"];
                     $_SESSION['telephone'] = $result["id_telephone"];
                    }else{
                     $_SESSION['type'] = 'contact';
                     $request1 = $db->prepare('SELECT id_chambre, id_telephone FROM Utilisateur, utilisateur_contact, contact WHERE contact.login_email = utilisateur_contact.login_email AND utilisateur_contact.login_email_user = Utilisateur.login_email_user AND contact.login_email = :pseudo');
                     $request1->bindParam(':pseudo', $Pseudo,PDO::PARAM_INT);
                     $request1->execute();
                     $result1 = $request1->fetch();
                     $_SESSION['chambre'] = $result1["id_chambre"];
		             $_SESSION['telephone'] = $result1["id_telephone"];
                    }
                    
                    $_SESSION['pseudo'] = $Pseudo; 
                    
                    //! on redirige l'utilisateur vers la page dashboard
                    
                    header('Location: ../dashboard');
                }
            }
        }
    }
}
echo '</div></div></div>'; 

require_once('../template/footer.html');//!Enfin on appelle notre footer codé en html
?>

