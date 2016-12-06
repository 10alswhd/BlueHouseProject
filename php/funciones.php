<!-- Incluimos la Cabecera y con ella los Estilos CSS -->
<?php include('comunes/cabecera.php');?>

<!-- Creamos un div contenedor de los ejercicios y creamos el titulo -->
<div>
	<h2> Ejercicios de Funciones </h2>


<!-- Primera Función -->
<h3>Primera Función</h3>
<?php
	//Creamos la función
	function es_digito($n){
		if is_numeric($n){
			if ($n>0 && $n<9){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}
	//Llamamos la función
	if(isset($_GET['digito'])){
		$n1 = $_GET['digito'];
		$d1 = es_digito($n1);
		if ($d1 == true){
			print "El número introducido es un número entre 0 y 9.";
		}else{
			print "El número introducido no es un número entre 0 y 9. ";
		}//Fin del else
	}//Fin del if
	else{
		print "<p>No ha introducido ningún dígito para probar la función es_digito, recuerda ?digito=x</p>";
	}
?>


<!-- Segunda Función -->
<h3>Segunda Función</h3>
<?php
	//Creamos la función
	function su_longitud($n){
		return strlen($n);
	}
	//Llamamos la función
	if(isset($_GET['cadena'])){
		$n2 = $_GET['cadena'];
		$d2 = su_longitud($n2);
		print "<p>La longitud de la cadena ".$n2." es: ".$d2."</p>";
	}//Fin del if
	else{
		print "<p>No ha introducido ninguna cadena, recuerda ?cadena=x</p>";
	}//Fin del else
?>


<!-- Tercera Función -->
<h3>Tercera Función</h3>
<?php
	//Creamos la función
	function potencia($a,$b){
		if is_int($n){
			return pow($a, $b);
		}else{
			return false;
		}
	}
	//Llamamos la función
	if(isset($_GET['a']) && isset($_GET['b'])){
		$a = $_GET['a'];
		$b = $_GET['b'];
		$d3 = potencia($a,$b);
		if($d3){
			print "<p>La potencia de ".$a." elevado a ".$b." es: ".$d3."</p>";
		}else{
			print "<p>El valor introducido no es númerico</p>"
		}
	}//Fin del if
	else{
		print "<p>No ha introducido los digitos a y b, recuerda ?a=x&b=x</p>";
	}//Fin del else
?>


<!-- Cuarta Función -->
<h3>Cuarta Función</h3>
<?php 
	//Creamos la función
	function es_vocal($n){
		$nv= strtoupper($n);//Las pongo en mayusculas para que no diferencia a de A y considere las dos vocales.
		if ($nv!=A && $nv!=E && $nv!=I && $nv!=O && $nv!=U){
			return false;
		}else{
			return true;
		}
	}
	//Llamamos la función
	if(isset($_GET['vocal'])){
		$n4 = $_GET['vocal'];
		$d4 = es_vocal($n4);
		if ($d4 == true){
			print "El caracter ".$n4." es una vocal.";
		}else{
			print "El caracter ".$n4." no es una vocal. ";
		}//Fin del else
	}//Fin del if
	else{
		print "<p>No ha introducido ningún caracter, recuerda ?vocal=x</p>";
	}//Fin del else
?>
	

<!-- Quinta Función -->
<h3>Quinta Función</h3>
<?php 
	//Creamos la función
	function es_par($n){
		if ($n%2==0){
    			return true;
		}else{
    			return false;
		}		
	}
	//Llamamos la función
	if(isset($_GET['par'])){
		$n5 = $_GET['par'];
		$d5 = es_par($n5);
		if ($d5 == true){
			print "El número ".$n5." es par.";
		}else{
			print "El número ".$n5." no es par. ";
		}//Fin del else
	}//Fin del if
	else{
		print "<p>No ha introducido ningún caracter, recuerda ?par=x</p>";
	}//Fin del else
?>


<!-- Sexta Función -->
<h3>Sexta Función</h3>
<?php
	//Creamos la función
	function posicion($cad,$char){
		return strpos($cad,$char) ;
	}
	//Llamamos la función
	if(isset($_GET['cad']) && isset($_GET['char'])){
		$cad = $_GET['cad'];
		$char= $_GET['char'];
		$d6 = posicion($cad,$char);
		print "<p>La posición de ".$char." en ".$cad." es: ".$d6." </p>";
	}else{
		print "<p>No ha introducido ningún caracter, recuerda ?cad=x&char=x</p>";
	}//Fin del else
?>


<!-- Septima Función -->
<h3>Septima Función</h3>
<?php 
	//Creamos la función
	function mayusculas($n){
		return strtoupper($n) ;
	}
	//Llamamos la función
	if(isset($_GET['may'])){
		$n7 = $_GET['may'];
		if ($n7==strtoupper($n7)){
			print "<p>La letra ".$n7." ya está en mayusculas: </p>";
		}//Fin del if
		else{
			$d7 = mayusculas($n7);
			print "<p>La letra ".$n7." pasada a mayusculas es: ".$d7."</p>";
		}//Fin del else
	}else{
		print "<p>No ha introducido ningún caracter, recuerda ?may=x</p>";
	}//Fub del else
?>


<!-- Octava Función -->
<h3>Octava Función</h3>
<?php 
	//Creamos la función
	function cad_may($cadmay){
		return strtoupper($cadmay) ;
	}
	//Llamamos la función
	if(isset($_GET['cadmay'])){
		$n8 = $_GET['cadmay'];
		$d8 = cad_may($n8);
		print "<p>La cadena ".$n8. " pasada a mayusculas es: ".$d8."</p>";
	}else{
		print "<p>No ha introducido ninguna cadena, recuerda ?cadmay=x</p>";
	}//Fin del else
?>


<!-- Novena Función -->
<h3>Novena Función</h3>
<?php
	//Creamos la función
	function union($cad1,$cad2){
		$cad1.=' '; //añadimos un espacio entre cada cadena
		return $cad1.=$cad2 ;
	}
	//Llamamos la función
	if(isset($_GET['cad1']) && isset($_GET['cad2'])){
		$cad1 = $_GET['cad1'];
		$cad2 = $_GET['cad2'];
		$d9 = union($cad1,$cad2);
		print "<p>Las cadena unidas son: ".$d9." </p>";
	}else{
		print "<p>No ha introducido cadenas, recuerda ?cad1=x&cad2=x</p>";
	}
?>


<!-- Decima Función -->
<h3>Décima Función</h3>
<?php //decima funcion 
	//Creamos la función
	function cuadrado($n){
		$n = $n*$n;
		return $n;
	}
	//Llamamos la función
	if(isset($_GET['cuadrado'])){
		$n10 = $_GET['cuadrado'];
		$d10 = cuadrado($n10);
		print "<p>El cuadrado de ".$n10." es: ".$d10."</p>";
	}else{
		print "<p>No ha introducido un numero, recuerda ?cuadrado=x</p>";
	}
?>

<?php include('comunes/footer.php'); ?>
</div>
