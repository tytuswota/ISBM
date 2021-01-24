<?php
//meant to simulate the iriduim gate way
require_once('db.php');

ini_set('display_erros',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);

if($_SERVER["REQUEST_METHOD"] == "POST"){
    $raw_post = file_get_contents('php://input');

    preform_action(decode_message($raw_post), $raw_post);
}

function decode_message($raw_post){
    $json_object = json_decode($raw_post);
    $incoming_hex_message = $json_object->data;
    $ascii_string = '';

    for($i = 0; $i <= strlen($incoming_hex_message); $i+=2){
        $ascii_string .= chr(hexdec(substr($incoming_hex_message, $i,2)));
    }

    return explode(';', $ascii_string);
}

function store_gps_data($data){
    $db = new DB();
    $longitude = $data[1];
    $latitude = $data[2];
    $date_time = $data[3];

    $stmt = $db->db->prepare("INSERT INTO gps(longitude, latitude, date_time) VALUES (:longitude,:latitude, :date_time)");

    $stmt->bindParam(':longitude',$longitude);
    $stmt->bindParam(':latitude',$latitude);
    $stmt->bindParam(':date_time', $date_time);
    if($stmt->execute()){
        echo "oke";
    }else{
        print_r($stmt->errorInfo());
        echo "failed";
    }
}

function store_sensor_data($data){
    //to do
}

function store_boat_speed_course($data){
    //to do
}

function store_battery_status($data){
    //to do
}

function get_ais_data($data){
    //to do
}

function log_default($data){
    $db = new DB();
    $stmt = $db->db->prepare("INSERT INTO log(data) VALUES(:a)");
    $stmt->bindParam(':a', $data);
    $stmt->execute();
}

function log_data($data){

}

function preform_action($data, $raw_post){
    //=========protocol actions
    //store gps data 1
    //store sensor status 2
    //store boat speed and course 3
    //store battery status 4
    $action = $data[0];

    switch($action){
        case 1:
            return store_gps_data($data);
        case 2:
            return store_sensor_data($data);
        case 3:
            return store_boat_speed_course($data);
        case 4:
            return store_battery_status($data);
        case 5:
            return get_ais_data($data);
        default:
            return log_default($raw_post);
    }

}