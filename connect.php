<?php

$password = "**";

if (!isset($_GET["key"]) || strcmp(strval($_GET["key"]), $password) !== 0) {
    echo "Invallid key";
    exit(0);
}


$servername = "**";
$username = "**";
$password = "**";
$database = "**";

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "Connected successfully\n";

date_default_timezone_set("Europe/Amsterdam");
$date = date("Y-m-d");
$time = date("G:i:s");

$temperature=intval($_GET["temperature"])/100;
$humidity=intval($_GET["humidity"])/100;
$pressure=intval($_GET["pressure"])/100;

$conn->query("INSERT INTO data (temperature, humidity, pressure, date, time) VALUES (".$temperature.", ".$humidity.", ".$pressure.", '".$date."', '".$time."')")
?>