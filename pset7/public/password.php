<?php

    // конфігурація
    require("../includes/config.php");

    $hash = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("password_form.php", ["title" => "Setting"]);
    }
    
    // перевірка на заповнення усіх полів та порівняння паролей
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["password1"]) || password_verify($_POST["password1"], $hash[0]["hash"]) == 0 )
        {
            apologize("Incorrectly entered old password.");
        }
        
        if (empty($_POST["password2"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]) || $_POST["password2"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match!");
        }
        else
        {
           $ad = CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($_POST["password2"], PASSWORD_DEFAULT), $_SESSION["id"]);
            
            // перевірка на унікальність username
            if ($ad === 0)
                apologize("EROR!");
            // else
            // {
                
            // }
            //dump($hash);
            // redirect to portfolio
            redirect("/index.php");
        }
    }

?>