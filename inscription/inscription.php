<?php
  require_once('database.php');
 ?>
 <!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title>Formulaire d'inscription</title>
</head>

<body>

    <h1>Formulaire d'inscription</h1>
    <div class="row" id="errors"></div>
    <div class="row" id="success"></div>


<?php

echo '<form action="" method="post">
Email Utilisateur : <input type="text" name="email_user" />
</br>
Nom Utilisateur : <input type="text" name="nom_user" />
</br>
Prenom Utilisateur : <input type="text" name="prenom_user" />
</br>
Mot de passe Utilisateur: <input type="password" name="mdp_user" />
</br>
Repetez Mot de passe : <input type="password" name="re_mdp_user" />
</br>
</br>
Email Contact : <input type="text" name="email_contact" />
</br>
Nom Contact : <input type="text" name="nom_contact" />
</br>
Prenom Contact : <input type="text" name="prenom_contact" />
</br>
Mot de passe Contact: <input type="password" name="mdp_contact" />
</br>
Repetez Mot de passe : <input type="password" name="re_mdp_contact" />
</br>
Id de la chambre : <input type="text" name="id_chambre" />
</br>
<input type="submit" name="submit" value="inscription" />';

if(isset($_POST['submit'])) { // si le bouton "Connexion" est appuyé
  echo "le bouton est appuyé";
    // on vérifie que le champ "pseudo" n'est pas vide
    // empty vérifie à la fois si le champ est vide et si le champ existe belle et bien (is set)
    if(empty($_POST['email_user'])) {
        echo "Le champs email de l'utilisateur est vide.";
    }else if(empty($_POST['mdp_user'])){  // on vérifie maintenant si le champ "Mot de passe" n'est pas vide"
        echo "Le champ Mot de passe de l'Utilisateur est vide.";
    }else if(empty($_POST['nom_user'])){
        echo "Le champs nom de l'utilisateur est vide.";
    }else if(empty($_POST['prenom_user'])){
        echo "Le champs prenom de l'utilisateur est vide.";
    }else if(empty($_POST['re_mdp_user'])){
        echo "Le champs repetez le mot de passe de l'utilisateur est vide.";
    }else if(empty($_POST['email_contact'])){
        echo "Le champs email du contact est vide.";
    } else if(empty($_POST['mdp_contact'])) {
        echo "Le champ Mot de passe du contact est vide.";
    }else if(empty($_POST['nom_contact'])){
        echo "Le champs nom du contact est vide.";
    }else if(empty($_POST['prenom_contact'])){
        echo "Le champs prenom du contact est vide.";
    }else if(empty($_POST['re_mdp_contact'])){
        echo "Le champs repetez le mot de passe du contact est vide.";
    }else if(empty($_POST['id_chambre'])){
        echo "Le champs id_chambre est vide.";
    } else if(($_POST['re_mdp_user']) === ($_POST['mdp_user']) && ($_POST['re_mdp_contact']) === ($_POST['mdp_contact'])){
        echo "information plausible";

            $email_user = htmlentities($_POST['email_user'], ENT_QUOTES, "utf-8");
            $mdp_user = htmlentities($_POST['mdp_user'], ENT_QUOTES, "utf-8");
            $nom_user = htmlentities($_POST['nom_user'], ENT_QUOTES, "utf-8");
            $email_contact = htmlentities($_POST['email_contact'], ENT_QUOTES, "utf-8");
            $mdp_contact = htmlentities($_POST['mdp_contact'], ENT_QUOTES, "utf-8");
            $nom_contact = htmlentities($_POST['nom_contact'], ENT_QUOTES, "utf-8");
            $id_chambre = htmlentities($_POST['id_chambre'], ENT_QUOTES, "utf-8");
            //on se connecte à la base de données:
            $db = dbConnect();

        		if ($db != false) {
                // on fait maintenant la requête dans la base de données pour rechercher si ces données existe et correspondent:
                $request2 = $db->prepare("INSERT INTO contact (login_email, password, full_name) VALUES (:email_contact, :mdp_contact, :nom_contact)");
                $request2->bindParam(':email_contact', $email_contact,PDO::PARAM_INT);
                $request2->bindParam(':mdp_contact', $mdp_contact,PDO::PARAM_INT);
                $request2->bindParam(':nom_contact', $nom_contact,PDO::PARAM_INT);
                $request2->execute();

                $request = $db->prepare("INSERT INTO Utilisateur (login_email_user, password, full_name, id_chambre) VALUES (:email_user, :mdp_user, :nom_user, :id_chambre)");
                $request->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                $request->bindParam(':mdp_user', $mdp_user,PDO::PARAM_INT);
                $request->bindParam(':nom_user', $nom_user,PDO::PARAM_INT);
                $request->bindParam(':id_chambre', $id_chambre,PDO::PARAM_INT);
                $request->execute();

                echo "votre Compte est maintenant créé !";
                header('Location: ../identification/identification.php');
            }
      }
    }
?>

</body>
</html>
