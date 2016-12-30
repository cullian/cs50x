<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("quote_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        // validate submission
        if (empty($stock))
        {
            apologize("You must provide a valid symbol.");
        }
        // render quote
        render("quote.php", ["title" => "Quote", "stock" => $stock]);
    }
    
?>