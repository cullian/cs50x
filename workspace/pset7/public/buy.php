<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        // validate
        if ($stock === false)
        {
            apologize("You must provide a valid symbol.");
        }
        if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("You must provide a positive integer.");
        }
        // make sure we have enough to buy it
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $rows[0]["cash"];
        $cost = $stock["price"] * $_POST["shares"];
        if ($cost > $cash)
        {
            apologize("You aint got enuff!");
        }
        // insert new stock into portfolios or update shares if it already exists
        CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",  $_SESSION["id"],  $stock["symbol"],  $_POST["shares"]);
        // update users cash
        CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
        // record transaction
        CS50::query("INSERT INTO history (transaction, user_id, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", "BUY",  $_SESSION["id"],  $stock["symbol"],  $_POST["shares"], $cost);
        // back to portfolio        
        redirect("/");
    }
    
?>