<?php
/**
 * \file deconnexion/index.php
 * \brief Permet la deconnexion
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */

  //! demarrage de la session
  session_start();
  
  //! on detruit le cookie utilisé dans la page dashboard
  setcookie('current-id','');
  
  //! Enfin on detruit toutes les sessions de l'utilisateur 
  session_destroy();
  
  //!puis on termine par rediriger l'utilisateur de l'application à la page identification
  header('Location: ../identification/');
?>
