<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" 
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<head>
<title>
Flight Survey 
</title>
</head>
<body>

<?php
if (empty($_POST['flight_number']) || empty($_POST['flight_date'])|| 
empty($_POST['departure_time']) || empty($_POST['departing_airport']))
 echo "<p>You must enter your flight information!
 Click your browser's Back button to 
 return to the Guest Book form.</p>";
 else {
 $DBConnect = @mysql_connect("localhost", "root", 
 "mgs314");
 if ($DBConnect === FALSE)
 echo "<p>Unable to connect to the database 
 server.</p>"
 . "<p>Error code " . mysql_errno()
 . ": " . mysql_error() . "</p>";
 
 
 else {
 $DBName = "Survey";
 if (!@mysql_select_db($DBName, $DBConnect)) {
 $SQLstring = "CREATE DATABASE $DBName";
 $QueryResult = @mysql_query($SQLstring,
 $DBConnect);
 if ($QueryResult === FALSE)
 echo "<p>Unable to execute the 
 query.</p>"
 . "<p>Error code " . mysql_errno($DBConnect)
. ": " . mysql_error($DBConnect)
 . "</p>";
 else
 echo "<p>Your survey is the first entry!</p>";
 }
 mysql_select_db($DBName, $DBConnect);
$TableName = "Results";
 $SQLstring = "SHOW TABLES LIKE '$TableName'";
 $QueryResult = @mysql_query($SQLstring, $DBConnect);
 if (mysql_num_rows($QueryResult) == 0) {
 $SQLstring = "CREATE TABLE $TableName 
 (countID SMALLINT
 NOT NULL AUTO_INCREMENT PRIMARY KEY,
 flight_number INT, flight_date DATE, departure_time TIME, 
 departing_airport VARCHAR(40), destination VARCHAR(40),
 staff INT, storage INT, seating INT, 
 cleanliness INT, noise INT)";
 
 $QueryResult = @mysql_query($SQLstring, 
 $DBConnect);
 if ($QueryResult === FALSE)
 echo "<p>Unable to create the table.</p>"
 . "<p>Error code " . mysql_errno($DBConnect)
 . ": " . mysql_error($DBConnect) . 
 "</p>";
}
 
 
$FlightNumber = stripslashes($_POST['flight_number']);
$FlightDate = stripslashes($_POST['flight_date']);
$DepartureTime = stripslashes($_POST['departure_time']);
$DepAirport = stripslashes($_POST['departing_airport']);
$Destination = stripslashes($_POST['destination']);
$staff =($_POST['staff']);
$storage =($_POST['storage']);
$seating =($_POST['seating']);
$cleanliness =($_POST['cleanliness']);
$noise =($_POST['noise']);
$SQLstring = "INSERT INTO $TableName 
 VALUES(NULL, '$FlightNumber', '$FlightDate', '$DepartureTime', '$DepAirport',
 '$Destination', '$staff', '$storage', '$seating', '$cleanliness', '$noise')";
 $QueryResult = @mysql_query($SQLstring, $DBConnect);
 if ($QueryResult === FALSE)
 echo "<p>Unable to execute the 
 query.</p>"
 . "<p>Error code " . mysql_errno($DBConnect)
 . ": " . mysql_error($DBConnect) . "</p>";
 else
 echo "<h1>Thank you for taking our survey!</h1>";
 }
 mysql_close($DBConnect);
 }
?>

</body>
</html>
