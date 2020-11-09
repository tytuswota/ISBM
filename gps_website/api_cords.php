<?php

include_once 'includes/dbh.php';

$sql = "SELECT * FROM gps order by date_time desc limit 20";
$result = mysqli_query($conn, $sql);
$resultCheck = mysqli_num_rows($result);

$cords = [];

if ($resultCheck > 0) {
    while ($row = mysqli_fetch_assoc($result)) {
        $cords[] = [
            "id" => $row['id'],
            "lat" => $row['longitude'],
            "lon" => $row['latitude'],
            "data" => $row['date_time'],
        ];

    }
}

header('Content-Type: application/json');
echo json_encode([
    'cords' => $cords
]);