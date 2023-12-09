<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>FIC</title>
    <link rel="stylesheet" href="css/style.css">
</head>

<body class="login">
    <div class="loginPage">
        <div class="loginMid">
            <h1 class="header">Login</h1>
            <form action="role.php" method="post">
                <label for="username">Gmail</label><br>
                <input type="text" name="username" placeholder="Enter your gmail" required><br><br>
                <label for="pass">Password</label><br>
                <input type="password" name="pass" placeholder="Enter your password" required>
                <br><br><br>
                <div class="button">
                <button type="submit" class="button">Login</button>
                
            </div>
            </form>
            </div>
    </div>
    <br>
        <div class="footer"><a href="register.php" class="register" class="link">Don't have an account yet?</a></div>    
        
</body>

</html>