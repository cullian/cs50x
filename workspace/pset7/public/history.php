<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // query database for history that belong with current user
        $history = CS50::query("SELECT * FROM history WHERE user_id = ? ORDER BY date_time", $_SESSION["id"]);

        // render form
        render("history.php", ["title" => "Portfolio", "history" => $history]);
    }
    // else apologize
    else
    {
    apologize("Method not supported");
    }
    
?>