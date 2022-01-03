<?php
// TODO: Add this number to be password and id from the database, or a new column on DB.
$api_key_value = "tPmAT5Ab3j7F9";

if ($_SERVER["REQUEST_METHOD"] == "GET") {
    //connect to the database
    include("database_connect.php"); //We include the database_connect.php which has the data for the connection to the database
    // Check the connection
    if (mysqli_connect_errno()) {
      echo "Failed to connect to MySQL: " . mysqli_connect_error();
    }
    
    $sql = "SELECT id, PASSWORD, 
			SENT_NUMBER_1, SENT_NUMBER_2, SENT_NUMBER_3, SENT_NUMBER_4, 
			SENT_BOOL_1, SENT_BOOL_2, SENT_BOOL_3, RECEIVED_BOOL1, 
			RECEIVED_BOOL2, RECEIVED_BOOL3, RECEIVED_BOOL4, 
			RECEIVED_NUM1, RECEIVED_NUM2, RECEIVED_NUM3, RECEIVED_NUM4
			FROM ESPtable2";
    
    if ($result = $con->query($sql)) {
        $rows = array();
        while($r = mysqli_fetch_assoc($result)) {
            print json_encode($r);
        }        
        $result->free();
    }
    $con->close();
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    //connect to the database
    include("database_connect.php"); //We include the database_connect.php which has the data for the connection to the database
    // Check the connection
    if (mysqli_connect_errno()) {
      echo "Failed to connect to MySQL: " . mysqli_connect_error();
    }

    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $column = test_input($_POST["column"]);
        $value = test_input($_POST["value"]);
        
        $sql  = "UPDATE ESPtable2 SET ".$column." = ".$value."";
        
        if ($con->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $con->error;
        }
        $con->close();
    }
    else {
        echo "Wrong API Key provided.";
    }
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}