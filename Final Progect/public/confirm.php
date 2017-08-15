<?php

  // конфігурація
  require("../includes/config.php");

  if ($_SERVER["REQUEST_METHOD"] == "GET")
  {
    render("confirm_form.php", ["title" => "Confirm"]);
  }
  
  //$captcha
  function captcha_show() 
  {
    $n1 =  rand(1,100); $n2 =  rand(1,9);
    $answer = $n1 + $n2;
    $num = ("$n1 + $n2 = ?");
    $_SESSION['captcha'] = $answer;
    echo $num;
  }

	if ($_SESSION['confirm']['code'] != $_POST["code"])
	{
    apologize("Code is incorrect.");
	}
  else if($_SESSION['captcha'] != $_POST['captcha'])
  {
    apologize("Incorrect captcha.");
  }
  else
  {
  	$_SESSION["id"] = $_SESSION['confirm']['id'];
    redirect("/");
  }
?>