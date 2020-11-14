<?php
    require_once("includes/DB.php");
    $pdo = new DB();
?>

<!DOCTYPE html>
<html>
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.7.1/dist/leaflet.css" />
    <script src="https://unpkg.com/leaflet@1.7.1/dist/leaflet.js"></script>
<head>
<style>

body {
   background-color: #65C9FF;
   font-family: Arial, Helvetica, sans-serif;
   width: 100%;
   height: 100%;
}

.header {
  padding: 30px;
  text-align: center;
  background: #A1DEFF;
}

.header h1 {
  font-size: 50px;
}

table {
    font-family: arial, sans-serif;
    border-collapse: collapse;
    width: 38.7%;
}

td, th {
    border: 1px solid #000000;
    text-align: center;
    padding: 8px;
}

tr:nth-child(even) {
    background-color: #CCFFB9;
} 

#mapid { height: 460px; width: 740px; border: 1px solid #000000;}
</style>
</head>
<body>

<center>
<div class="header">
    <h1> Zeilboot status </h1>
</div>
<br>
<div id="mapid"> </div>
<br>
<table>
    <tr>
        <th>Id</th>
        <th>Longitude</th>
        <th>Latitude</th> 
        <th>Date</th>
    </tr>

<?php
    $stmt =
    $resultCheck = mysqli_num_rows($result);
    $cords = [];

    foreach($pdo->db->query("SELECT * FROM gps order by date_time desc limit 20", PDO::FETCH_ASSOC) as $row)
    {
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

var myIcon = L.icon({
    iconUrl: 'zeilboot.png',
    iconSize: [50, 46],
    iconAnchor: [25, 23],
});

var marker = L.marker([ cords[0].lat, cords[0].lon ], {icon: myIcon}).addTo(map);

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