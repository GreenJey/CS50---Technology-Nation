<form action="recovery.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="email" placeholder="E-mail" type="email" required="">
        </div>
        <div class="form-group">
            <input class="form-control" name="password" placeholder="New password" type="password" required="">
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Password (again)" type="password" required="">
        </div>
        <div class="form-group">
            <input class="form-control" name="captcha" placeholder="<?captcha_show()?>" type="text" required="">
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Recovery
            </button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="register.php">Register</a> for an account
</div>
<div>
    or <a href="login.php">Log in</a>
</div>

