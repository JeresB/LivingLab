<?php
	/**
	* \file dashboard/php/request.php
	* \brief Permet de crée un lien entre les requêtes Ajax et la BDD
	* \author {Théo D. & Jeremy B.}
	* \version 1
	*/

	/// Démarrage de la session
	session_start();
	header("Content-Type: text/plain");

	/// Inclusion de la page database.php
	require_once('../../php/database.php');

	/// On récupère le lien de la requête
	$request = substr($_SERVER['PATH_INFO'], 1);

	/// Si la requête est un module
	if (is_dir('../'.$request)) {
		/// On extrait le nom du module
		$moduleName = substr($request, strrpos($request, '/') + 1);

		/// On charge la page html et la page js du module demandé
		sendHtmlAndJsData($moduleName, $request, $moduleName);

	/// Si la requête n'est pas un module alors on veut accéder à la BDD
	} else {
		/// Connexion à la BDD
		$db = dbConnect();

		/// Connexion réussie
		if ($db != false) {

			/// On découpe la requête pour chaque /
			$request_explode = explode('/', $request);

			/// On récupère le type de la requête
			$requestType = $_SERVER['REQUEST_METHOD'];

			/// Si la requête commence par Capteur
			if($request_explode[0] == 'Capteur') {
				$data = NULL;

				/// Pour une requête de capteurs globaux
				if ($requestType == 'GET') {
					$data = dbRequestCapteur($db);
				}

				if ($data != NULL)
					sendJsonData($data);
					/// Si la requête commence par Telephone
			} else if($request_explode[0] == 'Telephone') {
				$data = NULL;

				if ($requestType == 'GET') {
					/// Requête vers la BDD
					$data = dbRequestPas($db);
				}

				/// Envoi des données à encoder en JSon
				if ($data != NULL)
					sendJsonData($data);
			/// Si la requête commence par OneSensor
			} else if($request_explode[0] == 'OneSensor') {
				$data = NULL;

				/// Si la requête contient une donnée
				$id = $request_explode[1];

				/// Pour une requête de données dans l'intention de crée un graphique
				if ($id != NULL && $id != "" && $requestType == 'GET') {
					$id = intval($id);
					/// Requête vers la BDD
					$data = dbRequestOneSensor($db, $id);
				}

				/// Envoi des données à encoder en JSon
				if ($data != NULL)
					sendJsonData($data);

			/// Si la requête commence par historique
			} else if($request_explode[0] == 'historique') {
				$data = NULL;

				/// Donnée 1 : identifiant du capteur
				$type = $request_explode[1];
				/// Donnée 2 : date où commence l'historique
				$debut = $request_explode[2];
				/// Donnée 3 : date où fini l'historique
				$fin = $request_explode[3];

				if ($requestType == 'GET') {
					$type = intval($type);
					/// Requête vers la BDD
					$data = dbRequestHistorique($db, $type, $debut, $fin);
				}

				/// Envoi des données à encoder en JSon
				if ($data != NULL)
					sendJsonData($data);

			/// Si la requête n'est pas correct
			} else {
				header('HTTP/1.1 503 Service Unavailable');
				exit;
			}

		/// Si la connexion à la BDD à échouée
		} else {
			header('HTTP/1.1 400 Bad request');
			exit;
		}
	}

	/**
     *  \brief sendHtmlAndJsData
     *
     *  Permet de charger les page html et js d'un module demandé
     *
     *  \param $divId : nom de la div où on charge le module
     *  \param $modulePath : chemin pour accéder au fichier html et js du module
 	 *  \param $moduleName : nom du module
     */
	function sendHtmlAndJsData($divId, $modulePath, $moduleName) {
	  $data = array ('html' => $modulePath.'/'.$moduleName.'.html',
			'divId' => $divId, 'js' => $modulePath.'/'.$moduleName.'.js');
		sendJsonData($data);
	}

	/**
     *  \brief sendJsonData
     *
     *  Envoie des données vers le client sous format JSon
     *
     *  \param $data : données récupérées dans la BDD
     *  \param $code : par défaut 200 (réponse OK)
     * 
     *  \return données encodées en Json
     */
	function sendJsonData($data, $code = 200) {
	  header('Content-Type: text/plain; charset=utf-8');
	  header('Cache-control: no-store, no-cache, must-revalidate');
	  header('Pragma: no-cache');
		header('HTTP/1.1 200 OK');
	  echo json_encode($data);
		exit;
	}
?>
