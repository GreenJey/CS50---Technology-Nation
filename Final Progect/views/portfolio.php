<div id="middle">
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
                <th>Info</th>
            </tr>
        </thead>
        <tfoot >
            <tr align="left" >
                <td><font><strong>CASH</font></strong></td>
                <td></td>
                <td></td>
                <td></td>
                <td><?php print("<td>$" . number_format($cash, 2) . "</td>")?></td>
            </tr>
        </tfoot>    
        <tbody align="left">
            <tr>
            <?php foreach ($positions as $position): ?>
            </tr>
            
            <tr>    
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= "$" . $position["price"] ?></td>
                <td><?= "$" . number_format($position["price"] * $position["shares"], 2)?></td>
                <td>
                    <div class="form-group">
                    <button onclick="alert('Кількість: <?= $position["shares"] ?>')" class="btn btn-default" type="submit">Click</button>
                    </div>
                </td>
            </tr>
    
            <?php endforeach ?>
            </tr>
        </tbody>
    </table>
</div>