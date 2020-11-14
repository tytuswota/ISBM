<?php

require_once("DB.php");
$pdo = new DB();

$pdo->db->query("SELECT * FROM gps order by date_time desc limit 20");
$cords = [];

foreach($pdo->db->query("SELECT * FROM gps order by date_time desc limit 20", PDO::FETCH_ASSOC) as $row)
{
    $cords[] = [
        "id" => $row['id'],
        "lat" => $row['longitude'],
        "lon" => $row['latitude'],
        "data" => $row['date_time'],
    ];
}

header('Content-Type: application/json');
echo json_encode([
    'cords' => $cords
]);