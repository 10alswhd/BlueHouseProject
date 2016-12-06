<?php include('comunes/cabecera.php');?>

<div>
    <h2>Página de arrays</h2>
    <p>Veamos el contenido del array persona:</p>

<?php  
	//creamos array 
	$persona =[
		'nombre'=>'Aida',
		'apellido1'=>'Cumbreras',
		'apellido2'=>'Casado'
	];//fin de asignar valores al array
  
	//creamos funcion
	function llama_array($n){
		foreach ($n as $clave => $valor) {
			print "<p>El valor de la clase $clave es $valor</p>";
		}
	}//fi de funcion
	llama_array($persona);//llamamos la funcion
?>

    <h2>Página de arrays</h2>
    <p>Veamos el contenido del array nombres:</p>

<?php  
	//creamos array 
	$ciudades =['Sevilla','Huelva','Granada'];
	$nombres =['Juan','Pepito','Fulanito',$ciudades];//fin de asignar valores al array
  
	//creamos funcion
	function llama_array2($n){
		foreach ($n as $clave => $valor) {
			if (is_array($valor)){
				foreach ($valor as $clave1 => $valor1){
					print "<p>El valor de la clase $clave1 del subarray con clave $clave es $valor1</p>";
				}//fin del foreach
			}//fin del if
			else{
				print "<p>El valor de la clase $clave es $valor</p>";
			}
			
		}
	}//fi de funcion
	llama_array2($nombres);//llamamos la funcion
?>




<?php include('comunes/footer.php'); ?>
<div>
