<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    $rows = CS50::query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name1, admin_name2) AGAINST (?)", $_GET["geo"]);
    
    foreach ($rows as $row)
    {
        array_push($places, $row);
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>