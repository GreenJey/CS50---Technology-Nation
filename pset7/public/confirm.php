<?php

    // конфігурація
    require("../includes/config.php");

    $hash = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("confirm_form.php", ["title" => "Confirm"]);
    }
    
  function not_found() 
  {
		exit('Страница 404');
	}

	if ( !$_SESSION['confirm']['code'] )
	{
		not_found();
	}
	else
	{
		redirect("/confirm.php");
	}

?>