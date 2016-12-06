<?php
include_once 'my.pw.php'
  $conn =  mysqli_connect($mysql_db_address, $mysql_username ,$mysql_password,$mysql_db_name);
  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
}
?>
