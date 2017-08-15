<?
// configuration
require("../includes/config.php"); 
    
$positions = CS50::query("SELECT price FROM history WHERE user_id = ? order by time DESC", $_SESSION["id"]);
    
if (count($positions) == 0)
{
  apologize("No transactions to display.");
}

$_SESSION['loader'] = 0;

//$query = mysqli_query($CONNECT, 'SELECT `text` FROM `history` LIMIT '.$_SESSION['loader'].', 2');


if ( !mysqli_num_rows($positions) ) {

	if ( $_SESSION['loader'] == 0 ) exit('empty');
	else exit('end');

	exit;
}




$_SESSION['loader'] += 2;

while ( $row = mysqli_fetch_assoc($positions) ) {


	echo '<p>'.$row['text'].'</p>';



}



?>