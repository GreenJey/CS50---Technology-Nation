<?php
    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("login_form.php", ["title" => "Log In"]);
    }

    //$captcha 
    function captcha_show() {
        $n1 =  rand(1,100); $n2 =  rand(1,9);
        $answer = $n1 + $n2;
        $num = ("$n1 + $n2 = ?");
        $_SESSION['captcha'] = $answer;
        echo $num;
    }

    // else if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (!filter_var(($_POST["email"]), FILTER_VALIDATE_EMAIL)) 
        {
            apologize("E-mail is incorrect.");
        }
        else if($_SESSION['captcha'] != $_POST['captcha'])
        {
            apologize("Incorrect captcha.");
        }

        // база даних запитів для користувача
        $rows = CS50::query("SELECT * FROM users WHERE email = ?", $_POST["email"]);

        // якщо ми знайшли користувача, перевірте пароль
        if (count($rows) == 1) // count — Подсчитывает количество элементов массива или что-то в объекте
        {
            $row = $rows[0];

            // порівняти хеш входу користувача з хешем, який знаходиться в базі даних
            if (password_verify($_POST["password"], $row["hash"]))
            {
                // якщо користувач зараз увійшов, зберігаючи ідентифікатор користувача в сеансі
                $_SESSION["id"] = $row["id"];

                // redirect to portfolio
                redirect("/");
            }
        }

        // else apologize
        apologize("Invalid password.");
    }
?>
