<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>FIC | Login</title>
    <link rel="stylesheet" href="css/style.css">
</head>

<body class="login">
    <?php
    if(isset($_POST['submit'])){
        $username = $_POST['username'];
        $password = $_POST['pass'];
        require_once("connect.php");
        $sql = "SELECT `ID` , `username` , `password` , `role` ,`fname` FROM user_info WHERE username = '$username'";
        $result = mysqli_query($conn , $sql);
        $user = mysqli_fetch_array($result , MYSQLI_ASSOC);
        if($user){
            if(password_verify($password , $user["password"])){
                session_start();
                $_SESSION['id'] = $user['ID'];
                $_SESSION['name'] = $user['fname'];
                if($user['role'] == 'user'){
                    header("Location: user.php");
                    die();
                }elseif($user['role'] == 'viewer'){
                    header("Location: viewer.php");
                    die();
                }elseif($user['role'] == 'admin'){
                    header("Location: admin.php");
                    die();
                }else{
                    header("Location: reject.php");
                    die();
                }
            }else{
                echo "<div class='alert'> Password is incorrect. </div>";
            }
        }else{
            echo "<div class='alert'> Email doesn't exist. </div>";
        }
    }
    ?>
    <div class="loginPage">
        <div class="loginMid">
            <h1 class="header">Login</h1>
            <form action="login.php" method="post">
                <label for="username">Gmail</label><br>
                <input type="text" name="username" placeholder="Enter your gmail" required><br><br>
                <label for="pass">Password</label><br>
                <input type="password" name="pass" placeholder="Enter your password" required>
                <br><br><br>
                <div class="button">
                <button type="submit" name="submit" class="button">Login</button>
                
            </div>
            </form>
            </div>
    </div>
    <br>
        <div class="footer"><span class="register">Don't have an account yet? </span><a href="register.php" class="register" class="link"> Register here.</a></div>    
        
</body>

</html>