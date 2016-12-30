<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // query database for stocks that belong with current user
        $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ? ORDER BY symbol", $_SESSION["id"]);
        // find out how much cash the user has
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        // fill positions with all the positions for table
        $positions = [];
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"],
                    "total" => $stock["price"] * $row["shares"]
                ];
            }
        }
        // render form
        render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" =>  $cash[0]["cash"]]);
    }
    // else apologize
    else
    {
    apologize("Method not supported");
    }
    
?>