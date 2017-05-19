<?php
	session_start();
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
			if($request_explode[0] == 'Capteur') {
				$data = NULL;

				$id = $request_explode[1];

				if ($id != NULL && $id != "" && $requestType == 'GET') {
					$id = intval($id);
					$data = dbRequestCapteur($db, $id);

				} else if ($requestType == 'GET') {
					$data = dbRequestCapteur($db);
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
