<?php
    /**
     * config.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Configures app.
     */

    //define('ID', '719276944924114');
    //define('SECRET', 'ce75e2f2a3e2c8adb556f6858a193c4c');
    //define('URL', 'http://cs50.zzz.com.ua/fb.php');

    // display errors, warnings, and notices
    ini_set("display_errors", true);
    error_reporting(E_ALL);

    // requirements
    require("helpers.php");
    // echo __DIR__;

    // CS50 Library
    require("../vendor/library50-php-5/CS50/CS50.php");
    CS50::init(__DIR__ . "/../config.json");

    // enable sessions
    session_start();
    
    // $base_dir = "/public";
    // require authentication for all pages except /login.php, /logout.php, and /register.php
    if (!in_array($_SERVER["PHP_SELF"], ["/public/login.php", "/public/logout.php", "/public/register.php", "/public/recovery.php", "/public/confirm.php", "/public/feedback.php"]))
    {
        if (empty($_SESSION["id"]))
        {
            redirect("login.php");
        }
    }
?>
