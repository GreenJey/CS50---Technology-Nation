<form action="password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="email" placeholder="E-mail" type="email" required="">
        </div>
        <div class="form-group">
            <input class="form-control" name="password1" placeholder="Old password" type="password" required="">
        </div>
        <div class="form-group">
            <input class="form-control" name="password2" placeholder="New password" type="password" required="">
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Password (again)" type="password" required="">
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Apply
            </button>
        </div>
    </fieldset>
</form>
<!--<div>-->
<!--    or <a href="login.php">log in</a>-->
<!--</div>-->