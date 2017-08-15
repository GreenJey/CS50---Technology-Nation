<?php

    // конфігурація
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("register_form.php", ["title" => "Register"]);
    }

    // згенерувати випадковий ключ для e-mail
    function random_str( $num = 30 ) 
    {
        return substr(str_shuffle('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'), 0, $num);
    }

    //$captcha = ($_POST['captcha']);
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
        else if (!preg_match('/^[A-z0-9]{10,30}$/', $_POST['password']))
        {    
            apologize("The password is incorrect and can contain 10 - 30 characters (A-z / 0-9)");
        }    
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match!");
        }
        // else if($_SESSION['captcha'] != $_POST['captcha'])
        // {
        //     apologize("Incorrect captcha.");
        // }
        
        // додавання нового user до бази даних
        $add = CS50::query("INSERT IGNORE INTO users (username, email, hash, cash) VALUES(?, ?, ?, 10000.0000)", $_POST["username"], $_POST["email"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        // перевірка на унікальність username or E-mail
        if ($add === 0)
        {
            apologize("Duplicate username or E-mail!");
        }

         // відправка E-mail
        $code = random_str(5);

        $_SESSION['confirm'] = array(
            'type' => 'register',
            'email' => $_POST['email'],
            'password' => $_POST['password'],
            'code' => $code,
        );

        mail($_POST['email'], 'Регистрация', "Код подтверждения регистрации: <b>$code</b>");
        
        // Якщо реєстрація буде успішною, ви також зможете ввійти до нового користувача (як за "запам'ятовування" id в $_SESSION ), а потім перенаправлення до index.php .
        //$rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        //$id = $rows[0]["id"];
        
        //$_SESSION["id"] = $id;

        // redirect to portfolio
        redirect("/confirm.php");
        
    }

?>