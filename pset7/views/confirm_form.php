<form action="confirm.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="code" placeholder="Code" type="text" required="">
        </div>
        <div class="form-group">
            <input class="form-control" name="captcha" placeholder="<?captcha_show()?>" type="text" required="">
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Confirm
            </button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="login.php">Log in</a>
</div>
<div>
    or <a href="register.php">Register</a>
</div>
