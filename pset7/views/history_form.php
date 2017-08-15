<div id="middle">
    <table class="table table-striped">
    
        <thead>
            <tr>
                <th>Transaction</th>
                <th>Date/Time</th>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Price</th>
            </tr>
        </thead>
    
        <tbody align=left>
            <tr>
            <?php foreach ($positions as $position): ?>
            
            <tr>    
                <td><?= $position["transaction"] ?></td>
                <td><?php date_default_timezone_set('Europe/Kiev'); echo date('d.m.Y - H:i:s', strtotime($position["time"]. "UTC")) ?></td>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= "$" . number_format($position["price"] * $position["shares"], 2)?></td>
            </tr>
    
            <?php endforeach ?>

            </tr>
        </tbody>
    </table>
</div>