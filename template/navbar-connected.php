<!-- \file : navbar-connected.html -->
<!-- \brief Navbar pour la page d'accueil quand l'utilisateur est connecté -->
<!-- \author {Théo D. & Jeremy B.} -->
<!-- \version 1 -->

<nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
    <div class="container">
        <!-- Brand and toggle get grouped for better mobile display -->
        <div class="navbar-header">
            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
            <a href = "../" class="navbar-brand">Living Lab - L'habitat intelligent</a>
        </div>
        
        <!-- Collect the nav links, forms, and other content for toggling -->
        
        <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
            <div class="navbar-form navbar-right">
                <button id = "deconnexion-home" type="submit" class="btn btn-md btn-danger">Log out</button>
            </div>
            <ul class = "nav navbar-nav navbar-right">
                <li><a href = "dashboard">Dashboard</a></li>
                <li><a href = "Alerte">Alerte</a></li>
                <li><a href = "profil">Profil</a></li>
            </ul>
        </div>
        <!-- /.navbar-collapse -->
    </div>
    <!-- /.container -->
</nav>
