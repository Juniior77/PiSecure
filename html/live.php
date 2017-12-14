<!doctype html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="VILAIRE Guillaume">
    <link rel="icon" href="../../../../favicon.ico">

    <title>PiSecure</title>

    <!-- Bootstrap core CSS -->
    <link href="style/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="starter-template.css" rel="stylesheet">
  </head>

  <body>

    <nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
      <a class="navbar-brand" href="#">PiSecure</a>
      <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>

      <div class="collapse navbar-collapse" id="navbarsExampleDefault">
        <ul class="navbar-nav mr-auto">
          <li class="nav-item">
            <a class="nav-link" href="index.html">Accueil</a>
          </li>
          <li class="nav-item active">
            <a class="nav-link" href="live.php">Live<span class="sr-only">(current)</span></a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="enregistrement.php">Enregistrement</a>
          </li>
          </li>
        </ul>
      </div>
    </nav>

    <main role="main" class="container">

      <div class="starter-template">
        <h1>Visualisation de la caméra</h1>
		<div class="jumbotron">
			<OBJECT classid="clsid:9BE31822-FDAD-461B-AD51-BE1D1C159921"
			codebase="http://downloads.videolan.org/pub/videolan/vlc/latest/win32/axvlc.cab"
			width="480" height="320" id="vlc" events="True">
			<param name="Src" value="http://192.168.1.22:8080/" />
			<param name="ShowDisplay" value="True" />
			<param name="AutoLoop" value="False" />
			<param name="AutoPlay" value="True" />
			<embed id="vlcEmb" type="application/x-google-vlc-plugin" version="VideoLAN.VLCPlugin.2" autoplay="yes" loop="no" width="640" height="480"
			target="http://192.168.1.22:8080/" ></embed>
			</OBJECT>

		</div>
      
      </div>

    </main><!-- /.container -->


    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="style/js/bootstrap.min.js"></script>
  </body>
</html>
