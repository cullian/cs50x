<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // get symbols of stocks user owns
        $symbols = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        // render form
        render("sell_form.php", ["title" => "Sell", "symbols" => $symbols]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if user did not select a symbol
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to sell.");
        }
        // lookup symbol
        $stock = lookup($_POST["symbol"]);
        // lookup users cash
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        // get number of shares of symbol that the user owns
        $shares = CS50::query("SELECT shares FROM portfolios WHERE symbol = ? AND user_id = ?", $stock["symbol"],  $_SESSION["id"]);
        // validate submission
        if (empty($shares))
        {
            apologize("You don't have any of that stock to sell");
        }
        // remove stocks from portfolio and update cash and record transaction
        $value = $stock["price"] * $shares[0]["shares"];
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"] , $stock["symbol"]);
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);
        CS50::query("INSERT INTO history (transaction, user_id, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", "SELL",  $_SESSION["id"],  $stock["symbol"], $shares[0]["shares"], $value);
        // back to portfolio        
        redirect("/");
    }
    
?>