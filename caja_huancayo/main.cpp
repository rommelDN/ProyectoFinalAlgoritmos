#include <iostream>
#include <string>
#include <vector>
#include <limits>
//ESTRUCTURAS DE DATOS
#include "Pila.h"
#include "Cola.h"
#include "ListaEnlazada.h"
//CLASSES
#include "Cliente.h"
#include "Servicios.h"
#include "ServicioContratado.h"
#include "Cuentas.h"
#include "Seguros.h"
#include "HashTable.h"

using namespace std;
void limpiarBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void pausar() {
	cout << "\nPresione Enter para continuar...";
	limpiarBuffer();
}
void mostrarMenu() {
	cout << "\n=== SISTEMA BANCARIO ===" << endl;
	cout << "1. Gestionar Clientes" << endl;
	cout << "2. Gestionar Cuentas" << endl;
	cout << "3.	Gestionar Seguros" << endl;
	cout << "4.	Gestionar Creditos" << endl;
	cout << "5.	Gestionar Tarjetas" << endl;
	cout << "6. Gestionar Servicios Contratados" << endl;
	cout << "7. Mostrar Reportes" << endl;
	cout << "8. Salir" << endl;
	cout << "Seleccione una opcion: ";
}

void menuClientes(ListaEnlazada<Cliente<string>>& listaClientes, HashTable<Cliente<string>>& tablaClientes) {
	int opcion;
	do {
		cout << "\n=== GESTION DE CLIENTES ===" << endl;
		cout << "1. Agregar Cliente" << endl;
		cout << "2. Mostrar Clientes" << endl;
		cout << "3. Buscar Cliente por DNI" << endl;
		cout << "4. Eliminar Cliente por DNI" << endl;
		cout << "5. Volver al Menu Principal" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		limpiarBuffer();
		switch (opcion)
		{
		case 1: {
			string nombre, apellido, dni, email, telefono;
			cout << "\n--- Agregar Nuevo Cliente ---" << endl;
			cout << "Nombre: ";
			getline(cin, nombre);
			cout << "Apellido: ";
			getline(cin, apellido);
			cout << "DNI: ";
			getline(cin, dni);
			cout << "Email: ";
			getline(cin, email);
			cout << "Telefono: ";
			getline(cin, telefono);
			Cliente<string> nuevo(nombre, apellido, dni, email, telefono);
			tablaClientes.insertar(nuevo.getDNI(), nuevo);
			listaClientes.agregarFinal(nuevo);
			cout << "Cliente agregado exitosamente." << endl;
			pausar();
			break;
		}
		case 2: {
			cout << "\n--- Tabla de Clientes ---" << endl;
			tablaClientes.mostrar();
			pausar();
			break;
		}
		case 3: {
			string dni;
			cout << "\n--- Buscar Cliente por DNI ---" << endl;
			cout << "Ingrese DNI: ";
			getline(cin, dni);
			Cliente<string>* cliente = tablaClientes.buscar(dni);
			if (cliente != nullptr) {
				cout << "Cliente encontrado:\n";
				cliente->mostrar();
			}
			else {
				cout << "Error: No se encontro el cliente con el DNI proporcionado." << endl;
			}
			pausar();
			break;
		}
		case 4: {
			string dni;
			cout << "\n--- Eliminar Cliente por DNI ---" << endl;
			cout << "Ingrese DNI: ";
			getline(cin, dni);

			bool eliminado = tablaClientes.eliminar(dni);

			if (eliminado)
				cout << "Cliente eliminado correctamente.\n";
			else
				cout << "Error: No existe un cliente con ese DNI.\n";

			pausar();
			break;
		}
		case 5:
			cout << "Volviendo al menú principal..." << endl;
			break;
		default:
			cout << "Opcion invalida. Intente de nuevo." << endl;
			break;
		}

	} while (opcion != 5);
};

