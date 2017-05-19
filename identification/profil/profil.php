<?php
  session_start();
  require_once('../database.php');
 ?>
 <!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title>Profil</title>
</head>

<body>
  <header>
    <ul>
      <li><a href="../dashboard/index.html">Accueil</a></li>
      <li><a href="#">Alerte</a></li>
      <li><a href="../deconnexion/deconnexion.php">Deconnexion</a></li>
    </ul>
  </header>
  <main>

    <h1>Modifier mot de passe</h1>
    <div class="row" id="errors"></div>
    <div class="row" id="success"></div>


<?php

echo '<form action="" method="post">
Ancien mot de passe : <input type="password" name="ancien_mdp" />
</br>
Nouveau mot de passe : <input type="password" name="nouveau_mdp" />
</br>
Repetez Mot de passe : <input type="password" name="re_mdp" />
</br>
<input type="submit" name="submit" value="submit" />
</form>';

if(isset($_POST['submit'])) { // si le bouton "Connexion" est appuyé
    // on vérifie que les champs ne sont pas vide
    // empty vérifie à la fois si le champ est vide et si le champ existe belle et bien (is set)
    if(empty($_POST['ancien_mdp'])) {
        echo "Le champs correspondant à l'ancien mot de passe est vide.";
    }else if(empty($_POST['nouveau_mdp'])){  // on vérifie maintenant si le champ "Mot de passe" n'est pas vide"
        echo "Le champ correspondant au nouveau mot de passe est vide.";
    }else if(empty($_POST['re_mdp'])){
        echo "Le champs repetez le nouveau mot de passe de l'utilisateur est vide.";
    } else if(($_POST['re_mdp']) === ($_POST['nouveau_mdp'])){

            $ancien_mdp = htmlentities($_POST['ancien_mdp'], ENT_QUOTES, "utf-8");
            $nouveau_mdp = htmlentities($_POST['nouveau_mdp'], ENT_QUOTES, "utf-8");
            $re_mdp = htmlentities($_POST['re_mdp'], ENT_QUOTES, "utf-8");
            $email_user = $_SESSION['pseudo'];
            echo $email_user;
            //on se connecte à la base de données:
            $db = dbConnect();

        		if ($db != false) {
                // on fait maintenant la requête dans la base de données pour rechercher si ces données existe et correspondent:
                $request2 = $db->prepare("UPDATE contact SET password = :nouveau_mdp WHERE login_email = :email_user");
                $request2->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                $request2->bindParam(':nouveau_mdp', $nouveau_mdp,PDO::PARAM_INT);
                $request2->execute();

                $request = $db->prepare("UPDATE Utilisateur SET password = :nouveau_mdp WHERE login_email_user = :email_user");
                $request->bindParam(':email_user', $email_user,PDO::PARAM_INT);
                $request->bindParam(':nouveau_mdp', $nouveau_mdp,PDO::PARAM_INT);
                $request->execute();

                header('Location: ../dashboard/index.html');
            }
      }
    }
?>
</main>
</body>
</html>
