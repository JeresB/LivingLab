<?php
/**
 * \file inscription/index.php
 * \brief Permet l'inscription d'un utilisateur et d'un contact dans la base de données
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */
 
 /**
 * on appelle nos pages html et php necessaire afin de prendre en compte dans notre page
 * les fonctions css javascript mais aussi la connection à la base de données et les images
*/
require_once('../template/header.html');
require_once('../php/database.php');

/**
 * ci-dessous nous allons créer un formulaire en methode post qui aura pour objectif
 * de donner la possibilité à l'utilisateur du site de ce créer un compte, à lui et a son contact
 * en remplissant l'ensemble du formulaire
*/
?>

<title>Formulaire d'inscription</title>
        <div class = "container">
        <div class = "row">
        <div class = "col-md-6">
            <div class = "col-sm-10">
                <div class="page-header alert alert-success"> 
                <h1>Formulaire d'inscription</h1>
                </div>
            </div>
            <div class="row" id="errors"></div>
            <div class="row" id="success"></div>
            
            <form class="form-horizontal" action = "" method = "post">
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Email Utilisateur
                            <i class="fa fa-envelope pull-right" aria-hidden="true"></i></span>
                            <input type="email" name="email_user" class="form-control" placeholder="utilisateur@livinglab.com">
                        </div>
                    </div>
                </div>
        
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Nom Utilisateur
                            <i class="fa fa-user pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="nom_user" class="form-control" placeholder="Doe">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Prenom Utilisateur
                            <i class="fa fa-user pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="prenom_user" class="form-control" placeholder="John">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Numéro de télephone Utilisateur
                            <i class="fa fa-user pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="tel_number" class="form-control" placeholder="0123456789">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Mot de passe Utilisateur
                            <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                            <input type="password" name="mdp_user" class="form-control" placeholder="********">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Confirmer le mot de passe
                            <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                            <input type="password" name="re_mdp_user" class="form-control" placeholder="********">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Email Contact
                            <i class="fa fa-envelope pull-right" aria-hidden="true"></i></span>
                            <input type="email" name="email_contact" class="form-control" placeholder="contact@livinglab.com">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Nom Contact
                            <i class="fa fa-user pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="nom_contact" class="form-control" placeholder="Norris">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Prenom Contact
                            <i class="fa fa-user pull-right" aria-hidden="true"></i></span>
                            <input type="text" name="prenom_contact" class="form-control" placeholder="Chuck">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Mot de passe Contact
                            <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                            <input type="password" name="mdp_contact" class="form-control" placeholder="********">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Confirmer le mot de passe
                            <i class="fa fa-unlock-alt pull-right" aria-hidden="true"></i></span>
                            <input type="password" name="re_mdp_contact" class="form-control" placeholder="********">
                        </div>
                    </div>
                </div>
                
                <div class="form-group">
                    <div class="col-sm-10">
                        <div class="input-group">
                            <span class="input-group-addon i_label">Id de la chambre et du telephone
                            <i class="fa fa-home pull-right" aria-hidden="true"></i></span>
                            <input type="number" name="id_chambre" class="form-control" placeholder="1 ou 2">
                        </div>
                    </div>
                </div>

                <div class="form-group">
                    <div class="col-sm-offset-2 col-sm-10">
                        <input type="submit" name="submit" class="btn btn-default" value="S'inscrire !">
                        <button id = "home" class = "btn btn-default">Retour</button>
                    </div>
                </div>
            </form>
        </div>
        <div id = "erreur_inscription" class = "col-md-6">
<?php

/**
 * Lorsque que l'utilisateur du site appuie sur le bouton submit alors 
 * il y a une verification du remplissage de tous les champs dans un premier temps
 * avec l'envoie de message d'erreur en cas de non remplissage d'un de ces champs
 * puis une verification que les mots de passes soient bien similaires lorsque l'utilisateur
 * repete celui-ci avec ça precedente elocution
*/

