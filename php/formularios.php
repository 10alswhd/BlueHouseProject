<!-- Incluimos la Cabecera y con ella los Estilos CSS -->
<?php include('comunes/cabecera.php');?>

<!-- Creamos un div contenedor de los ejercicios y creamos el titulo -->
<div>
	<h2> Formularios </h2>

<?php
if (isset($_GET['error'])){
	print $_GET['error'];
}
?>

<form action="llamada.php" method="get">

	<p><label for="usuario">Usuario:  </label>
	<input type="text" name="usuario" id="usuario" placeholder="Escribe tu usuario" /></p>


	<p><label for="password">Password:  </label>
	<input type="text" name="password" id="password" placeholder="Escribe tu password" /></p>

	<p><input type="submit" name="Enviar" id="Enviar"/></p>

</from>


<?php include('comunes/footer.php'); ?>
</div>
