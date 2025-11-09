<?php
    $username = "your_username";
    $password = "your_password";
    $database = "your_database";
    $mysqli = new mysqli("localhost", $username, $password, $database);
    $query="CREATE TABLE tablename(id int(6) NOT NULL auto_increment,first varchar(15) NOT NULL,last varchar(15) NOT NULL,field1-name varchar(20) NOT NULL,field2-name varchar(20)NOT NULL,field3-name varchar(20) NOT NULL,field4-name varchar(30) NOT NULL, field5-name varchar(30)NOT NULL,PRIMARY KEY (id),UNIQUE id (id),KEY id_2 (id))";
    $mysqli->query("$query");
    $mysqli->close();
?>