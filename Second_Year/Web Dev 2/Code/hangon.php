<html>
    <head>
        <title>A Guessing game</title>
    </head>
    <body style="font-family: sans-serif;">
        <p>Guessing game...</p>

        <?php
            if ( $message !== false ) {
            echo("<p>$message</p>\n");
            }
        ?>
        <form method="post">
            <p><label for="guess">Input Guess</label>
            <input type="text" name="guess" id="guess" size="40" <?php echo 'value="' . htmlentities($guess) . '"'; ?> /></p>
            <input type="submit"/>
        </form>
    </body>
</html>