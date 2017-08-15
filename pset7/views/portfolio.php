<div id="middle">
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tfoot >
            <tr align=left >
                <td><font color="white">CASH</font></td>
                <td></td>
                <td></td>
                <td></td>
                <?php print("<td>$" . number_format($cash, 2) . "</td>")?>
            </tr>
        </tfoot>    
        <tbody align=left>
            <tr>
            <?php foreach ($positions as $position): ?>
            
            <tr>    
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= "$" . $position["price"] ?></td>
                <td><?= "$" . number_format($position["price"] * $position["shares"], 2)?></td>
            </tr>
    
            <?php endforeach ?>
            </tr>
        </tbody>
    </table>
</div>