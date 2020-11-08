<?php
    include_once 'includes/dbh.php';
?>

<html>
<link rel="stylesheet" href="https://unpkg.com/leaflet@1.7.1/dist/leaflet.css"
integrity="sha512-xodZBNTC5n17Xt2atTPuE1HxjVMSvLVW9ocqUKLsCC5CXdbqCmblAshOMAS6/keqq/sMZMZ19scR4PsZChSR7A=="
crossorigin=""/>

<script src="https://unpkg.com/leaflet@1.7.1/dist/leaflet.js"
integrity="sha512-XQoYMqMTK8LvdxXYG3nZ448hOEQiglfqkJs1NOQV44cWnUrBc8PkAOcXy20w0vlaXaVUearIOBhiXZ5V3ynxwA=="
crossorigin="">

</script>
<head>
<style>

body {
   background-image: url("zeilboot.jpg");
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

#mapid { height: 500px; width: 500px; border: 3px solid #000000;}

</style>
</head>
<body>

<center>
<h1> GPS data </h1>

<div id="mapid"></div><br>

<table>
    <tr>
        <th>Id</th>
        <th>Longitude</th>
        <th>Latitude</th> 
        <th>Date</th>
    </tr>

<?php
    $sql = "SELECT * FROM gps;";
    $result = mysqli_query($conn, $sql);
    $resultCheck = mysqli_num_rows($result);

    if ($resultCheck > 0) {
        while ($row = mysqli_fetch_assoc($result)) {

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
var mymap = L.map('mapid').setView([51.935740, 4.515179], 15);

L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="http://openstreetmap.org/copyright" target="_blank">OpenStreetMap</a> contributors'
}).addTo(mymap);

var popup = L.popup();

function onMapClick(e) {
    popup
        .setLatLng(e.latlng)
        .setContent("You clicked the map at " + e.latlng.toString())
        .openOn(mymap);
}

mymap.on('click', onMapClick);

var marker = L.marker([51.936767, 4.513687]).addTo(mymap);

var polygon = L.polygon([
    [51.933138, 4.52141],
    [51.932979, 4.517462],
    [51.934778, 4.510896],
    [51.936101, 4.510081]
]).addTo(mymap);

</script>