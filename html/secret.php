<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
    </head>
    <body>
    
        <?php
    if (isset($_POST['mot_de_passe']) AND $_POST['mot_de_passe'] ==  "pisecure") // Si le mot de passe est bon
    {
     header('Location: http://192.168.1.22/live.php');
	 exit();
    ?>
    <?php
    }
    else // Sinon, on affiche un message d'erreur
    {
        header('Location: http://192.168.1.22/index.html');
		exit();
    }
    ?>
    
        
    </body>
</html>
