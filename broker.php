<?php

    // Username and password database
    $user = 'admin'; 
    $pass = '12345678';

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
        // Data partitioning
        $temperatur = test_input($_POST["Temperatur"]);
        $idMesin = test_input($_POST["idMesin"]);
        $lokasi = test_input($_POST["location"]);
        
        // Connect to server name 'Jihadil', TCP port: 1344, and  database name 'Sensor_Monitoring'
        $connection_string = 'DRIVER = {SQL Server};
                                        SERVER=tcp:Jihadil,1344;
                                        DATABASE=Sensor_Monitoring';
        $conn = odbc_connect( $connection_string, $user, $pass );
        
        // Create query and execute query
        $sql = "INSERT INTO monitoring (temperatur, idMesin, lokasi) VALUES ('" . $temperatur . "', '" . $idMesin . "', '" . $lokasi . "')"; // Query
        $result = odbc_exec(conn,sql);
        
        $close = odbc_close_all(); // Close ODBC connection
    } 
    else {
        echo "No data posted with HTTP POST.";
    }
    
?>
