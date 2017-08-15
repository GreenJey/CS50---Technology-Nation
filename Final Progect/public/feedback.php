<?php
    // конфігурація
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("feedback_form.php", ["title" => "Feedback"]);
    }

    if ( strlen($_POST["message"]) <= 10 or strlen($_POST["message"]) >= 1000 )
    {
    	 apologize("The length of the message should be 10 - 1000 characters!");
    }

    function send_mail( $email, $title, $text ) 
    {
      mail($email, $title, '<!DOCTYPE html>
      <html>
        <head>
        <meta charset="UTF-8">
        <title>'.$title.'</title>
       	</head>
          <body style="margin:0">
            <div style="margin:0; padding:0; font-size: 18px; font-family: Arial, sans-serif; font-weight: bold; text-align: center; background: #FCFCFD">
              <div style="margin:0; background: #F44336; border-radius: 10px; padding: 20px; color:#fff">'.$title.'</div>
                <div style="padding:30px;">
                   <div style="background: #fff; border-radius: 10px; padding: 25px; border: 1px solid #EEEFF2">'.$text.'</div>
                </div>
              <div style="margin:0; background: #F44336; border-radius: 10px; padding: 20px; color:#fff">cs50.zzz.com.ua</div>    
            </div>
          </body>
      </html>', "From: npavlikivskij@cs50.zzz.com.ua\r\nMIME-Version: 1.0\r\nContent-Type: text/html; charset=UTF-8");
    }

		$to = "npavlikivskij@gmail.com";
		$subject = ($_POST["subject"]);
		$message = ($_POST["message"]);

		if(!(send_mail($to, $subject, $message)))
		{   
    	redirect("index.php");
		}
		else
    {
		  apologize("Error!");
    }
?>