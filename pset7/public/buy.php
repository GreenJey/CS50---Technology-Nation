<?php
    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Buy"]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Пошук акцій у формі покупки
        $stock = lookup($_POST["symbol"]);
        
        if ($stock == false)
        {
            apologize("The requested stock does not exist.");
        }
        
        // якщо поле акцій введено не коректно (не ціле число)
        else if (preg_match("/^\d+$/", $_POST["shares"]) != true || $_POST["shares"] == 0)
        {
            apologize("You can only buy whole shares of stocks, not fractions thereof.");
        }
        else
        {
            // визначити загальну вартість акцій
            $total = $stock["price"] * $_POST["shares"];
            
            // дізнатися баланс користувача
            $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            
            // якщо не вистачає готівки
            if ($cash[0]["cash"] < $total)
            {
                apologize("You don't have enough cash to buy the requested amount of stock.");
            }
            else
            {
                CS50::query("INSERT INTO portfolio (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock["symbol"], $_POST["shares"]);
                
                // update user's cash balance 
                CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $total, $_SESSION["id"]);
                
                // insert row into transaction history table
                CS50::query("INSERT INTO history (user_id, transaction, time, symbol, shares, price) VALUES (?, ?, CURRENT_TIMESTAMP, ?, ?, ?)", $_SESSION["id"], "BUY", strtoupper($_POST["symbol"]),  $_POST["shares"], $stock["price"]);
                
                // redirect to portfolio
                redirect("/");
            }
        }
    }
?>