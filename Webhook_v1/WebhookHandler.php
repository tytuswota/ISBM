<?php
header('Content-Type: application/json;charset=utf-8;');
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(-1);
//this is the webhook handler as

//here the auto load functions are called

$folderNames[] = 'Controllers';
$folderNames[] = 'Models';
$folderNames[] = 'Includes';
$GLOBALS['PROTOCOL_NUMBERS'] = [1,2,3,4,5,6,7];

set_include_path(implode(PATH_SEPARATOR, $folderNames));
spl_autoload_register(function($class)
{
    $paths = explode(PATH_SEPARATOR, get_include_path());
    foreach($paths as $path){
        $file = $path . '/' . $class . '.php';
        if(is_file($file)){
            include($file);
            return;
        }
    }
});

if($_SERVER["REQUEST_METHOD"] == "POST") {
    $json  = file_get_contents('php://input');
    $proto = MOMessageController::createMessage(json_decode($json));
    
    switch($proto){
    case 1:
	LocalizationController::createLocalization();    
	break;
      case 2:
	break;
      case 3:
	break;
      case 4:
	break;      
      case 5:
	break;
      case 6:
        break;
      case 7:
        break;
      default:
	break;	
    }
}






