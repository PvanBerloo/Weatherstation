<?php
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

$result = $conn->query("SELECT temperature, humidity, pressure FROM data ORDER BY ID DESC LIMIT 1;");

if ($result->num_rows > 0) {
    // output data of each row
    $row = $result->fetch_assoc();
    $temperature=$row["temperature"];
    $humidity=$row["humidity"];
    $pressure=$row["pressure"];
    
    echo "{\n"; 
    echo '"temperature": ' . $temperature . ",\n";
    echo '"humidity": ' . $humidity . ",\n";
    echo '"pressure": ' . $pressure . "\n";
    echo "}";
} else {
    echo "0 results";
}
$conn->close();
?>