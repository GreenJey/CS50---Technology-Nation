<form action="login.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="email" placeholder="E-mail" type="email" required="required">
        </div>
        <div class="form-group">
            <input class="form-control" name="password" placeholder="Password" type="password" required="required">
        </div>
        <div class="form-group">
            <input class="form-control" name="captcha" placeholder="<?captcha_show()?>" type="text" required="required">
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Log In
            </button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="register.php">Register</a> for an account
</div>
<div>
    or <a href="confirm.php">Activation Code</a>
</div>
<div>
    or <a href="recovery.php">Forgot password?</a>
</div>
