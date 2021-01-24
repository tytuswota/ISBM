<?php
    include_once 'includes/dbh.php';
?>
<!DOCTYPE html>
<html>
<link rel="stylesheet" href="https://unpkg.com/leaflet@1.7.1/dist/leaflet.css" />
<script src="https://unpkg.com/leaflet@1.7.1/dist/leaflet.js"></script>
<head>
<style>
* {
  box-sizing: border-box;
}

body {
  font-family: Arial;
  padding: 10px;
  background-image: url("background.jpg");
}

@import url("https://fonts.googleapis.com/css?family=Sacramento&display=swap");

/* Header/Blog Title */
.header {
  padding: 10px;
  text-align: center;
}

.header h1 {
  opacity: 0.8;
  font-size: calc(10px + 8vh);
  line-height: calc(10px + 1vh);
  text-shadow: 0 0 5px #ffa500, 0 0 15px #ffa500, 0 0 20px #ffa500, 0 0 40px #ffa500, 0 0 60px #ff0000, 0 0 10px #ff8d00, 0 0 98px #ff0000;
  color: #FFFCE5;
  font-family: "Arial", cursive;
  text-align: center;
  animation: blink 12s infinite;
  -webkit-animation: blink 12s infinite;
}

h2 {
  color: #FFE7CF;
}

/* Create two unequal columns that floats next to each other */
/* Left column */
.leftcolumn {   
  float: left;
  width: 60%;
  margin-right: 10px;
}

/* Right column */
.rightcolumn {
  float: left;
  width: 30%;
  padding-left: 1px;
}

/* Responsive layout - when the screen is less than 800px wide, make the two columns stack on top of each other instead of next to each other */
@media screen and (max-width: 800px) {
  .leftcolumn, .rightcolumn {   
    width: 100%;
    padding: 0;
  }
}

table {
    border-collapse: collapse;
    width: 100%;
    color: #000000;
}

td, th {
    border: 1px solid #000000;
    text-align: center;
    padding: 8px;
}

#mapid { height: 650px; width: 1050px; border: 0px solid #000000; opacity: 0.85;}

</style>
</head>
<body>
<div class="header">
  <h1>Zeilboot</h1>
</div>
  <div class="leftcolumn">
    <h2>Map</h2>
    <div id="mapid"> </div>
  </div>
  <div class="rightcolumn">
      <h2>GPS gegevens</h2>
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
    </div>
  </div>

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
setInterval(updateCordes, 5000);
</script>
