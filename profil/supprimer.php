<?php
/**
 * \file profil/supprimer.php
 * \brief Permet la suppression d'un contact
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
    * on appelle notre page php necessaire afin de ce connecter à la base de données
  */
  
  require_once('../php/database.php');
  
  //!on se connecte à la base de données:
  $db = dbConnect();
  
  //!on recupere l'attribut transferer en POST lors l'appel de la page
  $email_contact = $_POST['contact'];
  
  if ($db != false) {
    
    /**
     * La requête sql suivante aura pour but de supprimer de la bases de données
     * le contact choisi dans les 2 tables où il est representé
    */
    
    $request = $db->prepare("DELETE FROM utilisateur_contact WHERE login_email = :email_contact");
    $request->bindParam(':email_contact', $email_contact,PDO::PARAM_STR);
    $request->execute();
    
    $request1 = $db->prepare("DELETE FROM contact WHERE login_email = :email");
    $request1->bindParam(':email', $email_contact,PDO::PARAM_STR);
    $request1->execute();
    
    /**
     * Une fois ces requêtes effectuées l'utilisateur sera redirigé vers la page profil
    */
    header('Location: ../profil');
  }
?>