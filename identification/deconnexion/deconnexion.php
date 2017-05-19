<?php
  session_start();
  setcookie('current-id','');
  session_destroy();
  header('Location: ../identification.php');
?>
