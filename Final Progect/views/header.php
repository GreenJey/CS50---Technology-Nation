<!DOCTYPE html>

<html>

    <head>
        
        <meta charset="utf-8">
        
        <link rel="shortcut icon" href="https://hea-www.harvard.edu/~swolk/pictures/harvard-logo.png" type="image/x-icon">

        <!-- http://getbootstrap.com/ -->
        <link href="/css/bootstrap.min.css" rel="stylesheet"/>

        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <!-- https://jquery.com/ -->
        <script src="/js/jquery-1.11.3.min.js"></script>

        <!-- http://getbootstrap.com/ -->
        <script src="/js/bootstrap.min.js"></script>

        <script src="/js/scripts.js"></script>

        <style>
           body {
            background-image: url(/img/05.jpg); /* Путь к фоновому изображению */
           }
        </style>

    </head>

    <body>
        <div class="container">

            <div id="top">
                <div>
                    <a href="/"><img alt="C$50 Finance" src="/img/logo.png"/></a>
                    <a class="feedback" align="right" href="feedback.php"><img alt="C$50 Feedback" src="http://www.bangkokpvc.com/webmail.png" width="100" height="100"/></a>
                </div>
                <?php if (!empty($_SESSION["id"])): ?>
                    <nav role='navigation'>
                    <ul class="nav nav-pills">
                        <li><a href="quote.php"><strong><font color="white">Quote</font></strong></a></li>
                        <li><a href="buy.php"><strong><font color="white">Buy</font></strong></a></li>
                        <li><a href="sell.php"><strong><font color="white">Sell</font></strong></a></li>
                        <li><a href="history.php"><strong><font color="white">History</font></strong></a></li>
                        <li class = "setting"><a href=""><img alt= "Settings" src="/img/settings.png" width="40" height="25"/></a>
                            <ul class="menu">
                            <li><a href="password.php"><strong><font color="white">Change password</font></strong></a></li>
                            <li><a href="logout.php"><strong><font color="brown">Log Out</font></strong></a></li>
                            </ul>
                        </li>
                    </ul>
                    </nav>
                <?php endif ?>
            </div>

            <div id="middle">
