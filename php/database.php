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

function dbRequestCapteur($db, $id = -1)
{
  try {
    $request = 'SELECT co2, chute, temperature, humidite, four, capteur.id_chambre FROM capteur, chambre, utilisateur';
    $request .= ' WHERE capteur.id_chambre = chambre.id_chambre AND chambre.id_chambre = utilisateur.id_chambre';

    $statement = $db->prepare($request);
    $statement->execute();
    
    $result = $statement->fetchAll(PDO::FETCH_ASSOC);
  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return $result;
}


?>