/*void menuClientes(ListaEnlazada<Cliente<string>>& listaClientes) {
	int opcion;
	do {
		cout << "\n=== GESTION DE CLIENTES ===" << endl;
		cout << "1. Agregar Cliente" << endl;
		cout << "2. Mostrar Clientes" << endl;
		cout << "3. Buscar Cliente por DNI" << endl;
		cout << "4. Volver al Menu Principal" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		limpiarBuffer();

		switch (opcion)
		{
		case 1: {
			string nombre, apellido, dni, email, telefono;
			cout << "\n--- Agregar Nuevo Cliente ---" << endl;
			cout << "Nombre: ";
			getline(cin, nombre);
			cout << "Apellido: ";
			getline(cin, apellido);
			cout << "DNI: ";
			getline(cin, dni);
			cout << "Email: ";
			getline(cin, email);
			cout << "Telefono: ";
			getline(cin, telefono);

			try {
				listaClientes.agregarFinal(Cliente<string>(nombre, apellido, dni, email, telefono));
				cout << "Cliente agregado exitosamente." << endl;
			}
			catch (const exception& e) {
				cout << "Error al agregar cliente: " << e.what() << endl;
			}
			pausar();
			break;
		}
		case 2: { 
			cout << "\n--- Lista de Clientes ---" << endl;
			if(listaClientes.estaVacia()) {
				cout << "No hay clientes registrados." << endl;
			} else {
				listaClientes.mostrarTodo();
			}
			pausar();
			break; 
		};
		case 3: { 
			string dni;
			cout << "\n--- Buscar Cliente por DNI ---" << endl;
			cout << "Ingrese DNI: ";
			getline(cin, dni);
			try
			{
				Cliente<string> cliente = Cliente<string>::obtenerXdni(listaClientes, dni);
				cout << "Cliente encontrado:" << endl;
				cout << "ID: " << cliente.getID() << endl;
				cout << "Nombre: " << cliente.getNombre() << " " << cliente.getApellido() << endl;
				cout << "DNI: " << cliente.getDNI() << endl;
				cout << "Email: " << cliente.getCorreo() << endl;
				cout << "Telefono: " << cliente.getTelefono() << endl;
			}
			catch (const std::exception&)
			{
				cout << "Error: No se encontro el cliente con el DNI proporcionado." << endl;
			}
			pausar();
			break; 
		};
		case 4:
			cout << "Volviendo al menu principal..." << endl;
			break; 
		
		default:
			cout << "Opcion invalida. Intente de nuevo." << endl;
			break;
		}
	} while (opcion != 4);
	
}*/

void menuCuentas(ListaEnlazada<Cuenta<string, double>>& listaCuentas,ListaEnlazada<Servicios<string,double>>&listaDeServicios) {
	int opcion;
	do {
		cout << "\n=== GESTION DE CUENTAS ===" << endl;
		cout << "1. Crear Cuenta" << endl;
		cout << "2. Mostrar Cuentas" << endl;
		cout << "3. Buscar Cuenta por Numero" << endl;
		cout << "4. Volver al Menu Principal" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		limpiarBuffer();

		switch (opcion)
		{
		case 1: {
			string numCuenta, titular, fecha;
			double tasa, limite, ahorro;
			cout << "\n--- Crear Nueva Cuenta ---" << endl;
			cout << "Numero de Cuenta: ";
			getline(cin, numCuenta);
			cout << "Titular: ";
			getline(cin, titular);
			cout << "Fecha (dd/mm/aaaa): ";
			getline(cin, fecha);
			cout << "Tasa de Interes (%): ";
			cin >> tasa;
			cout << "Limite de Retiro: ";
			cin >> limite;
			cout << "Ahorro Objetivo: ";
			cin >> ahorro;
			limpiarBuffer();
			try {
				Cuenta<string, double>::setListaServiciosGlobal(listaDeServicios);
				Cuenta<string, double> nuevaCuenta(numCuenta, titular, fecha, tasa, limite, ahorro);
				listaCuentas.agregarFinal(nuevaCuenta);
				cout << "Cuenta creada exitosamente." << endl;
				cout << "ID Cuenta: " << nuevaCuenta.getIdCuenta() << endl;


			}catch (const exception& e) {
				cout << "Error al crear cuenta: " << e.what() << endl;
			}
			pausar();
			break;
		};
		case 2: {
			cout << "\n--- Lista de Cuentas ---" << endl;
			if(listaCuentas.estaVacia()) {
				cout << "No hay cuentas registradas." << endl;
			} else {
				listaCuentas.mostrarTodo();
			}
			pausar();
			break;
		
		};
		case 3: {
			string numCuenta;
			cout << "\n--- Buscar Cuenta por Numero ---" << endl;
			cout << "Ingrese Numero de Cuenta: ";
			getline(cin, numCuenta);
			cout << "Buscando cuenta..." << endl;
			
			
			pausar();
			break;
		};
		case 4:
			cout << "Volviendo al menu principal..." << endl;
			break;
		default:
			break;
		}
	
	} while (opcion != 4);
	
}

