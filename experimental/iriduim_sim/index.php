<?php
//meant to simulate the iridium gateway
ini_set('display_erros',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);

$server_url = "http://95.217.181.53/";

if($_SERVER["REQUEST_METHOD"] == "GET"){
    http_post($_GET["incoming_message"]);
}

function http_post($incoming_message){
    try{
        $data = make_json_object($incoming_message);

        $url = "http://95.217.181.53/";
        $ch = curl_init( $url );
        # Setup request to send json via POST.
        curl_setopt( $ch, CURLOPT_POSTFIELDS, $data );
        curl_setopt( $ch, CURLOPT_HTTPHEADER, array('Content-Type:application/json'));
        # Return response instead of printing.
        curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
        # Send request.
        $result = curl_exec($ch);
        curl_close($ch);
        print_r($result);
    }catch(Exception $e){
        echo "could't send message";
    }
}

/*function decode_message($incoming_hex_message){
    $ascii_string = '';
    for($i = 0; $i < strlen($incoming_hex_message); $i+=2){
        $ascii_string .= chr(hexdec(substr($incoming_hex_message,$i,2)));
    }
}*/

function make_json_object($incoming_data){
    $imei = "30043406443470";
    $momsn = "14";
    $transmition_time = "";

    $hex_array =
        ['0','1',
        '2','3',
        '4','5',
        '6','7',
        '8','9',
        'A','B',
        'C','D',
        'E','F'];

    $bin_data = explode(' ', $incoming_data);

    $hex = "";
    for($i = 0; $i < sizeof($bin_data); $i++){
        $x = str_split($bin_data[$i], 2);
        array_unshift($x, "00");
        $first_byte = $x[0] . $x[1];
        $second_byte = $x[2] . $x[3];

        $hex .= $hex_array[bindec($first_byte)];
        $hex .= $hex_array[bindec($second_byte)];
    }

    $arr = array('emei'=> $imei,
        'momsn' => $momsn,
        'transmition_time' => $transmition_time,
        'data' => $hex);

    $encoded_data = json_encode($arr);
    print_r($encoded_data);
    return $encoded_data;
}