if(isset($_POST['submit'])) { 
    
    if(empty($_POST['email_user'])) {
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs email de l\'utilisateur est vide.
                    </div>
                </div>';
    }else if(empty($_POST['mdp_user'])){  // on vérifie maintenant si le champ "Mot de passe" n'est pas vide"
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champ Mot de passe de l\'Utilisateur est vide.
                    </div>
                </div>';
    }else if(empty($_POST['nom_user'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs nom de l\'utilisateur est vide.
                    </div>
                </div>';
    }else if(empty($_POST['prenom_user'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs prenom de l\'utilisateur est vide.
                    </div>
                </div>';
    }else if(empty($_POST['tel_number'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs numéro de telephone de l\'utilisateur est vide.
                    </div>
                </div>';
    }else if(empty($_POST['re_mdp_user'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs repetez le mot de passe de l\'utilisateur est vide.
                    </div>
                </div>';
    }else if(empty($_POST['email_contact'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs email du contact est vide.
                    </div>
                </div>';
    } else if(empty($_POST['mdp_contact'])) {
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champ Mot de passe du contact est vide.
                    </div>
                </div>';
    }else if(empty($_POST['nom_contact'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs nom du contact est vide.
                    </div>
                </div>';
    }else if(empty($_POST['prenom_contact'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs prenom du contact est vide.
                    </div>
                </div>';
    }else if(empty($_POST['re_mdp_contact'])){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs repetez le mot de passe du contact est vide.
                    </div>
                </div>';
    }else if(empty($_POST['id_chambre']) || (($_POST['id_chambre']) != 1 && ($_POST['id_chambre']) != 2)){
        echo '<div class="col-sm-10">
                    <div class="alert alert-danger">
                        <i class="fa fa-exclamation-triangle" aria-hidden="true"></i>
                        Le champs id_chambre incorrect.
                    </div>
                </div>';
        
    } else if(($_POST['re_mdp_user']) === ($_POST['mdp_user']) && ($_POST['re_mdp_contact']) === ($_POST['mdp_contact'])){
        echo "information plausible";

            //! les champs sont bien posté et pas vide, on sécurise les données entrées par l'utilisateur:
            $email_user = htmlentities($_POST['email_user'], ENT_QUOTES, "utf-8");
            $mdp_user = htmlentities($_POST['mdp_user'], ENT_QUOTES, "utf-8");
            $nom_user = htmlentities($_POST['nom_user'], ENT_QUOTES, "utf-8");
            $prenom_user = htmlentities($_POST['prenom_user'], ENT_QUOTES, "utf-8");
            $tel_number = htmlentities($_POST['tel_number'], ENT_QUOTES, "utf-8");
            $email_contact = htmlentities($_POST['email_contact'], ENT_QUOTES, "utf-8");
            $mdp_contact = htmlentities($_POST['mdp_contact'], ENT_QUOTES, "utf-8");
            $nom_contact = htmlentities($_POST['nom_contact'], ENT_QUOTES, "utf-8");
            $prenom_contact = htmlentities($_POST['prenom_contact'], ENT_QUOTES, "utf-8");
            $id_chambre = htmlentities($_POST['id_chambre'], ENT_QUOTES, "utf-8");
            
            /**
             * Dans un second temps on va inserer toutes ces données entrées dans
             * les differentes table de la base de donnée
            */
            
            //!on se connecte à la base de données:
            $db = dbConnect();

        		if ($db != false) {
                
                $request2 = $db->prepare("INSERT INTO contact (login_email, password, first_name, last_name) VALUES (:email_contact, :mdp_contact, :prenom_contact, :nom_contact)");
                $request2->bindParam(':email_contact', $email_contact,PDO::PARAM_INT);
                $request2->bindParam(':mdp_contact', $mdp_contact,PDO::PARAM_INT);
                $request2->bindParam(':prenom_contact', $prenom_contact,PDO::PARAM_INT);
                $request2->bindParam(':nom_contact', $nom_contact,PDO::PARAM_INT);
                $request2->execute();

                $request = $db->prepare("INSERT INTO Utilisateur (login_email_user, password, first_name, last_name, id_chambre, id_telephone) VALUES (:email_user, :mdp_user, :prenom_user, :nom_user, :id_chambre, :id_telephone)");
                $request->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                $request->bindParam(':mdp_user', $mdp_user,PDO::PARAM_INT);
                $request->bindParam(':prenom_user', $prenom_user,PDO::PARAM_INT);
                $request->bindParam(':nom_user', $nom_user,PDO::PARAM_INT);
                $request->bindParam(':id_chambre', $id_chambre,PDO::PARAM_INT);
                $request->bindParam(':id_telephone', $id_chambre,PDO::PARAM_INT);
                $request->execute();
                
                $request1 = $db->prepare("INSERT INTO telephone (id_telephone) VALUES (:id_telephone)");
                $request1->bindParam(':id_telephone', $id_chambre,PDO::PARAM_INT);
                $request1->execute();
                
                $request4 = $db->prepare("UPDATE telephone SET numero = :tel_number WHERE id_telephone = :id_telephone");
                $request4->bindParam(':tel_number', $tel_number,PDO::PARAM_INT);
                $request4->bindParam(':id_telephone', $id_chambre,PDO::PARAM_INT);
                $request4->execute();
                
                $request3 = $db->prepare("INSERT INTO utilisateur_contact (login_email, login_email_user) VALUES (:email_contact, :email_user)");
                $request3->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                $request3->bindParam(':email_contact', $email_contact,PDO::PARAM_INT);
                $request3->execute();
                
            
                /**
                 * Une fois ces requêtes effectuées l'utilisateur sera redirigé vers la page identification
                 * afin qu'il ce connecte
                */
                echo '<script type="text/javascript">
                        document.location.href="../identification";
                    </script>';
               
            }
        }
    }
  echo '</div></div></div>'; 
  require_once('../template/footer.html');//!Enfin on appelle notre footer codé en html
?>