void menuSeguros(ListaEnlazada<Seguros<string,double>>& listaSeguros, ListaEnlazada<Servicios<string, double>>& listaDeServicios,ListaEnlazada<Cliente<string>>& listaClientes) {
	int opcion;
	do {
		cout << "\n=== GESTION DE SEGUROS ===" << endl;
		cout << "1. Crear Seguro" << endl;
		cout << "2. Mostrar Seguro" << endl; //Por Cliente
		cout << "3. Ingresar Asegurados" << endl;
		cout << "4. Crear Reclamo" << endl;
		cout << "5. Volver al Menu Principal" << endl;
		cin >> opcion;
		limpiarBuffer();

		switch (opcion)
		{
		case 1: { 
			string n_cuenta, t, f_a, t_seguro;
			double meses_cov, prima_mensual, monto_cov;
			cout << "\n--- Crear Nuevo Seguro ---" << endl;
			cout << "Numero de Cuenta: ";
			getline(cin, n_cuenta);
			cout << "Titular: ";
			getline(cin, t);
			cout << "Fecha (dd/mm/aaaa): ";
			getline(cin, f_a);
			cout << "Tipo de Seguro: ";
			getline(cin, t_seguro);
			cout << "Prima Mensual: ";
			cin >> prima_mensual;
			cout << "Meses De Covertura: ";
			cin >> meses_cov;
			cout << "Monto De Covertura: ";
			cin >> monto_cov;
			limpiarBuffer();
			try{
				Seguros<string, double>::setListaServiciosGlobal(listaDeServicios);
				Seguros<string, double> nuevoSeguro(n_cuenta, t, f_a, t_seguro, meses_cov, prima_mensual, monto_cov);
				listaSeguros.agregarFinal(nuevoSeguro);
				cout << "Seguro creado exitosamente." << endl;
				cout << "ID Cuenta: " << nuevoSeguro.getIdSeguro() << endl;
			
			}catch (const exception& e) {
				cout << "Error al crear seguro: " << e.what() << endl;
			}		
			pausar();
			break; 
		};
		case 2: { break; };
		case 3: { 
			string id_seg, dni, n, r;
			double p;
			cout << "\n--- Ingresar Asegurados ---" << endl;
			cout << "ID del Seguro: ";
			getline(cin, id_seg);
			cout << "DNI del Cliente: ";
			getline(cin, dni);
			cout << "Nombre del Beneficiario: ";
			getline(cin, n);
			cout << "Relacion con el Beneficiario: ";
			getline(cin, r);
			cout << "Porcentaje de Participacion: ";
			cin >> p;
			limpiarBuffer();
			try
			{
				//Implementa la creacion del asegurado
				

			}
			catch (const exception& e)
			{
				cout << "Error al Ingresar Asegurado: " << e.what() << endl;
			}
			pausar();
			
			break; 
		};
		case 4: { break; };
		case 5:
			cout << "Volviendo al menu principal..." << endl;
			break;
		default:
			break;
		}
	
	} while (opcion!=5);
};

