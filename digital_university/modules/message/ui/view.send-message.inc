<?php
include_once 'blade/view.message.blade.inc';
?>

<?php
if (isset($_GET['receiver'])) {
	$receiver = $_GET['receiver'];
	$sender = $_SESSION['globalUser']->getID();

}
else {
	echo $_GET['receiver'];
	header('Location:message.php');
	exit();
}


?>
<nav id="header-navigation">
	
	<div class="brand">
		<h1>Communication</h1>
	</div>
</nav>
<div class="container-fluid">
	<div class="row">
		<div class="col-sm-2">
			<ul class="menu">
		<div onclick="location.href='group.php?group'">
				<div class="menu-item" style="cursor: pointer;"><a href="message.php">Home</a></div>
	      </div> 
	      <div onclick="location.href='create-group.php?create-group'">
				<div class="menu-item" style="cursor: pointer;"><a href="create-group.php">Create Group</a></div>
		  </div>
		   <div onclick="location.href='send-email.php?send-email'">
				<div class="menu-item" style="cursor: pointer;"><a href="send-email.php">Send Email</a>
				</div>
			</div>
			<div onclick="location.href='email-inbox.php?email-inbox'">
				<div class="menu-item" style="cursor: pointer;"><a href="email-inbox.php">email inbox</a>
				</div>
			</div>
			
			</ul>
		</div>
		<div class="display-table-cell" id="middle">
			<div class="message">
				<h2 class="message-heading">
					<a href="#"><?php echo $receiverDetails->FirstName .' ' . $receiverDetails->MiddleName .' ' . $receiverDetails->LastName; ?></a></h2>
				<div class="message-body">
					<div class="message-box" id="message-box">
					</div>
				</div>

				<form action="" method="POST" id="com-form">
					<div>
						<input type="text" name="messageText" value="" placeholder="type your message" class="message-text" id="messageText">	
					</div>
					<div>
						<input type="submit" name="send-message" value="Send" class="btn btn-default btn-sm" id="send-message">
					</div>
				</form>
			</div>
		</div>
		<!-- <div class="display-table-cell" id="right">
<?php
// show user list
foreach ($userList as $user) {
?>
			<div class="user">
				<img src="resources/img/profile/<?php echo $user->ID ?>" class="image-circle">
				<div class="user-content">
					<h3><a href="send-message.php?receiver=<?php echo $user->ID; ?>"><?php echo $user->FirstName .' ' . $user->MiddleName. ' ' . $user->LastName; ?></a></h3>
						<p> </p>
				</div>
			</div>
<?php	
}
?>
		</div> -->
	</div>
</div>
<script type="text/javascript">
	$(document).ready(function() {
		var sender = "<?php echo $sender; ?>";
		var receiver = "<?php echo $receiver; ?>";
		var fg=0;

		// send message
		$('#com-form').submit(function(e){
			e.preventDefault();
			var message = $('#messageText').val();
			var message = message.replace("'"," ");
			$('#messageText').val('');
			$.ajax({
				method: 'POST',
				url: 'resources/live/send-message.live.php',
				data: {sender: sender, receiver: receiver, message: message},
				dataType: 'text',
				success: function() {
					console.log('success');
				}
			});
		});

		// get message
		setInterval(function() {
			if(fg==0)
			{
				$("#message-box").animate({ scrollTop: 8000}, 1000);
				fg=1;
			}
			
			$.ajax({
				method: 'GET',
				url: 'resources/live/get-message.live.php',
				data:{sender: sender, receiver: receiver},
				dataType: 'text',
				success: function($result) {
					$('#message-box').html($result);
				}
			});
		}, 500);
	});	
</script>