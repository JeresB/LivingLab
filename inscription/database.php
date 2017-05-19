<?php
require_once('constants.php');

function dbConnect()
{
  try{
  	$pdo = new PDO('mysql:host='.DB_SERVEUR.';dbname='.DB_NAME.';charset=utf8', DB_USER, DB_PASSWORD);
  }catch (PDOException $e){
  	echo "pb ".$e->getMessage()."\n";
  }
  return $pdo;
}

?>
