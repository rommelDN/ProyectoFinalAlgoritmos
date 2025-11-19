#include <iostream>
#include <string>
#include <vector>
#include <limits>
//ESTRUCTURAS DE DATOS
#include "Pila.h"
#include "Cola.h"
#include "ListaEnlazada.h"
//ORDENAMIENTOS AVANZADOS
#include "MergeSort.h"
#include "QuickSort.h"
#include "QuickSelect.h"
//CLASSES
#include "Cliente.h"
#include "Servicios.h"
#include "ServicioContratado.h"
#include "Cuentas.h"
#include "Seguros.h"
#include "HashTable.h"
#include "Cuentas.cpp"
#include "Seguros.cpp"

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

void menuClientes(HashTable<Cliente<string>>& tablaClientes) {
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
			//listaClientes.agregarFinal(nuevo);
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

void menuCuentas(HashTable<Cuenta<string, double>>& tablaCuentas,HashTable<Servicios<string,double>>& tablaDeServicios) {
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
				Cuenta<string, double>::setTablaServiciosGlobal(tablaDeServicios);
				Cuenta<string, double> nuevaCuenta(numCuenta, titular, fecha, tasa, limite, ahorro);
				tablaCuentas.insertar(nuevaCuenta.getNumCuenta(), nuevaCuenta);
				cout << "Cuenta creada exitosamente." << endl;
				cout << "ID Cuenta: " << nuevaCuenta.getIdCuenta() << endl;


			}catch (const exception& e) {
				cout << "Error al crear cuenta: " << e.what() << endl;
			}
			pausar();
			break;
		};
		case 2: {
			cout << "\n--- Tabla de Cuentas ---" << endl;
			tablaCuentas.mostrar();
			pausar();
			break;
		
		};
		case 3: {
			string numCuenta;
			cout << "\n--- Buscar Cuenta por Numero ---" << endl;
			cout << "Ingrese Numero de Cuenta: ";
			getline(cin, numCuenta);
			cout << "Buscando cuenta..." << endl;
			Cuenta<string, double>* cuenta = tablaCuentas.buscar(numCuenta);
			if (cuenta != nullptr) {
				cout << "Cliente encontrado:\n";
				cuenta->mostrar();
			}
			else {
				cout << "Error: No se encontro el cliente con el DNI proporcionado." << endl;
			}
			pausar();
			break;
		};
		case 4: {
			pausar();
			break;
		}
		case 5:
			cout << "Volviendo al menu principal..." << endl;
			break;
		default:
			break;
		}
	
	} while (opcion != 4);
	
}

