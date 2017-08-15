<?php
    // configuration
    require("../includes/config.php"); 
    
    $positions = CS50::query("SELECT transaction, time, symbol, shares, price FROM history WHERE user_id = ? order by time DESC", $_SESSION["id"]);
    
    if (count($positions) == 0)
    {
        apologize("No transactions to display.");
    }
    // else
    // {
    //     $positions = [];
        
    //     foreach($rows as $row)
    //     {    
    //         $positions[] = [
    //             "transaction" => $row["transaction"],
    //             "time" => $row["time"],
    //             "symbol" => $row["symbol"],
    //             "shares" => $row["shares"],
    //             "price" => $row["price"]
    //         ];
    //     }
        
        // render portfolio
        render("history_form.php", ["positions" => $positions, "title" => "History"]);
    //}
?>