<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>FIC | Register</title>
    <link rel="stylesheet" href="css/style.css">
</head>

<body class="login">
    <div class="loginPage">
        <div class="regisMid">
            <h1 class="header">Register</h1>
            <form action="role.php" method="post">
                <label for="name">Name</label><br>
                <div class="name"><input class="halfIn" type="text" name="fname" placeholder="Enter Firstname"><input class="halfIn" type="text" name="lname" placeholder="Enter Lastname"></div><br>
                <label for="username">Gmail</label><br>
                <input type="text" name="username" placeholder="Enter your gmail" required><br><br>
                <label for="pass">Password</label><br>
                <input type="password" name="pass" placeholder="Enter your password" required><br><br>
                <label for="pass">Re-enter Password</label><br>
                <input type="password" name="c-pass" placeholder="Enter your password" required>
                <br><br><br>
                <div class="button">
                <button type="submit" class="button">Submit</button>
                
            </div>
            </form>
            </div>
    </div>
    <br>
        <div class="footer"><a href="login.php" class="register" class="link">Already have an account?</a></div>    
        
</body>

</html>