<?php

    /* Created by: Muhammad Jihadil (jihadil003@gmail.com)
     * Publication: https://drive.google.com/file/d/1366n3-IRN7HiNp7mXm9MVnSAszm46DyY/view?usp=share_link
     */

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
        $sql = "INSERT INTO monitoring (waktu, temperatur, idMesin, lokasi) VALUES (current_timestamp, '" . $temperatur . "', '" . $idMesin . "', '" . $lokasi . "')"; // Query
        $result = odbc_exec(conn,sql);
        
        $close = odbc_close_all(); // Close ODBC connection
    } 
    else {
        echo "No data posted with HTTP POST.";
    }
    
?>
