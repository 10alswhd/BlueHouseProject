package com.example;

public class Empresa {
	
	private Empleado[] empleados;
	
	public Empresa(Empleado[] empleados) {
		this.empleados = empleados;
	}
	
	public int obtenerCuantoEmpleadosPorLaA(){
		int cuantos = 0;
		for (int i = 0; i < empleados.length; i++) {
			String primeraLetra = "" + empleados[i].getNombre().charAt(0);
			primeraLetra = primeraLetra.toLowerCase();
			if(primeraLetra.equals("a")){
				cuantos++;
			}
		}
		return cuantos;
	}
	
	public Empleado[] obtenerEmpleadosPorLaA(){
		int cuantos = 0;
		for (int i = 0; i < empleados.length; i++) {
			String primeraLetra = "" + empleados[i].getNombre().charAt(0);
			primeraLetra = primeraLetra.toLowerCase();
			if(primeraLetra.equals("a")){
				cuantos++;
			}
		}
		
		Empleado[] porLaAArray = new Empleado[cuantos];
		int indiceActual = 0;
		for (int i = 0; i < empleados.length; i++) {
			String primeraLetra = "" + empleados[i].getNombre().charAt(0);
			primeraLetra = primeraLetra.toLowerCase();
			if(primeraLetra.equals("a")){
				porLaAArray[indiceActual] = empleados[i];
				indiceActual++;
			}
		}
		
		return porLaAArray;
	}

	public static void main(String[] args) {
		Empleado[] empleados = {
				new Empleado("Juan", "m", 15),
				new Empleado("Diego", "m", 25),
				new Empleado("Ana", "f", 20),
				new Empleado("Alberto", "m", 45),
				new Empleado("Lucas", "m", 18),
				new Empleado("Ananias", "m", 15)
		};
		
		Empresa empresa = new Empresa(empleados);
		
		// Cuantos empiezan por la A
		System.out.println(empresa.obtenerCuantoEmpleadosPorLaA());
		
		Empleado[] porLaAArray = empresa.obtenerEmpleadosPorLaA();
		for (int i = 0; i < porLaAArray.length; i++) {
			System.out.println(porLaAArray[i].getNombre());
		}
	}
	
}

class Empleado{
	
//	 sexo nombre y edad.
	
	private String nombre;
	private String sexo;
	private int edad;
	
	public Empleado(String nombre, String sexo, int edad) {
		this.nombre = nombre;
		this.sexo = sexo;
		this.edad = edad;
	}
	
	public String getNombre() {
		return nombre;
	}
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}
	public String getSexo() {
		return sexo;
	}
	public void setSexo(String sexo) {
		this.sexo = sexo;
	}
	public int getEdad() {
		return edad;
	}
	public void setEdad(int edad) {
		this.edad = edad;
	}
	
}
