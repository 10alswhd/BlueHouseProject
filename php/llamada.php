<?php
	if (isset($_GET['usuario']) && isset($_GET['password'])){
		if($_GET['usuario'] == 'Bienve' && $_GET['password'] == 123456){
			print 'Acceso Correcto';
		}
		else{
			if($_GET['usuario'] == '' && $_GET['password'] == ''){
				header('Location: http://ejercicios.com/formularios.php?error=No ha introducido nada');
			}else{
				header('Location: http://ejercicios.com/formularios.php?error=Error de nombre o password');
			}
		}
	}else{
		header('Location: http://ejercicios.com/formularios.php');
	}
?>
