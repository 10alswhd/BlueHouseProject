<!-- Creamos el formulario de tipo radio -->

<?php
	$estado_civil = [[1,'Soltero'],[2,'Casado'],[3,'Divorciado']]
?>

<h3> Formulario de Tipo Radio </h3>
<form action="llamada.php" method="post">

<?php
	foreach ($estado_civil as $estado) {
		print "<input type='radio' name='estado' value='$estado[0]' id='$estado[1]'><label for='$estado[1]'>$estado[1]</label>";
	}
?>

</from>
<p><input type="submit" name="Enviar" id="Enviar"/></p>
