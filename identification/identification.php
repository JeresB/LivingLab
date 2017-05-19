<?php
  session_start();

  require_once('database.php');
 ?>
 <!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title>Un formulaire de connexion en AJAX</title>
</head>

<body>

    <h1>Un formulaire de connexion en AJAX</h1>
    <div class="row" id="errors"></div>
    <div class="row" id="success"></div>


<?php

echo '<form action="" method="post">
Nom utilisateur : <input type="text" name="pseudo" />
</br>
Mot de passe : <input type="password" name="mot_de_passe" />
<input type="submit" name="submit" value="Se connecter !" />';

if(isset($_POST['submit'])) { // si le bouton "Connexion" est appuyé
    // on vérifie que le champ "pseudo" n'est pas vide
    // empty vérifie à la fois si le champ est vide et si le champ existe belle et bien (is set)
    if(empty($_POST['pseudo'])) {
        echo "Le champ Pseudo est vide.";
    } else {
        // on vérifie maintenant si le champ "Mot de passe" n'est pas vide"
        if(empty($_POST['mot_de_passe'])) {
            echo "Le champ Mot de passe est vide.";
        } else {
            // les champs sont bien posté et pas vide, on sécurise les données entrées par le membre:
            $Pseudo = htmlentities($_POST['pseudo'], ENT_QUOTES, "utf-8"); // le htmlentities() passera les guillemets en entités HTML, ce qui empêchera les injections SQL
            $MotDePasse = htmlentities($_POST['mot_de_passe'], ENT_QUOTES, "utf-8");
            //on se connecte à la base de données:
            $db = dbConnect();

        		if ($db != false) {
                // on fait maintenant la requête dans la base de données pour rechercher si ces données existe et correspondent:
                $request = $db->prepare('SELECT * FROM Utilisateur, contact WHERE login_email_user = "'.$Pseudo.'" AND Utilisateur.password = "'.$MotDePasse.'" OR login_email = "'.$Pseudo.'" AND contact.password = "'.$MotDePasse.'"');
                $request->execute();

                // on compte les ligne reçu pour verifier si l'authentification est correct
                if($request->rowCount() == 0) {
                    echo "Le pseudo ou le mot de passe est incorrect, le compte n'a pas été trouvé.";
                } else {
                    echo "Vous êtes à présent connecté !";
                    // on ouvre la session avec $_SESSION:
                    $_SESSION['pseudo'] = $Pseudo; // la session peut être appelée différemment et son contenu aussi peut être autre chose que le pseudo
                    echo $_SESSION['pseudo'];
                    header('Location: dashboard/index.html');
                }
            }
        }
    }
}
?>

</body>
</html>
