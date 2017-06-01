<?php
/**
 * \file database.php
 * \brief Permet de faire des requêtes SQL vers la BDD
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */
 
/// Inclusion des constantes de connexion à la BDD
require_once('constants.php');

/**
 *  \brief dbConnect
 *
 *  Connexion à la BDD de type Mysql
 * 
 *  \return l'objet PDO
 */
function dbConnect() {
  try{
  	$pdo = new PDO('mysql:host='.DB_SERVEUR.';dbname='.DB_NAME.';charset=utf8', DB_USER, DB_PASSWORD);
  }catch (PDOException $e){
  	echo "pb ".$e->getMessage()."\n";
  }
  return $pdo;
}

/**
 *  \brief dbRequestPas
 *
 *  Requête pour avoir les données des pas en temps réel
 * 
 *  \param $db : objet PDO
 * 
 *  \return résultat de la requête
 */
function dbRequestPas($db) {
  try {
    
    $telephone = $_SESSION['telephone'];
    
    $request = "SELECT temps, pas FROM capteurUser WHERE id_telephone = :id";
    $request .= " ORDER BY temps DESC LIMIT 0, 2";

    $statement = $db->prepare($request);
    $statement->bindParam(':id', $telephone, PDO::PARAM_INT);
    $statement->execute();

    $result = $statement->fetchAll(PDO::FETCH_ASSOC);
  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return $result;
}

/**
 *  \brief dbRequestCapteur
 *
 *  Requête pour avoir les données des capteurs en temps réel
 * 
 *  \param $db : objet PDO
 * 
 *  \return résultat de la requête
 */
function dbRequestCapteur($db) {
  try {
    
    $chambre = $_SESSION['chambre'];
    
    $request = "SELECT date_heure, co2, chute, temperature, humidite, four, presence, capteur.id_chambre FROM capteur, chambre";
    $request .= " WHERE capteur.id_chambre = chambre.id_chambre AND chambre.id_chambre = :chambre";
    $request .= " ORDER BY date_heure DESC LIMIT 0, 2";

    $statement = $db->prepare($request);
    $statement->bindParam(':chambre', $chambre, PDO::PARAM_INT);
    $statement->execute();

    $result = $statement->fetchAll(PDO::FETCH_ASSOC);
  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return $result;
}

/**
 *  \brief dbRequestOneSensor
 *
 *  Requête pour avoir les données d'un capteur en temps réel
 * 
 *  \param $db : objet PDO
 * 
 *  \return résultat de la requête
 */
function dbRequestOneSensor($db, $id = -1) {
  try {
    
    $chambre = $_SESSION['chambre'];
    $request = "SELECT capteur.date_heure, ";
    if ($id == 1) {
      $request .= "capteur.co2, seuil.co2moyen, seuil.co2haut";
    } else if ($id == 2) {
      $request .= "capteur.humidite, seuil.humiditymin, seuil.humiditymax";
    } else if ($id == 3) {
      $request .= "capteur.temperature, seuil.temperaturemin, seuil.temperaturemax";
    }

    $request .= " FROM capteur, chambre, seuil";
    $request .= " WHERE capteur.id_chambre = chambre.id_chambre AND seuil.id_chambre = chambre.id_chambre AND chambre.id_chambre = :chambre";
    $request .= " ORDER BY date_heure DESC LIMIT 0, 30";

    $statement = $db->prepare($request);
    $statement->bindParam(':chambre', $chambre, PDO::PARAM_INT);
    $statement->execute();

    $result = $statement->fetchAll(PDO::FETCH_ASSOC);
  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return $result;
}

/**
 *  \brief dbRequestHistorique
 *
 *  Requête pour avoir les données d'un capteur avec un historique
 * 
 *  \param $db : objet PDO
 * 
 *  \return résultat de la requête
 */
function dbRequestHistorique($db, $type, $debut, $fin) {
  try {
    
    $chambre = $_SESSION['chambre'];
    
    $debut = str_replace('%', ' ', $debut);
    $fin = str_replace('%', ' ', $fin);
    
    $debut = str_replace('x', '/', $debut);
    $fin = str_replace('x', '/', $fin);
    
    $request = "SELECT date_heure, ";
    if ($type == 1) {
      $request .= "capteur.co2, seuil.co2moyen, seuil.co2haut";
    } else if ($type == 2) {
      $request .= "capteur.humidite, seuil.humiditymin, seuil.humiditymax";
    } else if ($type == 3) {
      $request .= "capteur.temperature, seuil.temperaturemin, seuil.temperaturemax";
    }

    $request .= " FROM capteur, chambre, seuil";
    $request .= " WHERE capteur.id_chambre = chambre.id_chambre AND seuil.id_chambre = chambre.id_chambre AND chambre.id_chambre = :chambre";
    $request .= " AND date_heure > :debut AND date_heure < :fin";
    $request .= " ORDER BY date_heure DESC";

    $statement = $db->prepare($request);
    $statement->bindParam(':chambre', $chambre, PDO::PARAM_STR);
    $statement->bindParam(':debut', $debut, PDO::PARAM_STR);
    $statement->bindParam(':fin', $fin, PDO::PARAM_STR);
    $statement->execute();

    $result = $statement->fetchAll(PDO::FETCH_ASSOC);
  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return $result;
}

/**
 *  \brief dbRequestNotif
 *
 *  Requête pour avoir les messages d'alertes liés aux capteurs
 * 
 *  \param $db : objet PDO
 * 
 *  \return résultat de la requête
 */
function dbRequestNotif($db) {
  try {
    
    $chambre = $_SESSION['chambre'];
    
    $request = "SELECT date_heure, detection_alerte, capteur.id_chambre FROM capteur, chambre";
    $request .= " WHERE capteur.id_chambre = chambre.id_chambre AND chambre.id_chambre = :chambre";
    $request .= " ORDER BY date_heure DESC";

    $statement = $db->prepare($request);
    $statement->bindParam(':chambre', $chambre, PDO::PARAM_INT);
    $statement->execute();

    $result = $statement->fetchAll(PDO::FETCH_ASSOC);
  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return $result;
}  

/**
 *  \brief dbNotifSeen
 *
 *  Requête pour ajouter une distinction aux messages d'alerte (savoir si les notifications des alertes ont déjà été vues)
 * 
 *  \param $db : objet PDO
 *  \param $id : clé primaire de l'alerte
 *  \param $text : message de l'alerte
 * 
 *  \return résultat de la requête
 */
function dbNotifSeen($db, $id, $text) {
  try {
    
    $chambre = $_SESSION['chambre'];
    $id = str_replace('%', ' ', $id);
    
    $request = "UPDATE capteur";
    $request .= " SET detection_alerte = :text";
    $request .= " WHERE date_heure = :id";
    $request .= " AND id_chambre = :chambre";

    $statement = $db->prepare($request);
    $statement->bindParam(':text', $text, PDO::PARAM_INT);
    $statement->bindParam(':id', $id, PDO::PARAM_INT);
    $statement->bindParam(':chambre', $chambre, PDO::PARAM_INT);
    $statement->execute();

  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return true;
} 

/**
 *  \brief dbRequestNotifUser
 *
 *  Requête pour avoir les messages d'alertes liés aux téléphones
 * 
 *  \param $db : objet PDO
 * 
 *  \return résultat de la requête
 */
function dbRequestNotifUser($db) {
  try {
    
    $telephone = $_SESSION['telephone'];
    
    $request = "SELECT temps, detection_alerte_user, capteurUser.id_telephone FROM capteurUser, telephone";
    $request .= " WHERE capteurUser.id_telephone = telephone.id_telephone AND telephone.id_telephone = :telephone";
    $request .= " ORDER BY temps DESC";

    $statement = $db->prepare($request);
    $statement->bindParam(':telephone', $telephone, PDO::PARAM_INT);
    $statement->execute();

    $result = $statement->fetchAll(PDO::FETCH_ASSOC);
  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return $result;
}  

/**
 *  \brief dbNotifUserSeen
 *
 *  Requête pour ajouter une distinction aux messages d'alerte (savoir si les notifications des alertes ont déjà été vues)
 * 
 *  \param $db : objet PDO
 *  \param $id : clé primaire de l'alerte
 *  \param $text : message de l'alerte
 * 
 *  \return résultat de la requête
 */
function dbNotifUserSeen($db, $id, $text) {
  try {
    
    $telephone = $_SESSION['telephone'];
    $id = str_replace('%', ' ', $id);
    
    $request = "UPDATE capteurUser";
    $request .= " SET detection_alerte_user = :text";
    $request .= " WHERE temps = :id";
    $request .= " AND id_telephone = :telephone";

    $statement = $db->prepare($request);
    $statement->bindParam(':text', $text, PDO::PARAM_INT);
    $statement->bindParam(':id', $id, PDO::PARAM_INT);
    $statement->bindParam(':telephone', $telephone, PDO::PARAM_INT);
    $statement->execute();

  }catch (PDOException $exception) {
    error_log('Request error: '.$exception->getMessage());
    return false;
  }
  return true;
} 

?>