<?php
/**
 * \file inscription/index.php
 * \brief Permet l'inscription d'un utilisateur et d'un contact dans la base de données
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */
 
/// Démarrage de la session
session_start();
  
$email_user = $_SESSION['pseudo'];
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="Application LivingLab">
    <meta name="author" content="Development by Theo Dupont & Jeremy Boiselet">
    <link rel="icon" type="image/png" href="image/icone.gif" />

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="css/font-awesome.min.css" rel="stylesheet" type="text/css">
    <link href="css/jquery-confirm.css" rel="stylesheet" type="text/css">

    <!-- Custom CSS -->
    <link href="css/index.css" rel="stylesheet" type="text/css">

  </head>

<body>

<!-- Si l'utilisateur est connecté la barre de menu change -->
<?php  if (empty($email_user)) {
    require_once('template/navbar-home.html');
  } else {
    require_once('template/navbar-connected.php');
  }
?>
    
<title>LivingLab</title>
    <div id = "panel_connexion" class = "container">
        <div class = "row">
            <div class = "col-md-4">
                <div class = "panel panel-default">
                    <div class = "panel-heading">
                        <h2>LivingLab 
                            <?php if (empty($email_user)) { echo '<button type="submit" class="btn btn-primary pull-right log-in">Log in</button>'; } ?>
                            <button type="submit" class="btn btn-primary pull-right sign-up">Sign up</button>
                        </h2>
                    </div>
                    <div class = "panel-body">
                        <p class = "text-justify">L'application LivingLab permet d'améliorer le confort au quotidien.
                        Grâce à des capteurs installés chez soi, LivingLab récupère les données
                        propres à votre habitat. Ces données vous sont ensuite accessibles à 
                        partir de notre plateforme. Ces données sont également traitées pour
                        assurer votre sécurité chaque jour.</p>
                        <img class = "img-responsive" src="image/logomaison.png">
                    </div>
                </div>
            </div>
            <div class = "col-md-8">
                <div class = "panel panel-default">
                    <div class = "panel-heading">
                        <h2>Les avis retour de nos utilisateurs :</h2>
                    </div>
                    <div class = "panel-body">
                        <div class ="row">
                            <div class = "col-md-6">
                                <img class = "img-responsive thumbnail pull-left" src="image/man.jpg">
                                <p><i class="fa fa-quote-left" aria-hidden="true"></i>
                                Après avoir testé LivingLab pendant un mois, je n'ai pas pus m'en séparer.
                                <i class="fa fa-quote-right" aria-hidden="true"></i></p>
                            </div>
                            <div class = "col-md-6">
                                <img class = "img-responsive thumbnail pull-left" src="image/woman.png">
                                <p><i class="fa fa-quote-left" aria-hidden="true"></i>
                                Cette application est juste géniale, je ne peux plus m'en passer.
                                Je la conseille à toutes les personnes intéressées.
                                <i class="fa fa-quote-right" aria-hidden="true"></i>
                                </p>
                            </div>
                            <div class = "col-md-6">
                                <img class = "img-responsive thumbnail pull-left" src="image/woman.png">
                                <p class = "text-justify"><i class="fa fa-quote-left" aria-hidden="true"></i>
                                Un ami m'a recommandé cette application que j'ai tout de suite appréciée.
                                Je vous la recommande.
                                <i class="fa fa-quote-right" aria-hidden="true"></i>
                                </p>
                            </div>
                            <div class = "col-md-6">
                                <img class = "img-responsive thumbnail pull-left" src="image/man.jpg">
                                <p><i class="fa fa-quote-left" aria-hidden="true"></i>
                                LivingLab est une application qui améliore grandement la sécurité des usagers.
                                C'est pourquoi je l'ai recommandé à mes parents qui m'en remercient.
                                <i class="fa fa-quote-right" aria-hidden="true"></i>
                                </p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <!-- jQuery -->
    <script src="js/jquery.min.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>
    
    <!-- Custom JS -->
    <script src="js/index.js"></script>
    
</body>

</html>
