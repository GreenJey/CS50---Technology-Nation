<?php
    // конфігурація
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // перевірити на наявність символа 
        $stock = lookup($_POST["symbol"]);
            
        if ($stock === false)
        {
            apologize("Symbol not found.");
        }
        else
        {
            render("quote.php", ["stock" => $stock, "title" => "Quote"]);
        }
    }
    else
    {
        render("quote_form.php", ["title" => "Get Quote"]);
    }
?>