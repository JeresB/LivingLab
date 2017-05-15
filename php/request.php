<?php
	header("Content-Type: text/plain");

	require_once('database.php');
	// We check the request type.
	$request = substr($_SERVER['PATH_INFO'], 1);
	//echo '$_SERVER["PATH_INFO"] : '.$_SERVER['PATH_INFO'];
	//echo '$request : '.$request;
	// We check if the request is a module.
	if (is_dir('../'.$request)) {
		// We extract the module name.
		$moduleName = substr($request, strrpos($request, '/') + 1);

		sendHtmlAndJsData($moduleName, $request, $moduleName);

	} else {
		$db = dbConnect();

		if ($db != false) {
			$request_explode = explode('/', $request);
			$requestType = $_SERVER['REQUEST_METHOD'];
			if($request_explode[0] == 'galerie') {
				$data = NULL;

				$id = $request_explode[1];

				if ($id != NULL && $id != "" && $requestType == 'GET') {
					$id = intval($id);
					$data = dbRequestGalerie($db, $id);

				} else if ($requestType == 'GET') {
					$data = dbRequestGalerie($db);
				}
				// } else if ($id != NULL && $id != "" && $requestType == 'PUT') {
				// 	parse_str(file_get_contents('php://input'), $_PUT);
				// 	error_log($_PUT['choice']);
				// 	$data = dbReplyPoll($db, intval($id), $_PUT['choice']);
				//
				// } else if ($id != NULL && $id != "" && $requestType == 'POST') {
				// 	$data = dbAddPoll($db, $_POST['login'], $_POST['title'],
				// 	$_POST['option1'], $_POST['option2'], $_POST['option3']);
				//
				// }
				if ($data != NULL)
					sendJsonData($data);
			} else if ($request_explode[0] == 'commentaire') {
				$data = NULL;

				$id = $request_explode[1];

				if ($id != NULL && $id != "" && $requestType == 'GET') {
					$id = intval($id);
					$data = dbRequestCommentaire($db, $id);
				}

				$commentaire = htmlspecialchars($_POST["commentaire"]);
				$id_image = htmlspecialchars($_POST["id_image"]);

				if ($_POST["commentaire"] != NULL && $_POST["commentaire"] != "" && $_POST["id_image"] != NULL && $_POST["id_image"] != "" && $requestType == 'POST') {
					$data = dbAddCommentaire($db, $commentaire, $id_image);
				}

				if ($data != NULL)
					sendJsonData($data);
			} else {
				header('HTTP/1.1 503 Service Unavailable');
				exit;
			}
		} else {
			header('HTTP/1.1 400 Bad request');
			exit;
		}
	}

	//----------------------------------------------------------------------------
	//--- sendHtmlAndJsData ------------------------------------------------------
	//----------------------------------------------------------------------------
	function sendHtmlAndJsData($divId, $modulePath, $moduleName)
	{
	  // We create the data (Html and Js).
	  $data = array ('html' => $modulePath.'/'.$moduleName.'.html',
			'divId' => $divId, 'js' => $modulePath.'/'.$moduleName.'.js');
		sendJsonData($data);
	}

	//----------------------------------------------------------------------------
	//--- sendJsonData -----------------------------------------------------------
	//----------------------------------------------------------------------------
	function sendJsonData($data, $code = 200)
	{
	  // We send the data to the client.
	  header('Content-Type: text/plain; charset=utf-8');
	  header('Cache-control: no-store, no-cache, must-revalidate');
	  header('Pragma: no-cache');
		header('HTTP/1.1 200 OK');
	  echo json_encode($data);
		exit;
	}
?>