void menuSeguros(HashTable<Seguros<string,double>>& tablaSeguros,HashTable<Servicios<string, double>>& tablaDeServicios, HashTable<Cliente<string>>& tablaClientes) {
	int opcion;
	do {
		cout << "\n=== GESTION DE SEGUROS ===" << endl;
		cout << "1. Crear Seguro" << endl;
		cout << "2. Mostrar Seguro" << endl; //Por Cliente
		cout << "3. Ingresar Asegurados" << endl;
		cout << "4. Ordenar Seguros (MergeSort)" << endl;
		cout << "5. Buscar Seguro por Numero de Cuenta" << endl;
		cout << "6. Crear Reclamo " << endl;
		cout << "7. Evaluar Cola de Reclamos " << endl;
		cout << "8. Mostrar Cola de Reclamos " << endl;
		cout << "9. Mostrar PIla de Reclamos " << endl;
		cout << "10. Volver al Menu Principal" << endl;
		cin >> opcion;
		limpiarBuffer();

		switch (opcion)
		{
		case 1: { 
			string dni,n_cuenta, t, f_a, t_seguro;
			double meses_cov, prima_mensual, monto_cov;
			cout << "\n--- Crear Nuevo Seguro ---" << endl;
			cout << "DNI del Cliente: ";
			getline(cin, dni);
			Cliente<string>* cliente = tablaClientes.buscar(dni);
			if (cliente == nullptr) {
				cout << "ERROR: Cliente no encontrado.\n";
				break;
			}
			cout << "Cliente encontrado: INGRESE DATOS DE SEGURO" << endl;
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
				Seguros<string, double>::setTablaServiciosGlobal(tablaDeServicios);
				Seguros<string, double> nuevoSeguro(n_cuenta, t, f_a, t_seguro, meses_cov, prima_mensual, monto_cov);
				tablaSeguros.insertar(nuevoSeguro.getNumCuenta(), nuevoSeguro);
				cout << "Seguro creado exitosamente." << endl;
				cout << "ID Cuenta: " << nuevoSeguro.getIdSeguro() << endl;
			
			}catch (const exception& e) {
				cout << "Error al crear seguro: " << e.what() << endl;
			}		
			pausar();
			break; 
		};
		case 2: { 
			cout << "\n--- Tabla de Cuentas ---" << endl;
			tablaSeguros.mostrar();
			pausar();
			break; 
		};
		case 3: { 
			string dni, nombre, relacion, num_cuenta;
			double porcentaje;
			cout << "\n--- Ingresar Asegurados ---" << endl;
			cout << "DNI del Cliente: ";
			getline(cin, dni);
			Cliente<string>* cliente = tablaClientes.buscar(dni);
			if (cliente == nullptr) {
				cout << "ERROR: Cliente no encontrado.\n";
				break;
			}
			cout << "Cliente encontrado: INGRESE DATOS DE ASEGURADOS" << endl;
			cout << "Ingrese el numero de cuenta: ";
			getline(cin, num_cuenta);
			Seguros<string, double>* seguro = tablaSeguros.buscar(num_cuenta);
			if (seguro == nullptr) {
				cout << "ERROR: Seguro no encontrado.\n";
				break;
			}
			cout << "Nombre del Beneficiario: ";
			getline(cin, nombre);
			cout << "Relacion con el Beneficiario: ";
			getline(cin, relacion);
			cout << "Porcentaje de Participacion: ";
			cin >> porcentaje;
			limpiarBuffer();
			try
			{
				seguro->crearBeneficiarioHash(seguro, cliente, nombre, relacion, porcentaje);
			}
			catch (const exception& e)
			{
				cout << "Error al Ingresar Asegurado: " << e.what() << endl;
			}
			
			pausar();
			break; 
		};
		case 4: { 
			cout << "\n--- Ordenar Seguros ( Convirtiendo HASH TABLE - VECTOR ) ---" << endl;
			auto listas = tablaSeguros.toVector();
			if (listas.empty()) {
				cout << "No hay Seguros para ordenar.\n";
				pausar();
				break;
			}
			auto criterio = [](const Seguros<string, double>& a,
				const Seguros<string, double>& b) {
					return a.getIdSeguro() < b.getIdSeguro();
				};
			mergeSort(listas,0,(int)listas.size()-1, criterio);
			cout << "\n--- Cuentas Ordenadas ---\n";
			for (auto& l : listas) {
				l.mostrarInfo();
				cout << "------------------\n";
			}
			pausar();
			break; 
		};
		case 5: {
			string numCuenta;
			cout << "\n--- Buscar Seguro por Numero ---" << endl;
			cout << "Ingrese Numero de Cuenta: ";
			getline(cin, numCuenta);
			cout << "Buscando cuenta..." << endl;
			Seguros<string, double>* seguros = tablaSeguros.buscar(numCuenta);
			if (seguros != nullptr) {
				cout << "Cliente encontrado:\n";
				seguros->mostrar();
			}
			else {
				cout << "Error: No se encontro el cliente con el DNI proporcionado." << endl;
			}
			pausar();
			break;
		};
		case 6: {
			cout << "\n--- Crear Clamo ---" << endl;
			string id_seguro, id_cliente, descripcion, fecha, num_cuenta, dni;
			double monto;
			cout << "Ingrese Numero del Seguro: ";
			getline(cin, num_cuenta);
			Seguros<string, double>* seguro = tablaSeguros.buscar(num_cuenta);
			if (seguro == nullptr) {
				cout << "ERROR: Seguro no encontrado.\n";
				break;
			}
			cout << "Ingrese DNI del Cliente: ";
			getline(cin, dni);
			Cliente<string>* cliente = tablaClientes.buscar(dni);
			if (cliente == nullptr) {
				cout << "ERROR: Cliente no encontrado.\n";
				break;
			}
			cout << "Ingrese Descripcion del Reclamo: ";
			getline(cin, descripcion);
			cout << "Ingrese Monto del Reclamo: ";
			cin >> monto;
			limpiarBuffer();
			cout << "Ingrese Fecha del Reclamo (dd/mm/aaaa): ";
			getline(cin, fecha);
			try {
				seguro->crearReclamo(seguro->getIdSeguro(), cliente->getID(), descripcion, fecha, monto);
				cout << "Reclamo creado con exito.\n";
			}
			catch (const exception& e) {
				cout << "Error al crear reclamo: " << e.what() << endl;
			}
			pausar();
			break;
		};
		case 7: {
			cout << "\n--- Procesar Reclamos ---" << endl;
			string num_cuenta;
			cout << "Ingrese Numero del Seguro: ";
			getline(cin, num_cuenta);
			Seguros<string, double>* seguro = tablaSeguros.buscar(num_cuenta);
			if (seguro == nullptr) {
				cout << "ERROR: Seguro no encontrado.\n";
				break;
			}
			bool procesado = seguro->procesarReclamosEncolados();
			if (!procesado)
				cout << "No hay reclamos pendientes.\n";
			else
				cout << "Procesamiento finalizado.\n";
			pausar();
			break;
		};
		case 8: {
			cout << "\n--- Mostrar Cola De Reclamos ---" << endl;
			string num_cuenta;
			cout << "Ingrese Numero del Seguro: ";
			getline(cin, num_cuenta);
			Seguros<string, double>* seguro = tablaSeguros.buscar(num_cuenta);
			if (seguro == nullptr) {
				cout << "ERROR: Seguro no encontrado.\n";
				break;
			}
			seguro->mostrarColaReclamos();
			pausar();
			break;
		};
		case 9: {
			cout << "\n--- Mostrar Historial de Reclamos ---" << endl;
			string num_cuenta;
			cout << "Ingrese Numero del Seguro: ";
			getline(cin, num_cuenta);
			Seguros<string, double>* seguro = tablaSeguros.buscar(num_cuenta);
			if (seguro == nullptr) {
				cout << "ERROR: Seguro no encontrado.\n";
				break;
			}
			seguro->mostrarHistorialReclamos();
			pausar();
			break;
		}

		case 10:
			cout << "Volviendo al menu principal..." << endl;
			break;
		default:
			break;
		}
	
	} while (opcion!=10);
};

