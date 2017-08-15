<?php

    // конфігурація
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("recovery_form.php", ["title" => "Recovery"]);
    }

    //$captcha 
    function captcha_show() {
        $n1 =  rand(1,100); $n2 =  rand(1,9);
        $answer = $n1 + $n2;
        $num = ("$n1 + $n2 = ?");
        $_SESSION['captcha'] = $answer;
        echo $num;
    }
    
    // перевірка на заповнення усіх полів та порівняння паролей
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (!filter_var(($_POST["email"]), FILTER_VALIDATE_EMAIL)) 
        {
            apologize("E-mail is incorrect.");
        }
        else if (!CS50::query("SELECT id FROM users WHERE email = ?", $_POST["email"]))
        {
            apologize("E-mail not found!");
        }
        else if (!preg_match('/^[A-z0-9]{8,30}$/', $_POST['password']))
        {    
            apologize("The password is incorrect and can contain 8 - 30 characters (A-z / 0-9)");
        }    
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("The password does not match!");
        }
        else if($_SESSION['captcha'] != $_POST['captcha'])
        {
            apologize("Incorrect captcha.");
        }
        else
        {
           $ad = CS50::query("UPDATE users SET hash = ? WHERE email = ?", password_hash($_POST["password"], PASSWORD_DEFAULT), $_POST["email"]);
           if ($ad === 0)
                apologize("ERROR!");
        }

        $new_pass = $_POST["password"];

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

        $to = ($_POST["email"]);
        $subject = 'New password';
        $message = "Your new password is: $new_pass";
        
        if(!(send_mail($to, $subject, $message)))
        {
            redirect("login.php");
        }
        else
            apologize("Error!");
    }
?>