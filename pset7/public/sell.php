<?php
    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = CS50::query("SELECT symbol FROM portfolio WHERE user_id = ?", $_SESSION["id"]);
        // else render form
        render("sell_form.php", ["title" => "Sell", "rows"=> $rows]);
    }

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to sell.");
        }
        else if (empty($_POST["shares"]) || $_POST["shares"] < 1)
        {
            apologize("These stocks have not yet been purchased.");
        }
        else 
        {
            $row = CS50::query("SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], strtoupper ($_POST["symbol"]));
            
            // calculate
               
            $stock = lookup($_POST["symbol"]);
                
            $total = $stock["price"] * $_POST["shares"];
                
            if ($row == false)
            {
                apologize("You don't have shares for selling.");
            }
            else if ($_POST["shares"] > $row[0]["shares"])
            {
                apologize("Too many shares.");
            }   
            else if  ($_POST["shares"] == $row[0]["shares"])
            {
                $delete = CS50::query("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $stock["symbol"]);
            }
            
                // оновити таблицю портфоліо
                CS50::query("UPDATE portfolio SET shares = shares - ? WHERE id = ?", $_POST["shares"], $row[0]["id"]);
                
                // оновити залишок коштів користувача з доходами від продажу акцій
                CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total, $_SESSION["id"]);
                
                // Вставити рядок в таблицю історії
                CS50::query("INSERT INTO history (user_id, transaction, time, symbol, shares, price) VALUES (?, ?, CURRENT_TIMESTAMP, ?, ?, ?)", $_SESSION["id"], "SELL", strtoupper($_POST["symbol"]),  $_POST["shares"], $stock["price"]);
                    
                // redirect to portfolio
                redirect("/index.php");
            
        }
    }
?>