void menuServiciosContratados(
	HashTable<ServicioContratado<string>>& tablaServiciosContratados,
	HashTable<Cliente<string>>& tablaClientes,
	HashTable<Servicios<string, double>>& tablaDeServicios
) {
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
				// Convertir HashTables a vectores para usar tus métodos actuales
				auto vecClientes = tablaClientes.toListaEnlazada();
				auto vecServicios = tablaDeServicios.toListaEnlazada();
				Cliente<string> cliente = Cliente<string>::obtenerXdni(vecClientes, dniCliente);
				Servicios<string, double> servicio = Servicios<string, double>::obtenerXnumCuenta(vecServicios, numCuentaServicio);
				auto servicioPtr = make_shared<Servicios<string, double>>(servicio);
				auto clientePtr = make_shared<Cliente<string>>(cliente);
				ServicioContratado<string> nuevo(fecha, servicioPtr, clientePtr);
				tablaServiciosContratados.insertar(servicio.getNumCuenta(), nuevo);
				cout << "Servicio contratado exitosamente!" << endl;
			}
			catch (const exception& e) {
				cout << "Error al contratar servicio: " << e.what() << endl;
			}
			pausar();
			break;
		}
		case 2: {
			cout << "\n--- Servicios Contratados ---" << endl;
			tablaServiciosContratados.mostrar();
			pausar();
			break;
		}
		case 3:
			cout << "Volviendo al menu principal..." << endl;
			break;
		default:
			cout << "Opción no válida." << endl;
			break;
		}
	} while (opcion != 3);
}

/*void menuServiciosContratados(ListaEnlazada<ServicioContratado<string>>& listaServiciosContratados, ListaEnlazada<Cliente<string>>& listaClientes, ListaEnlazada<Servicios<string, double>>& listaDeServicios) {
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
	
};*/

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
	HashTable<Cliente<string>> tablaClientes(10);

	ListaEnlazada<Cuenta<string, double>> listaCuentas;
	HashTable<Cuenta<string, double>> tablaCuentas(10);

	ListaEnlazada<Seguros<string, double>> listaSeguros;
	HashTable<Seguros<string, double>> tablaSeguros(10);

	ListaEnlazada<Servicios<string, double>> listaDeServicios;
	HashTable<Servicios<string, double>> tablaDeServicios(10);

	ListaEnlazada<ServicioContratado<string>> listaServiciosContratados;
	HashTable<ServicioContratado<string>> tablaServiciosContratados(10);
	
	// Configuración inicial
	Cuenta<string, double>::setTablaServiciosGlobal(tablaDeServicios);
	Seguros<string, double>::setTablaServiciosGlobal(tablaDeServicios);

	int opcionPrincipal;
	do {
		mostrarMenu();
		cin >> opcionPrincipal;
		limpiarBuffer();

		switch (opcionPrincipal) {
		case 1:
			menuClientes(tablaClientes);
			break;
		case 2:
			menuCuentas(tablaCuentas, tablaDeServicios);
			break;
		case 3:
			menuSeguros(tablaSeguros, tablaDeServicios, tablaClientes);
			break;
		case 4:
			//Gestionar Creditos
			break;
		case 5:
			//Gestionar Tarjetas
			break;
		case 6:
			menuServiciosContratados(tablaServiciosContratados, tablaClientes, tablaDeServicios);
			break;
		case 7:
			//menuReportes(listaClientes, listaCuentas, listaDeServicios, listaServiciosContratados);
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