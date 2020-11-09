<?php
    include_once 'includes/dbh.php';
?>
<!DOCTYPE html>
<html>
<link rel="stylesheet" href="https://unpkg.com/leaflet@1.7.1/dist/leaflet.css" />
<script src="https://unpkg.com/leaflet@1.7.1/dist/leaflet.js"></script>
<head>
<style>

body {
   /*background-image: url("zeilboot.jpg");*/
   background-color: #A9E0FF;
   width: 100%;
   height: 100%;
}

table {
    font-family: arial, sans-serif;
    border-collapse: collapse;
    width: 40%;
}

td, th {
    border: 2px solid #000000;
    text-align: center;
    padding: 8px;
}

tr:nth-child(even) {
    background-color: #CCFFB9;
}

#mapid { height: 500px; width: 700px; border: 3px solid #000000;}

</style>
</head>
<body>

<center>
<h1> GPS locatie </h1>

<div id="mapid"></div><br>

<table>
    <tr>
        <th>Id</th>
        <th>Longitude</th>
        <th>Latitude</th> 
        <th>Date</th>
    </tr>

<?php
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

            echo '<tr>';
            echo '<td>' . $row['id'] . '</td>';
            echo '<td>' . $row['longitude'] . '</td>';
            echo '<td>' . $row['latitude'] . '</td>';
            echo '<td>' . $row['date_time'] . '</td>';
            echo '</tr>';
        }
    }
?>

</table>
</center>
</body>
</html>

<script>
var cords = JSON.parse('<?php echo json_encode($cords) ?>');
</script>
<script>
var map = L.map('mapid');

L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="http://openstreetmap.org/copyright" target="_blank">OpenStreetMap</a> contributors'
}).addTo(map);

var popup = L.popup();

function onMapClick(e) {
    popup.setLatLng(e.latlng)
        .setContent("You clicked the map at " + e.latlng.toString())
        .openOn(map);
}

map.on('click', onMapClick);

var lineCords = [];
for (var i = 0; i < cords.length; i++) {
    lineCords.push([ cords[i].lat, cords[i].lon ]);
}

var line = L.polyline(lineCords, {color:'red'}).addTo(map);
map.fitBounds(line.getBounds());

var marker = L.marker([ cords[0].lat, cords[0].lon ]).addTo(map);

function updateCordes() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
        var data = JSON.parse(xhr.responseText);
        // console.log(data);
        var cords = data.cords;

        var lineCords = [];
        for (var i = 0; i < cords.length; i++) {
            lineCords.push([ cords[i].lat, cords[i].lon ]);
        }

        line.setLatLngs(lineCords);

        marker.setLatLng([ cords[0].lat, cords[0].lon ]);
    };
    xhr.open('get', 'api_cords.php', true);
    xhr.send();
}
setInterval(updateCordes, 1000);

</script>