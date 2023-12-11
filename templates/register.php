<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>FIC | Register</title>
    <link rel="stylesheet" href="css/style.css">
</head>

<body class="login">
<?php
if(isset($_POST['submit'])) {
    $role = "user";
    $username = $_POST['username'];
    $password = $_POST['pass'];
    $conPass = $_POST['c-pass'];
    $fname = $_POST['fname'];
    $lname = $_POST['lname'];
    $passwordHash = password_hash($password , PASSWORD_DEFAULT);
    $error = array();

    if($password != $conPass){
        array_push($error , "Passwords don't match with Re-enter Password.");
    }
    if(strlen($password) < 8 or strlen($password) > 31){
        array_push($error , "Password must be about 9 - 30 words long.");
    }
    if(strlen($username) > 31){
        array_push($error , "username must less than 31 words long.");
    }
    if(strlen($fname)>31 or strlen($lname)>31){
        array_push($error , "fname and lname must less than 31 words long.");
    }

    require_once "connect.php";
    $sql = "SELECT username FROM user_info WHERE username = '$username'";
    $result = mysqli_query($conn ,$sql);
    $rowCount = mysqli_num_rows($result);
    if($rowCount > 0){
        array_push($error , "Email already exist!");
    }

    if(count($error) > 0){
        foreach($error as $error){
            echo "<div class='alert'> $error </div>";
        }
    }
    else{
        $sql = "INSERT INTO user_info (`username` , `password` , `fname` , `lname` , `role`) VALUES (? , ? , ? , ? , ?) ";
        $stmt = mysqli_stmt_init($conn);
        $prepareStmt = mysqli_stmt_prepare($stmt,$sql);
        if($prepareStmt){
            mysqli_stmt_bind_param($stmt, "sssss" , $username , $passwordHash , $fname , $lname , $role);
            mysqli_stmt_execute($stmt);
            echo "<div class='successAlt'> You are registered successfully. </div>";
        }else{
            die("somrthing went wrong.");
        }
    }
}
?>
    <div class="loginPage">
        <div class="regisMid">
            <h1 class="header">Register</h1>
            <form action="register.php" method="post">
                <label for="name">Name</label><br>
                <div class="name"><input class="halfIn" type="text" name="fname" placeholder="Enter Firstname" required><input class="halfIn" type="text" name="lname" placeholder="Enter Lastname" required></div><br>
                <label for="username">Gmail</label><br>
                <input type="text" name="username" placeholder="Enter your gmail" required><br><br>
                <label for="pass">Password</label><br>
                <input type="password" name="pass" placeholder="Enter your password" required><br><br>
                <label for="pass">Re-enter Password</label><br>
                <input type="password" name="c-pass" placeholder="Enter your password" required>
                <br><br><br>
                <div class="button">
                <button type="submit" name="submit" class="button">Submit</button>
                
            </div>
            </form>
            </div>
    </div>
    <br>
        <div class="footer"><span class="register">Already have an account? </span><a href="login.php" class="register" class="link"> Login here.</a></div>    
        
</body>

</html>