void menuServiciosContratados(ListaEnlazada<ServicioContratado<string>>& listaServiciosContratados,ListaEnlazada<Cliente<string>>& listaClientes,ListaEnlazada<Servicios<string, double>>& listaDeServicios) {
	int opcion;

	do {
		cout << "\n=== SERVICIOS CONTRATADOS ===" << endl;
		cout << "1. Contratar Servicio" << endl;
		cout << "2. Mostrar Servicios Contratados" << endl;
		cout << "3. Volver al Menu Principal" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		limpiarBuffer();

		switch (opcion)
		{
		case 1: {
			string fecha, dniCliente, numCuentaServicio;
			cout << "\n--- Contratar Nuevo Servicio ---" << endl;
			cout << "Fecha de Contratacion (dd/mm/aaaa): ";
			getline(cin, fecha);
			cout << "DNI del Cliente: ";
			getline(cin, dniCliente);
			cout << "Numero de Cuenta del Servicio: ";
			getline(cin, numCuentaServicio);

			try {
				Cliente<string> cliente = Cliente<string>::obtenerXdni(listaClientes, dniCliente);
				Servicios<string, double> servicio = Servicios<string, double>::obtenerXnumCuenta(listaDeServicios, numCuentaServicio);

				// Crear shared_ptr
				auto servicioPtr = make_shared<Servicios<string, double>>(servicio);
				auto clientePtr = make_shared<Cliente<string>>(cliente);

				// Contratar servicio
				listaServiciosContratados.agregarFinal(ServicioContratado<string>(fecha, servicioPtr, clientePtr));
				cout << "Servicio contratado exitosamente!" << endl;
			}catch (const exception& e) {
				cout << "Error al contratar servicio: " << e.what() << endl;
			}
			pausar();
			break;
		};
		case 2:
			cout << "\n--- Servicios Contratados ---" << endl;
			if (listaServiciosContratados.estaVacia()) {
				cout << "No hay servicios contratados." << endl;
			}
			else {
				listaServiciosContratados.mostrarTodo();
			}
			pausar();
			break;
		case 3:
			cout << "Volviendo al menu principal..." << endl;
			break;

		default:
			break;
		}
	} while (opcion != 3);
	
};

void menuReportes(ListaEnlazada<Cliente<string>>& listaClientes,ListaEnlazada<Cuenta<string, double>>& listaCuentas,ListaEnlazada<Servicios<string, double>>& listaDeServicios,ListaEnlazada<ServicioContratado<string>>& listaServiciosContratados) {
	cout << "\n=== REPORTES DEL SISTEMA ===" << endl;
	cout << "Total de Clientes: " << listaClientes.getTamanio() << endl;
	cout << "Total de Cuentas: " << listaCuentas.getTamanio() << endl;
	cout << "Total de Servicios: " << listaDeServicios.getTamanio() << endl;
	cout << "Total de Servicios Contratados: " << listaServiciosContratados.getTamanio() << endl;

	cout << "\n¿Desea ver detalles? (s/n): ";
	char opcion;
	cin >> opcion;
	limpiarBuffer();

	if (opcion == 's' || opcion == 'S') {
		cout << "\n--- Clientes ---" << endl;
		listaClientes.mostrarTodo();
		cout << "\n--- Cuentas ---" << endl;
		listaCuentas.mostrarTodo();
		cout << "\n--- Servicios ---" << endl;
		listaDeServicios.mostrarTodo();
		cout << "\n--- Servicios Contratados ---" << endl;
		listaServiciosContratados.mostrarTodo();
	}
	pausar();
}

int main() {
	ListaEnlazada<Cliente<string>> listaClientes;
	HashTable<Cliente<string>> tablaClientes(20);
	ListaEnlazada<Cuenta<string, double>> listaCuentas;
	ListaEnlazada<Servicios<string, double>> listaDeServicios;
	ListaEnlazada<ServicioContratado<string>> listaServiciosContratados;
	ListaEnlazada<Seguros<string, double>> listaSeguros; // Lista de servicios para la configuración global
	// Configuración inicial
	Cuenta<string, double>::setListaServiciosGlobal(listaDeServicios);
	Seguros<string, double>::setListaServiciosGlobal(listaDeServicios);

	int opcionPrincipal;
	do {
		mostrarMenu();
		cin >> opcionPrincipal;
		limpiarBuffer();

		switch (opcionPrincipal) {
		case 1:
			//menuClientes(listaClientes);
			menuClientes(listaClientes,tablaClientes);
			break;
		case 2:
			menuCuentas(listaCuentas, listaDeServicios);
			break;
		case 3:
			menuSeguros(listaSeguros, listaDeServicios, listaClientes);
			break;
		case 4:
			//Gestionar Creditos
			break;
		case 5:
			//Gestionar Tarjetas
			break;
		case 6:
			menuServiciosContratados(listaServiciosContratados, listaClientes, listaDeServicios);
			break;
		case 7:
			menuReportes(listaClientes, listaCuentas, listaDeServicios, listaServiciosContratados);
			break;
		case 8:
			cout << "\n¡Gracias por usar el Sistema Bancario! Hasta pronto." << endl;
			break;
		default:
			cout << "Opcion no valida! Intente de nuevo." << endl;
			pausar();
		}
	} while (opcionPrincipal != 8);

	return 0;
};