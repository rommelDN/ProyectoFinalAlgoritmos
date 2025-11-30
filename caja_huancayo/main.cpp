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
#include "DataSetGenerator.h"
//CLASSES
#include "Cliente.h"
#include "Servicios.h"
#include "ServicioContratado.h"
#include "Cuentas.h"
#include "Seguros.h"
#include "HashTable.h"
#include "Cuentas.cpp"
#include "Seguros.cpp"
#include "CreditoPersonal.h"
#include "CreditoEmpresarial.h"
#include "CreditoVivienda.h"
#include "Diseno.h"
// INCLUDES DE TARJETAS
#include "Tarjetas.h"
#include "TarjetaCredito.h"
#include "TarjetaDebito.h"

using namespace std;
void limpiarBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void pausar() {
	cout << "\nPresione Enter para continuar...";
	limpiarBuffer();
}

void limpiarConsola() {
	system("cls");
}

void dibujarMenu();

void dibujarMenuCuentas();
void dibujarMenuSeguros();
void dibujarMenuTransaccion();

void mostrarMenu() {
	
	cout << "\n=== SISTEMA BANCARIO ===" << endl;
	cout << "1. Gestionar Clientes" << endl;
	cout << "2. Gestionar Cuentas" << endl;
	cout << "3.	Gestionar Seguros" << endl;
	cout << "4.	Gestionar Creditos" << endl;
	cout << "5.	Gestionar Tarjetas" << endl;
	cout << "6. Gestionar Servicios Contratados" << endl;
	//cout << "7. Mostrar Reportes" << endl;
	cout << "7. Gestionar Transacciones" << endl;
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
			cout << "Volviendo al men� principal..." << endl;
			break;
		default:
			cout << "Opcion invalida. Intente de nuevo." << endl;
			break;
		}

	} while (opcion != 5);
};

void menuCuentas(HashTable<Cuenta<string, double>>& tablaCuentas, HashTable<Servicios<string, double>>& tablaDeServicios) {
	
	int opcion;
	do {
		dibujarMenuCuentas();
		gotoxy(5, 10);
		cout << "\n=== GESTION DE CUENTAS ===" << endl;
		cout << "1. Crear Cuenta" << endl;
		cout << "2. Mostrar Cuentas" << endl;
		cout << "3. Buscar Cuenta por Numero" << endl;
		cout << "4. Depositar" << endl;
		cout << "5. Retirar" << endl;
		cout << "6. Ordenar Cuentas (MergeSort)" << endl;
		cout << "7. Ordenar Cuentas (QuickSort)" << endl;
		cout << "8. Generar Data Set " << endl;
		cout << "9. Calcular Intereses " << endl;
		cout << "10. Volver al Menu Principal" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		
		limpiarBuffer();
		system("cls");
		dibujarMenuCuentas();
		gotoxy(5, 10);

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


			}
			catch (const exception& e) {
				cout << "Error al crear cuenta: " << e.what() << endl;
			}
			pausar();
			system("cls");
			//dibujarMenuCuentas();
			//gotoxy(5, 10);
			break;
			
		};
		case 2: {
			cout << "\n--- Tabla de Cuentas ---" << endl;
			tablaCuentas.mostrar();
			pausar();
			system("cls");
			//dibujarMenuCuentas();
			//gotoxy(5, 10);
			break;
		};
		case 3: {
			string numCuenta;
			cout << "\n--- Buscar Cuenta por Numero ---" << endl;
			cout << "Ingrese Numero de Cuenta: ";
			getline(cin, numCuenta);
			cout << "Buscando cuenta..." << endl;
			Cuenta<string, double>* cuenta = tablaCuentas.buscar(numCuenta);
			Servicios<string, double>* servicio = tablaDeServicios.buscar(numCuenta);
			if (cuenta != nullptr) {
				cout << "Cliente encontrado:\n";
				cuenta->mostrar();
			}
			else {
				cout << "Error: No se encontro el cliente con el DNI proporcionado." << endl;
			}
			system("cls");
			pausar();
			break;
		};
			  /*case 4: {
				  cout << "\n--- Depositar A Cuenta ---" << endl;
				  string numCuenta;
				  double monto;
				  cout << "Ingrese Numero de Cuenta: ";
				  getline(cin, numCuenta);
				  Cuenta<string, double>* cuenta = tablaCuentas.buscar(numCuenta);
				  Servicios<string, double>* servicio = tablaDeServicios.buscar(numCuenta);
				  if (cuenta == nullptr) {
					  cout << "Error: No se encontro la cuenta con el numero proporcionado." << endl;
					  pausar();
					  break;
				  }
				  cout << "Ingrese Monto a Depositar: ";
				  cin >> monto;
				  limpiarBuffer();
				  double saldoAnterior = servicio->getSaldo();
				  cuenta->depositar(monto);
				  if (cuenta->getSaldo() != saldoAnterior) {
					  servicio->setSaldo(saldoAnterior + monto);
					  cout << "Saldo actualizado en el sistema." << endl;
				  }
				  delete cuenta;
				  pausar();
				  break;
			  }*/
		case 4: {
			cout << "\n--- Depositar A Cuenta ---" << endl;
			string numCuenta;
			double monto;

			cout << "Ingrese Numero de Cuenta: ";
			getline(cin, numCuenta);


			Cuenta<string, double>* cuenta = tablaCuentas.buscarRef(numCuenta);
			Servicios<string, double>* servicio = tablaDeServicios.buscarRef(numCuenta);
			if (cuenta == nullptr || servicio == nullptr) {
				cout << "Error: No se encontro la cuenta." << endl;
				pausar();
				break;
			}
			cout << "Ingrese Monto a Depositar: ";
			cin >> monto;
			limpiarBuffer();
			double saldoAnterior = servicio->getSaldo();

			cuenta->depositar(monto);

			if (cuenta->getSaldo() != saldoAnterior) {
				cout << "Saldo actualizado en el sistema." << endl;
			}
			system("cls");
			pausar();
			break;
		}
		case 5: {
			cout << "\n--- Retirar A Cuenta ---" << endl;
			system("cls");
			pausar();
			break;
		}
		case 6: {
			cout << "\n--- Ordenar Cuentas ( Convirtiendo HASH TABLE - VECTOR ) ---" << endl;
			auto listas = tablaCuentas.toVector();
			if (listas.empty()) {
				cout << "No hay Cuentas para ordenar.\n";
				pausar();
				break;
			}
			////////////////////////////////////
			//ORDENAMIENTO CON MERGESORT
			////////////////////////////////////
			auto criterio = [](const Cuenta<string, double>& a,
				const Cuenta<string, double>& b) {
					return a.getLimiteRetiro() < b.getLimiteRetiro();
				};
			mergeSort(listas, 0, (int)listas.size() - 1, criterio);
			cout << "\n--- Cuentas Ordenadas ---\n";
			for (auto& l : listas) {
				l.mostrarInfo();
				cout << "------------------\n";
			}
			system("cls");
			pausar();
			break;
		}
		case 7: {
			cout << "\n--- Ordenar Cuentas ( Convirtiendo HASH TABLE - VECTOR ) ---" << endl;
			auto listas = tablaCuentas.toVector();
			if (listas.empty()) {
				cout << "No hay Cuentas para ordenar.\n";
				pausar();
				break;
			}
			////////////////////////////////////
			//ORDENAMIENTO CON QUICKSORT
			/////////////////////////////////////
			auto criterio = [](const Cuenta<string, double>& a,
				const Cuenta<string, double>& b) {
					return a.getAhorroObjetivo() < b.getAhorroObjetivo();
				};
			quicksort(listas, 0, (int)listas.size() - 1, criterio);
			cout << "\n--- Cuentas Ordenadas x Ahorro Objetivo---\n";
			for (auto& l : listas) {
				l.mostrarInfo();
				cout << "------------------\n";
			}
			system("cls");
			pausar();
			break;
		}
		case 8: {
			cout << "\n--- Data Set ---" << endl;
			cout << endl;
			vector<string> columnasCuentas = { "ID", "Tasa De Interes", "Limite Retiro" };
			vector<DataSetGenerator<Cuenta<string, double>>::Extractor> extrac = {
				[](const Cuenta<string,double>& c) { return c.getIdCuenta(); },
				[](const Cuenta<string,double>& c) { return to_string(c.getTasaInteres()); },
				[](const Cuenta<string,double>& c) { return to_string(c.getLimiteRetiro()); }
			};
			DataSetGenerator<Cuenta<string, double>>::listar(
				columnasCuentas,
				extrac,
				tablaCuentas
			);
			system("cls");
			pausar();
			break;
		};
		case 9:
		{
			cout << "\n--- Calcular Intereses ---" << endl;
			string numCuenta;
			int meses;
			cout << "Ingrese Numero de Cuenta: ";
			getline(cin, numCuenta);
			Cuenta<string, double>* cuenta = tablaCuentas.buscar(numCuenta);
			Servicios<string, double>* servicio = tablaDeServicios.buscar(numCuenta);
			if (cuenta == nullptr) {
				cout << "Error: No se encontro la cuenta con el numero proporcionado." << endl;
				pausar();
				break;
			}
			cout << "Calculando intereses, Ingrese Cantidad de meses: ";
			cin >> meses;
			double futuro = cuenta->interesRecursivo(meses);
			cout << "El monto futuro despues de " << meses << " meses es: $" << futuro << endl;
			system("cls");
			pausar();
			break;

		};
		case 10:
			cout << "Volviendo al menu principal..." << endl;
			break;
		default:
			break;
		}

	} while (opcion != 10);
	system("cls");

}

void menuSeguros(HashTable<Seguros<string, double>>& tablaSeguros,
	HashTable<Servicios<string, double>>& tablaDeServicios,
	HashTable<Cliente<string>>& tablaClientes) {
	int opcion;
	do {
		dibujarMenuSeguros();
		gotoxy(5, 10);
		cout << "\n=== GESTION DE SEGUROS ===" << endl;
		cout << "1. Crear Seguro" << endl;
		cout << "2. Mostrar Seguro" << endl;
		cout << "3. Ingresar Asegurados" << endl;
		cout << "4. Ordenar Seguros (MergeSort)" << endl;
		cout << "5. Ordenar Seguros (QuickSort)" << endl;
		cout << "6. Buscar Seguro por Numero de Cuenta" << endl;
		cout << "7. Crear Reclamo" << endl;
		cout << "8. Evaluar Cola de Reclamos" << endl;
		cout << "9. Mostrar Cola de Reclamos" << endl;
		cout << "10. Mostrar Pila de Reclamos" << endl;
		cout << "11. Generar Data Set" << endl;
		cout << "13. Crear Relacion entre Beneficiarios" << endl;
		cout << "14. Mostrar Red de Beneficiarios (Grafo)" << endl;
		cout << "12. Volver al Menu Principal" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		limpiarBuffer();
		system("cls");
		dibujarMenuSeguros();
		gotoxy(5, 10);

		switch (opcion)
		{
		case 1: {
			string dni, n_cuenta, t, f_a, t_seguro;
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
			try {
				Seguros<string, double>::setTablaServiciosGlobal(tablaDeServicios);
				Seguros<string, double> nuevoSeguro(n_cuenta, t, f_a, t_seguro, meses_cov, prima_mensual, monto_cov);
				tablaSeguros.insertar(nuevoSeguro.getNumCuenta(), nuevoSeguro);
				cout << "Seguro creado exitosamente." << endl;
				cout << "ID Cuenta: " << nuevoSeguro.getIdSeguro() << endl;
			}
			catch (const exception& e) {
				cout << "Error al crear seguro: " << e.what() << endl;
			}
			system("cls");
			pausar();
			break;
		}

		case 2: {
			cout << "\n--- Tabla de Cuentas ---" << endl;
			tablaSeguros.mostrar();
			system("cls");
			pausar();
			break;
		}

		case 3: {
			// MODIFICADO: Ahora usa crearBeneficiarioConGrafo
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
			try {
				// CAMBIO AQUÍ: Usa el nuevo método que integra el grafo
				seguro->crearBeneficiarioConGrafo(seguro, cliente, nombre, relacion, porcentaje);
			}
			catch (const exception& e) {
				cout << "Error al Ingresar Asegurado: " << e.what() << endl;
			}
			system("cls");
			pausar();
			break;
		}

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
			mergeSort(listas, 0, (int)listas.size() - 1, criterio);
			cout << "\n--- Cuentas Ordenadas ---\n";
			for (auto& l : listas) {
				l.mostrarInfo();
				cout << "------------------\n";
			}
			system("cls");
			pausar();
			break;
		}

		case 5: {
			cout << "\n--- Ordenar Seguros ( Convirtiendo HASH TABLE - VECTOR ) ---" << endl;
			auto listas = tablaSeguros.toVector();
			if (listas.empty()) {
				cout << "No hay Seguros para ordenar.\n";
				pausar();
				break;
			}
			auto criterio = [](const Seguros<string, double>& a,
				const Seguros<string, double>& b) {
					return a.getMesesCobertura() < b.getMesesCobertura();
				};
			quicksort(listas, 0, (int)listas.size() - 1, criterio);
			cout << "\n--- Cuentas Ordenadas x Meses De Cobertura---\n";
			for (auto& l : listas) {
				l.mostrarInfo();
				cout << "------------------\n";
			}
			system("cls");
			pausar();
			break;
		}

		case 6: {
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
			system("cls");
			pausar();
			break;
		}

		case 7: {
			cout << "\n--- Crear Reclamo ---" << endl;
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
			system("cls");
			pausar();
			break;
		}

		case 8: {
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
			system("cls");
			pausar();
			break;
		}

		case 9: {
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
			system("cls");
			pausar();
			break;
		}

		case 10: {
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
			system("cls");
			pausar();
			break;
		}

		case 11: {
			cout << "\n--- Data Set ---" << endl;
			vector<string> columnas = { "ID", "Tipo Seguro", "Monto Covertura" };
			vector<DataSetGenerator<Seguros<string, double>>::Extractor> extractores = {
				[](const Seguros<string,double>& s) { return s.getIdSeguro(); },
				[](const Seguros<string,double>& s) { return s.getTipoSeguro(); },
				[](const Seguros<string,double>& s) { return to_string(s.getMontoCobertura()); }
			};
			DataSetGenerator<Seguros<string, double>>::listar(
				columnas,
				extractores,
				tablaSeguros
			);
			system("cls");
			pausar();
			break;
		}

			   // ========== NUEVOS CASOS PARA EL GRAFO ==========

		case 13: {
			// Crear relación entre beneficiarios
			cout << "\n--- Crear Relacion entre Beneficiarios ---" << endl;
			string num_cuenta, dni;
			cout << "Ingrese Numero del Seguro: ";
			getline(cin, num_cuenta);
			Seguros<string, double>* seguro = tablaSeguros.buscar(num_cuenta);
			if (seguro == nullptr) {
				cout << "ERROR: Seguro no encontrado.\n";
				break;
			}
			cout << "DNI del Cliente: ";
			getline(cin, dni);
			Cliente<string>* cliente = tablaClientes.buscar(dni);
			if (cliente == nullptr) {
				cout << "ERROR: Cliente no encontrado.\n";
				break;
			}

			string nombre_origen, nombre_destino, tipo_relacion;
			double peso;

			cout << "\n--- Beneficiario Origen ---" << endl;
			cout << "Nombre del beneficiario origen: ";
			getline(cin, nombre_origen);

			cout << "\n--- Beneficiario Destino ---" << endl;
			cout << "Nombre del beneficiario destino: ";
			getline(cin, nombre_destino);

			cout << "\nPeso de la relacion (porcentaje transferible): ";
			cin >> peso;
			limpiarBuffer();

			cout << "Tipo de relacion (SUSTITUTO/DEPENDIENTE/FAMILIAR): ";
			getline(cin, tipo_relacion);

			try {
				seguro->crearRelacionBeneficiarios(
					nombre_origen, cliente->getID(),
					nombre_destino, cliente->getID(),
					peso, tipo_relacion
				);
			}
			catch (const exception& e) {
				cout << "Error: " << e.what() << endl;
			}
			system("cls");
			pausar();
			break;
		}

		case 14: {
			// Mostrar red completa de beneficiarios
			cout << "\n--- Red de Beneficiarios (Grafo) ---" << endl;
			string num_cuenta;
			cout << "Ingrese Numero del Seguro: ";
			getline(cin, num_cuenta);
			Seguros<string, double>* seguro = tablaSeguros.buscar(num_cuenta);
			if (seguro == nullptr) {
				cout << "ERROR: Seguro no encontrado.\n";
				break;
			}
			seguro->mostrarRedBeneficiarios();
			system("cls");
			pausar();
			break;
		}

		case 12:
			cout << "Volviendo al menu principal..." << endl;
			break;

		default:
			cout << "Opcion invalida. Intente de nuevo." << endl;
			break;
		}

	} while (opcion != 12);
	system("cls");
}
/*void menuSeguros(HashTable<Seguros<string, double>>& tablaSeguros, HashTable<Servicios<string, double>>& tablaDeServicios, HashTable<Cliente<string>>& tablaClientes) {
	int opcion;
	do {
		cout << "\n=== GESTION DE SEGUROS ===" << endl;
		cout << "1. Crear Seguro" << endl;
		cout << "2. Mostrar Seguro" << endl; //Por Cliente
		cout << "3. Ingresar Asegurados" << endl;
		cout << "4. Ordenar Seguros (MergeSort)" << endl;
		cout << "5. Ordenar Seguros (QuickSort)" << endl;
		cout << "6. Buscar Seguro por Numero de Cuenta" << endl;
		cout << "7. Crear Reclamo " << endl;
		cout << "8. Evaluar Cola de Reclamos " << endl;
		cout << "9. Mostrar Cola de Reclamos " << endl;
		cout << "10. Mostrar PIla de Reclamos " << endl;
		cout << "11. Generar Data Set " << endl;
		cout << "12. Volver al Menu Principal" << endl;
		cin >> opcion;
		limpiarBuffer();

		switch (opcion)
		{
		case 1: {
			string dni, n_cuenta, t, f_a, t_seguro;
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
			try {
				Seguros<string, double>::setTablaServiciosGlobal(tablaDeServicios);
				Seguros<string, double> nuevoSeguro(n_cuenta, t, f_a, t_seguro, meses_cov, prima_mensual, monto_cov);
				tablaSeguros.insertar(nuevoSeguro.getNumCuenta(), nuevoSeguro);
				cout << "Seguro creado exitosamente." << endl;
				cout << "ID Cuenta: " << nuevoSeguro.getIdSeguro() << endl;

			}
			catch (const exception& e) {
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
			////////////////////////////////////
			//ORDENAMIENTO CON MERGESORT
			////////////////////////////////////
			auto criterio = [](const Seguros<string, double>& a,
				const Seguros<string, double>& b) {
					return a.getIdSeguro() < b.getIdSeguro();
				};
			mergeSort(listas, 0, (int)listas.size() - 1, criterio);
			cout << "\n--- Cuentas Ordenadas ---\n";
			for (auto& l : listas) {
				l.mostrarInfo();
				cout << "------------------\n";
			}
			pausar();
			break;
		};
		case 5: {
			cout << "\n--- Ordenar Seguros ( Convirtiendo HASH TABLE - VECTOR ) ---" << endl;
			auto listas = tablaSeguros.toVector();
			if (listas.empty()) {
				cout << "No hay Seguros para ordenar.\n";
				pausar();
				break;
			}
			////////////////////////////////////
			//ORDENAMIENTO CON QUICKSORT
			/////////////////////////////////////
			auto criterio = [](const Seguros<string, double>& a,
				const Seguros<string, double>& b) {
					return a.getMesesCobertura() < b.getMesesCobertura();
				};
			quicksort(listas, 0, (int)listas.size() - 1, criterio);
			cout << "\n--- Cuentas Ordenadas x Meses De Cobertura---\n";
			for (auto& l : listas) {
				l.mostrarInfo();
				cout << "------------------\n";
			}

			pausar();
			break;

		};
		case 6: {
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
		case 7: {
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
		case 8: {
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
		case 9: {
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
		case 10: {
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
		case 11: {
			cout << "\n--- Data Set ---" << endl;
			cout << endl;
			vector<string> columnas = { "ID", "Tipo Seguro", "Monto Covertura" };
			vector<DataSetGenerator<Seguros<string, double>>::Extractor> extractores = {
				[](const Seguros<string,double>& s) { return s.getIdSeguro(); },
				[](const Seguros<string,double>& s) { return s.getTipoSeguro(); },
				[](const Seguros<string,double>& s) { return to_string(s.getMontoCobertura()); }
			};
			DataSetGenerator<Seguros<string, double>>::listar(
				columnas,
				extractores,
				tablaSeguros   // <- tu hash table ya existente
			);


			pausar();
			break;
		};

		case 12:
			cout << "Volviendo al menu principal..." << endl;
			break;
		default:
			break;
		}

	} while (opcion != 12);
};
*/
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
				// Convertir HashTables a vectores para usar tus m�todos actuales
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
			cout << "Opci�n no v�lida." << endl;
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

//Menu cerditos//
using T1 = string;
using T2 = double;
ListaEnlazada<CreditoPersonal<T1, T2>> listaCP;
ListaEnlazada<CreditoVivienda<T1, T2>> listaCV;
ListaEnlazada<CreditoEmpresarial<T1, T2>> listaCE;
void crearCreditoPersonal() {
	T1 num_cuenta, titular, fecha_apertura, destino;
	T2 monto_prestamo, tasa_interes, seguro_desgravamen_val;
	int plazo_meses;
	int opcion_seguro;

	cout << "\n--- CREAR CREDITO PERSONAL ---" << endl;

	// Lectura de datos heredados de Servicios
	cout << "Numero de Cuenta (Servicio): "; cin >> num_cuenta; limpiarBuffer();
	cout << "Nombre del Titular: "; getline(cin, titular);
	cout << "Fecha de Apertura (DD/MM/AAAA): "; cin >> fecha_apertura; limpiarBuffer();

	// Lectura de datos de Credito base
	cout << "Monto del Prestamo: $"; cin >> monto_prestamo; limpiarBuffer();
	cout << "Plazo en meses: "; cin >> plazo_meses; limpiarBuffer();
	cout << "Tasa de Interes (ej. 0.15 para 15%): "; cin >> tasa_interes; limpiarBuffer();

	// Lectura de datos específicos de CreditoPersonal
	cout << "Destino del Credito: "; getline(cin, destino);
	cout << "¿Incluye Seguro de Desgravamen? (1=Si, 0=No): "; cin >> opcion_seguro; limpiarBuffer();
	seguro_desgravamen_val = (opcion_seguro == 1) ? 1.0 : 0.0;

	CreditoPersonal<T1, T2> nuevoCP(
		num_cuenta, titular, fecha_apertura, monto_prestamo, plazo_meses,
		tasa_interes, destino, seguro_desgravamen_val
	);

	// Agregar el objeto a la lista global
	listaCP.agregarFinal(nuevoCP);
	cout << "\n✅ Credito Personal agregado a la Lista Enlazada." << endl;
}

void crearCreditoVivienda() {
	T1 num_cuenta, titular, fecha_apertura, direccion;
	T2 monto_prestamo, tasa_interes, valor_propiedad;
	int plazo_meses;

	cout << "\n--- CREAR CREDITO MI VIVIENDA ---" << endl;

	// Lectura de datos heredados y Credito base
	cout << "Numero de Cuenta (Servicio): "; cin >> num_cuenta; limpiarBuffer();
	cout << "Nombre del Titular: "; getline(cin, titular);
	cout << "Fecha de Apertura (DD/MM/AAAA): "; cin >> fecha_apertura; limpiarBuffer();
	cout << "Monto del Prestamo: $"; cin >> monto_prestamo; limpiarBuffer();
	cout << "Plazo en meses: "; cin >> plazo_meses; limpiarBuffer();
	cout << "Tasa de Interes (ej. 0.08 para 8%): "; cin >> tasa_interes; limpiarBuffer();

	// Lectura de datos específicos de CreditoVivienda
	cout << "Direccion de la Propiedad: "; getline(cin, direccion);
	cout << "Valor de la Propiedad: $"; cin >> valor_propiedad; limpiarBuffer();

	CreditoVivienda<T1, T2> nuevoCV(
		num_cuenta, titular, fecha_apertura, monto_prestamo, plazo_meses,
		tasa_interes, direccion, valor_propiedad
	);

	// Agregar el objeto a la lista global
	listaCV.agregarFinal(nuevoCV);
	cout << "\n✅ Credito Vivienda agregado a la Lista Enlazada." << endl;
}

void crearCreditoEmpresarial() {
	T1 num_cuenta, titular, fecha_apertura, nombre_empresa, ruc;
	T2 monto_prestamo, tasa_interes, linea_credito;
	int plazo_meses;

	cout << "\n--- CREAR CREDITO EMPRESARIAL ---" << endl;

	// Lectura de datos heredados y Credito base
	cout << "Numero de Cuenta (Servicio): "; cin >> num_cuenta; limpiarBuffer();
	cout << "Nombre del Titular: "; getline(cin, titular);
	cout << "Fecha de Apertura (DD/MM/AAAA): "; cin >> fecha_apertura; limpiarBuffer();
	cout << "Monto del Prestamo: $"; cin >> monto_prestamo; limpiarBuffer();
	cout << "Plazo en meses: "; cin >> plazo_meses; limpiarBuffer();
	cout << "Tasa de Interes (ej. 0.12 para 12%): "; cin >> tasa_interes; limpiarBuffer();

	// Lectura de datos específicos de CreditoEmpresarial
	cout << "Nombre de la Empresa: "; getline(cin, nombre_empresa);
	cout << "RUC: "; cin >> ruc; limpiarBuffer();
	cout << "Linea de Credito Maxima: $"; cin >> linea_credito; limpiarBuffer();

	CreditoEmpresarial<T1, T2> nuevoCE(
		num_cuenta, titular, fecha_apertura, monto_prestamo, plazo_meses,
		tasa_interes, nombre_empresa, ruc, linea_credito
	);

	// Agregar el objeto a la lista global
	listaCE.agregarFinal(nuevoCE);
	cout << "\n✅ Credito Empresarial agregado a la Lista Enlazada." << endl;
}

// ----------------------------------------------------
// FUNCIÓN PRINCIPAL DE GESTIÓN DE CRÉDITOS
// ----------------------------------------------------

void menuCreditos(HashTable<Cliente<string>>& tablaClientes, HashTable<Credito<string, double>>& tablaCreditos) {
	int opcion;
	string dniCliente;
	Cliente<string>* clienteVerificado = nullptr;

	do {
		// Limpiar y dibujar el menú al inicio de cada iteración
		system("cls");
		dibujarMenuCreditos();

		gotoxy(5, 9);
		cout << "   GESTION DE CREDITOS " << endl;
		gotoxy(2, 11);
		cout << "Instrucciones: Aqui podras solicitar un credito de 3 tipos diferentes," << endl;
		gotoxy(2, 12);
		cout << " asi como listarlos para poder estar informado sobre tus creditos" << endl;
		gotoxy(2, 15);
		cout << "1. Solicitar Crédito Personal" << endl;
		gotoxy(2, 18);
		cout << "2. Solicitar Crédito Vivienda" << endl;
		gotoxy(2, 21);
		cout << "3. Solicitar Crédito Empresarial" << endl;
		gotoxy(2, 24);
		cout << "4. Listar Créditos Activos" << endl;
		gotoxy(2, 26);
		cout << "0. Volver al Menu Principal" << endl;
		gotoxy(35, 17);
		cout << "Ingrese opcion: ";

		if (!(cin >> opcion)) {
			opcion = -1;
			cin.clear();
		}
		cin.ignore(); // Limpiar buffer después de leer número

		// Limpiar y redibujar después de la selección
		system("cls");
		dibujarMenuCreditos();
		gotoxy(2, 15); // Posicionar para la siguiente información

		if (opcion >= 1 && opcion <= 3) {
			// ===============================================
			// 🚨 PASO 1: VALIDACIÓN CRÍTICA DEL CLIENTE
			// ===============================================
			cout << "---------------------------------------" << endl;
			cout << "PASO 1: VERIFICACIÓN DE CLIENTE" << endl;
			cout << "Ingrese el DNI del cliente solicitante: ";
			cin >> dniCliente;

			// Limpiar y redibujar después de ingresar DNI
			system("cls");
			dibujarMenuCreditos();
			gotoxy(2, 15);

			// Buscar en la tabla de clientes 
			clienteVerificado = tablaClientes.buscarRef(dniCliente);

			if (clienteVerificado == nullptr) {
				cout << "\n❌ ERROR: El cliente con DNI " << dniCliente << " NO está registrado." << endl;
				cout << "Debe registrar al cliente primero (Opción 1 del menú principal)." << endl;
				pausar();
				continue; // Volver al menú de créditos
			}

			cout << "\n✅ Cliente verificado. Datos del titular: " << endl;
			clienteVerificado->mostrarInfo();
			cout << "---------------------------------------" << endl;

			// Datos comunes del crédito
			double monto, tasa;
			int plazo;
			string titular = clienteVerificado->getNombre() + " " + clienteVerificado->getApellido();
			string numCuentaAsociada = dniCliente;

			cout << "PASO 2: INGRESO DE DATOS DEL CRÉDITO" << endl;
			cout << "Monto del Préstamo (USD): ";
			if (!(cin >> monto)) {
				monto = 0;
				cin.clear();
			}
			cin.ignore();

			cout << "Plazo (meses): ";
			if (!(cin >> plazo)) {
				plazo = 0;
				cin.clear();
			}
			cin.ignore();

			cout << "Tasa de Interés Anual (Ej: 0.10 para 10%): ";
			if (!(cin >> tasa)) {
				tasa = 0;
				cin.clear();
			}
			cin.ignore();

			// --- 🎯 FECHA SOLICITADA AL USUARIO ---
			string fechaApertura;
			cout << "Fecha de Apertura del Crédito (YYYY-MM-DD): ";
			getline(cin, fechaApertura);

			// Limpiar y redibujar antes de mostrar resultado
			system("cls");
			dibujarMenuCreditos();
			gotoxy(2, 15);

			// ===============================================
			// PASO 3: SOLICITUD DE CRÉDITO ESPECÍFICO
			// ===============================================
			if (opcion == 1) { // Personal
				string destino;
				int tieneSeguro;
				cout << "Destino del Crédito (Ej: Viaje, Estudios): ";
				getline(cin, destino);
				cout << "¿Desea Seguro de Desgravamen? (1=Si, 0=No): ";
				if (!(cin >> tieneSeguro)) {
					tieneSeguro = 0;
					cin.clear();
				}
				cin.ignore();

				CreditoPersonal<string, double>* nuevoCredito = new CreditoPersonal<string, double>(
					numCuentaAsociada, titular, fechaApertura,
					monto, plazo, tasa,
					destino, (double)tieneSeguro
				);
				tablaCreditos.insertar(nuevoCredito->getIdServicio(), *nuevoCredito);
				string id_gen = nuevoCredito->getIdServicio();
				delete nuevoCredito;

				cout << "\n🟢 Crédito Personal APROBADO y REGISTRADO con ID: " << id_gen << endl;

			}
			else if (opcion == 2) { // Vivienda
				string direccion;
				double valorPropiedad;
				cout << "Dirección de la Propiedad: ";
				getline(cin, direccion);
				cout << "Valor Total de la Propiedad (USD): ";
				if (!(cin >> valorPropiedad)) {
					valorPropiedad = 0;
					cin.clear();
				}
				cin.ignore();

				CreditoVivienda<string, double>* nuevoCredito = new CreditoVivienda<string, double>(
					numCuentaAsociada, titular, fechaApertura,
					monto, plazo, tasa,
					direccion, valorPropiedad
				);
				tablaCreditos.insertar(nuevoCredito->getIdServicio(), *nuevoCredito);
				string id_gen = nuevoCredito->getIdServicio();
				delete nuevoCredito;
				cout << "\n🟢 Crédito Hipotecario APROBADO y REGISTRADO con ID: " << id_gen << endl;

			}
			else if (opcion == 3) { // Empresarial
				string nombreEmpresa, ruc;
				double lineaCredito;
				cout << "Nombre de la Empresa: ";
				getline(cin, nombreEmpresa);
				cout << "RUC/Identificador Tributario: ";
				getline(cin, ruc);
				cout << "Línea de Crédito Máxima Aprobada (USD): ";
				if (!(cin >> lineaCredito)) {
					lineaCredito = 0;
					cin.clear();
				}
				cin.ignore();

				CreditoEmpresarial<string, double>* nuevoCredito = new CreditoEmpresarial<string, double>(
					numCuentaAsociada, titular, fechaApertura,
					monto, plazo, tasa,
					nombreEmpresa, ruc, lineaCredito
				);
				tablaCreditos.insertar(nuevoCredito->getIdServicio(), *nuevoCredito);
				string id_gen = nuevoCredito->getIdServicio();
				delete nuevoCredito;
				cout << "\n🟢 Crédito Empresarial APROBADO y REGISTRADO con ID: " << id_gen << endl;
			}

		}
		else if (opcion == 4) {
			cout << "\n===== LISTADO DE CRÉDITOS ACTIVOS (" << tablaCreditos.getNumElementos() << ") =====" << endl;
			if (tablaCreditos.getNumElementos() == 0) {
				cout << "No hay créditos registrados." << endl;
			}
			else {
				tablaCreditos.forEach([](const Credito<string, double>& c) {
					c.mostrarInfo();
					cout << "-----------------------------------" << endl;
					});
			}
		}
		else if (opcion != 0) {
			cout << "\n❌ Opción no válida. Intente de nuevo." << endl;
		}

		if (opcion != 0) {
			pausar();
		}

	} while (opcion != 0);

	// Limpiar pantalla al salir del menú
	system("cls");
}

// ===========================================
// MENU DE TARJETAS
// ===========================================
void menuTarjetas(
	HashTable<TarjetaCredito<string, double>>& tablaTarjetasCredito,
	HashTable<TarjetaDebito<string, double>>& tablaTarjetasDebito,
	HashTable<Servicios<string, double>>& tablaDeServicios
) {
	int opcion;
	do {
		// ========== FONDO ROJO ACTIVADO ==========
		fondoRojo();
		// =========================================
		
		cout << "\n=== GESTION DE TARJETAS ===" << endl;
		cout << "1. Crear Tarjeta de Credito" << endl;
		cout << "2. Crear Tarjeta de Debito" << endl;
		cout << "3. Mostrar Todas las Tarjetas de Credito" << endl;
		cout << "4. Mostrar Todas las Tarjetas de Debito" << endl;
		cout << "5. Buscar Tarjeta por Numero" << endl;
		cout << "6. Usar Credito (Tarjeta Credito)" << endl;
		cout << "7. Pagar Credito (Tarjeta Credito)" << endl;
		cout << "8. Retirar Dinero (Tarjeta Debito)" << endl;
		cout << "9. Depositar Dinero (Tarjeta Debito)" << endl;
		cout << "10. Bloquear/Desbloquear Tarjeta" << endl;
		cout << "11. Ver Dias hasta Vencimiento" << endl;
		cout << "12. Proyectar Deuda (Tarjeta Credito)" << endl;
		cout << "13. Mostrar Estadisticas de Tarjeta" << endl;
		cout << "14. Ordenar Tarjetas de Credito" << endl;
		cout << "15. Listar con DataSetGenerator" << endl;
		cout << "16. Insertar Tarjeta en Arbol 1" << endl;
		cout << "17. Insertar Tarjeta en Arbol 2" << endl;
		cout << "18. Buscar en Arbol 1" << endl;
		cout << "19. Mostrar Arbol 1 Ordenado" << endl;
		cout << "20. Mostrar Arbol 2 Ordenado" << endl;
		cout << "21. Mostrar Estructura Arbol 1" << endl;
		cout << "22. Mostrar Estructura Arbol 2" << endl;
		cout << "23. Comparar Busqueda en 2 Arboles" << endl;
		cout << "24. Transferir Credito" << endl;
		cout << "25. Transferir Dinero" << endl;
		cout << "26. Mostrar Mis Transferencias" << endl;
		cout << "27. Mostrar Red Completa" << endl;
		cout << "28. Recorrido BFS" << endl;
		cout << "29. Recorrido DFS" << endl;
		cout << "30. Verificar Camino entre Tarjetas" << endl;
		cout << "31. Analizar Red de Transferencias" << endl;
		cout << "32. Analizar Patrones de Retiro" << endl;
		cout << "\n========================================" << endl;
		cout << "0. Volver al Menu Principal" << endl;
		
		// ========== RESETEAR COLOR PARA INPUT ==========
		cout << "\033[0m";
		// ================================================
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		limpiarBuffer();

		switch (opcion) {
		case 1: { // Crear Tarjeta de Crédito
			fondoRojo();
			string numCuenta, titular, fecha, numTarjeta, fechaEmision, fechaVenc, cvv;
			double lineaCredito, tasaInteres;

			cout << "\n--- CREAR TARJETA DE CREDITO ---" << endl;
			cout << "Numero de Cuenta: ";
			getline(cin, numCuenta);
			cout << "Titular: ";
			getline(cin, titular);
			cout << "Fecha apertura (dd/mm/yyyy): ";
			getline(cin, fecha);
			cout << "Numero de Tarjeta (16 digitos): ";
			getline(cin, numTarjeta);
			cout << "Fecha Emision (dd/mm/yyyy): ";
			getline(cin, fechaEmision);
			cout << "Fecha Vencimiento (dd/mm/yyyy): ";
			getline(cin, fechaVenc);
			cout << "CVV (3 digitos): ";
			getline(cin, cvv);
			cout << "Linea de Credito: $";
			cin >> lineaCredito;
			cout << "Tasa de Interes Mensual (%): ";
			cin >> tasaInteres;
			limpiarBuffer();

			try {
				TarjetaCredito<string, double> nuevaTarjeta(
					numCuenta, titular, fecha, numTarjeta,
					fechaEmision, fechaVenc, cvv,
					lineaCredito, tasaInteres
				);

				tablaTarjetasCredito.insertar(numTarjeta, nuevaTarjeta);

				cout << "\n✓ Tarjeta de credito creada exitosamente!" << endl;
				cout << "ID: " << nuevaTarjeta.getIdTarjeta() << endl;
				nuevaTarjeta.mostrarInfo();
			}
			catch (const exception& e) {
				cout << "Error: " << e.what() << endl;
			}
			pausar();
			break;
		}

		case 2: { // Crear Tarjeta de Débito
			fondoRojo();
			string numCuenta, titular, fecha, numTarjeta, fechaEmision, fechaVenc, cvv;
			double limiteDiario;

			cout << "\n--- CREAR TARJETA DE DEBITO ---" << endl;
			cout << "Numero de Cuenta: ";
			getline(cin, numCuenta);
			cout << "Titular: ";
			getline(cin, titular);
			cout << "Fecha apertura (dd/mm/yyyy): ";
			getline(cin, fecha);
			cout << "Numero de Tarjeta (16 digitos): ";
			getline(cin, numTarjeta);
			cout << "Fecha Emision (dd/mm/yyyy): ";
			getline(cin, fechaEmision);
			cout << "Fecha Vencimiento (dd/mm/yyyy): ";
			getline(cin, fechaVenc);
			cout << "CVV (3 digitos): ";
			getline(cin, cvv);
			cout << "Limite Diario de Retiro: $";
			cin >> limiteDiario;
			limpiarBuffer();

			try {
				TarjetaDebito<string, double> nuevaTarjeta(
					numCuenta, titular, fecha, numTarjeta,
					fechaEmision, fechaVenc, cvv,
					limiteDiario
				);

				tablaTarjetasDebito.insertar(numTarjeta, nuevaTarjeta);

				cout << "\n✓ Tarjeta de debito creada exitosamente!" << endl;
				cout << "ID: " << nuevaTarjeta.getIdTarjeta() << endl;
				nuevaTarjeta.mostrarInfo();
			}
			catch (const exception& e) {
				cout << "Error: " << e.what() << endl;
			}
			pausar();
			break;
		}

		case 3: { // Mostrar todas las tarjetas de crédito
			fondoRojo();
			cout << "\n--- TARJETAS DE CREDITO ---" << endl;
			tablaTarjetasCredito.mostrar();
			pausar();
			break;
		}

		case 4: { // Mostrar todas las tarjetas de débito
			fondoRojo();
			cout << "\n--- TARJETAS DE DEBITO ---" << endl;
			tablaTarjetasDebito.mostrar();
			pausar();
			break;
		}

		case 5: { // Buscar tarjeta por número
			fondoRojo();
			string numTarjeta;
			int tipoTarjeta;

			cout << "\n--- BUSCAR TARJETA ---" << endl;
			cout << "Tipo de tarjeta: 1) Credito  2) Debito: ";
			cin >> tipoTarjeta;
			limpiarBuffer();
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);

			if (tipoTarjeta == 1) {
				TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) {
					cout << "\nTarjeta encontrada:" << endl;
					tarjeta->mostrarInfo();
				}
				else {
					cout << "Tarjeta no encontrada." << endl;
				}
			}
			else {
				TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) {
					cout << "\nTarjeta encontrada:" << endl;
					tarjeta->mostrarInfo();
				}
				else {
					cout << "Tarjeta no encontrada." << endl;
				}
			}
			pausar();
			break;
		}

		case 6: { // Usar crédito
			fondoRojo();
			string numTarjeta;
			double monto;

			cout << "\n--- USAR CREDITO ---" << endl;
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);

			TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
			if (tarjeta != nullptr) {
				cout << "Credito disponible: $" << tarjeta->getCreditoDisponible() << endl;
				cout << "Monto a usar: $";
				cin >> monto;
				limpiarBuffer();

				tarjeta->usarCredito(monto);
			}
			else {
				cout << "✗ Tarjeta no encontrada." << endl;
			}
			pausar();
			break;
		}

		case 7: { // Pagar crédito
			fondoRojo();
			string numTarjeta;
			double monto;

			cout << "\n--- PAGAR CREDITO ---" << endl;
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);

			TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
			if (tarjeta != nullptr) {
				cout << "Deuda actual: $" << tarjeta->getCreditoUtilizado() << endl;
				cout << "Monto a pagar: $";
				cin >> monto;
				limpiarBuffer();

				tarjeta->pagarCredito(monto);
			}
			else {
				cout << "✗ Tarjeta no encontrada." << endl;
			}
			pausar();
			break;
		}

		case 8: { // Retirar dinero
			fondoRojo();
			string numTarjeta;
			double monto;

			cout << "\n--- RETIRAR DINERO ---" << endl;
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);

			TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
			if (tarjeta != nullptr) {
				tarjeta->consultarSaldoDetallado();
				cout << "\nMonto a retirar: $";
				cin >> monto;
				limpiarBuffer();

				tarjeta->retirar(monto);
			}
			else {
				cout << "✗ Tarjeta no encontrada." << endl;
			}
			pausar();
			break;
		}

		case 9: { // Depositar dinero
			fondoRojo();
			string numTarjeta;
			double monto;

			cout << "\n--- DEPOSITAR DINERO ---" << endl;
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);

			TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
			if (tarjeta != nullptr) {
				cout << "Monto a depositar: $";
				cin >> monto;
				limpiarBuffer();

				tarjeta->depositar(monto);
			}
			else {
				cout << "✗ Tarjeta no encontrada." << endl;
			}
			pausar();
			break;
		}

		case 10: { // Bloquear/Desbloquear
			fondoRojo();
			string numTarjeta;
			int tipoTarjeta, accion;

			cout << "\n--- BLOQUEAR/DESBLOQUEAR TARJETA ---" << endl;
			cout << "Tipo: 1) Credito  2) Debito: ";
			cin >> tipoTarjeta;
			limpiarBuffer();
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);
			cout << "Accion: 1) Bloquear  2) Desbloquear: ";
			cin >> accion;
			limpiarBuffer();

			if (tipoTarjeta == 1) {
				TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) {
					if (accion == 1) tarjeta->bloquearTarjeta();
					else tarjeta->desbloquearTarjeta();
				}
				else {
					cout << "✗ Tarjeta no encontrada." << endl;
				}
			}
			else {
				TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) {
					if (accion == 1) tarjeta->bloquearTarjeta();
					else tarjeta->desbloquearTarjeta();
				}
				else {
					cout << "✗ Tarjeta no encontrada." << endl;
				}
			}
			pausar();
			break;
		}

		case 11: { // Ver días hasta vencimiento
			fondoRojo();
			string numTarjeta, fechaActual;
			int tipoTarjeta;

			cout << "\n--- DIAS HASTA VENCIMIENTO ---" << endl;
			cout << "Tipo: 1) Credito  2) Debito: ";
			cin >> tipoTarjeta;
			limpiarBuffer();
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);
			cout << "Fecha actual (dd/mm/yyyy): ";
			getline(cin, fechaActual);

			if (tipoTarjeta == 1) {
				TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) {
					int dias = tarjeta->diasHastaVencimiento(fechaActual);
					if (dias >= 0) {
						cout << "Dias hasta vencimiento: " << dias << " dias" << endl;
					}
				}
				else {
					cout << "✗ Tarjeta no encontrada." << endl;
				}
			}
			else {
				TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) {
					int dias = tarjeta->diasHastaVencimiento(fechaActual);
					if (dias >= 0) {
						cout << "Dias hasta vencimiento: " << dias << " dias" << endl;
					}
				}
				else {
					cout << "✗ Tarjeta no encontrada." << endl;
				}
			}
			pausar();
			break;
		}

		case 12: { // Proyectar deuda
			fondoRojo();
			string numTarjeta;
			int meses;

			cout << "\n--- PROYECTAR DEUDA ---" << endl;
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);

			TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
			if (tarjeta != nullptr) {
				cout << "Numero de meses a proyectar: ";
				cin >> meses;
				limpiarBuffer();

				tarjeta->proyectarDeuda(meses);
			}
			else {
				cout << "✗ Tarjeta no encontrada." << endl;
			}
			pausar();
			break;
		}

		case 13: { // Mostrar estadísticas
			fondoRojo();
			string numTarjeta;
			int tipoTarjeta;

			cout << "\n--- ESTADISTICAS ---" << endl;
			cout << "Tipo: 1) Credito  2) Debito: ";
			cin >> tipoTarjeta;
			limpiarBuffer();
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);

			if (tipoTarjeta == 1) {
				TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) {
					tarjeta->mostrarEstadisticas();
				}
				else {
					cout << "✗ Tarjeta no encontrada." << endl;
				}
			}
			else {
				TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) {
					tarjeta->mostrarEstadisticas();
				}
				else {
					cout << "✗ Tarjeta no encontrada." << endl;
				}
			}
			pausar();
			break;
		}

		case 14: { // Ordenar tarjetas
			fondoRojo();
			cout << "\n--- ORDENAR TARJETAS DE CREDITO ---" << endl;
			auto listaTarjetas = tablaTarjetasCredito.toVector();

			if (listaTarjetas.empty()) {
				cout << "No hay tarjetas para ordenar." << endl;
				pausar();
				break;
			}

			cout << "Ordenar por:" << endl;
			cout << "1. Linea de credito (mayor a menor)" << endl;
			cout << "2. Credito utilizado (mayor a menor)" << endl;
			cout << "3. Credito disponible (mayor a menor)" << endl;
			int criterio;
			cin >> criterio;
			limpiarBuffer();

			switch (criterio) {
			case 1:
				quicksort(listaTarjetas, 0, listaTarjetas.size() - 1,
					[](const TarjetaCredito<string, double>& a, const TarjetaCredito<string, double>& b) {
						return a.getLineaCredito() > b.getLineaCredito();
					});
				break;
			case 2:
				quicksort(listaTarjetas, 0, listaTarjetas.size() - 1,
					[](const TarjetaCredito<string, double>& a, const TarjetaCredito<string, double>& b) {
						return a.getCreditoUtilizado() > b.getCreditoUtilizado();
					});
				break;
			case 3:
				quicksort(listaTarjetas, 0, listaTarjetas.size() - 1,
					[](const TarjetaCredito<string, double>& a, const TarjetaCredito<string, double>& b) {
						return a.getCreditoDisponible() > b.getCreditoDisponible();
					});
				break;
			}

			cout << "\n✓ Tarjetas ordenadas:" << endl;
			for (const auto& tarjeta : listaTarjetas) {
				tarjeta.mostrarInfo();
				cout << "---" << endl;
			}
			pausar();
			break;
		}

		case 15: { // DataSetGenerator
			fondoRojo();
			cout << "\n--- LISTAR CON DATASET GENERATOR ---" << endl;
			cout << "1. Listar Tarjetas de Credito" << endl;
			cout << "2. Listar Tarjetas de Debito" << endl;
			int tipo;
			cin >> tipo;
			limpiarBuffer();

			if (tipo == 1) {
				vector<string> columnas = {
					"Numero", "Estado", "Linea", "Usado", "Disponible", "Tasa%"
				};

				vector<function<string(const TarjetaCredito<string, double>&)>> extractores = {
					[](const TarjetaCredito<string, double>& t) { return t.getNumTarjeta(); },
					[](const TarjetaCredito<string, double>& t) { return t.getEstado(); },
					[](const TarjetaCredito<string, double>& t) { return to_string(t.getLineaCredito()); },
					[](const TarjetaCredito<string, double>& t) { return to_string(t.getCreditoUtilizado()); },
					[](const TarjetaCredito<string, double>& t) { return to_string(t.getCreditoDisponible()); },
					[](const TarjetaCredito<string, double>& t) { return to_string(t.getTasaInteresMensual()); }
				};

				DataSetGenerator<TarjetaCredito<string, double>>::listar(
					columnas,
					extractores,
					tablaTarjetasCredito
				);
			}
			else {
				vector<string> columnas = {
					"Numero", "Estado", "Limite Diario", "Retirado Hoy", "Disponible Hoy"
				};

				vector<function<string(const TarjetaDebito<string, double>&)>> extractores = {
					[](const TarjetaDebito<string, double>& t) { return t.getNumTarjeta(); },
					[](const TarjetaDebito<string, double>& t) { return t.getEstado(); },
					[](const TarjetaDebito<string, double>& t) { return to_string(t.getLimiteDiarioRetiro()); },
					[](const TarjetaDebito<string, double>& t) { return to_string(t.getRetiradoHoy()); },
					[](const TarjetaDebito<string, double>& t) { return to_string(t.getLimiteDisponibleHoy()); }
				};

				DataSetGenerator<TarjetaDebito<string, double>>::listar(
					columnas,
					extractores,
					tablaTarjetasDebito
				);
			}
			pausar();
			break;
		}

		case 16: { // Insertar en Arbol 1
			fondoRojo();
			cout << "\n=== INSERTAR EN ARBOL 1 (POR NUMERO) ===" << endl;
			cout << "1. Tarjeta de Credito\n2. Tarjeta de Debito" << endl;
			int tipo;
			cout << "Tipo: ";
			cin >> tipo;
			limpiarBuffer();
			string numTarjeta;
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);

			if (tipo == 1) {
				TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) tarjeta->insertarEnArbolPorNumero();
				else cout << "Tarjeta no encontrada" << endl;
			}
			else {
				TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) tarjeta->insertarEnArbolPorNumero();
				else cout << "Tarjeta no encontrada" << endl;
			}
			pausar();
			break;
		}

		case 17: { // Insertar en Arbol 2
			fondoRojo();
			cout << "\n=== INSERTAR EN ARBOL 2 (POR MONTO) ===" << endl;
			cout << "1. Tarjeta de Credito\n2. Tarjeta de Debito" << endl;
			int tipo;
			cout << "Tipo: ";
			cin >> tipo;
			limpiarBuffer();
			string numTarjeta;
			double monto;
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);
			cout << "Monto: $";
			cin >> monto;
			limpiarBuffer();

			if (tipo == 1) {
				TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) tarjeta->insertarEnArbolPorMonto(monto);
				else cout << "Tarjeta no encontrada" << endl;
			}
			else {
				TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) tarjeta->insertarEnArbolPorMonto(monto);
				else cout << "Tarjeta no encontrada" << endl;
			}
			pausar();
			break;
		}

		case 18: { // Buscar en Arbol 1
			fondoRojo();
			cout << "\n=== BUSCAR EN ARBOL 1 ===" << endl;
			string numTarjeta;
			cout << "Numero de Tarjeta: ";
			getline(cin, numTarjeta);
			if (Tarjetas<string>::buscarEnArbolPorNumero(numTarjeta))
				cout << "Tarjeta ENCONTRADA" << endl;
			else cout << "Tarjeta NO encontrada" << endl;
			pausar();
			break;
		}

		case 19: { // Mostrar Arbol 1
			fondoRojo();
			Tarjetas<string>::mostrarArbol1Ordenado();
			pausar();
			break;
		}

		case 20: { // Mostrar Arbol 2
			fondoRojo();
			Tarjetas<string>::mostrarArbol2Ordenado();
			pausar();
			break;
		}

		case 21: { // Estructura Arbol 1
			fondoRojo();
			Tarjetas<string>::mostrarEstructuraArbol1();
			pausar();
			break;
		}

		case 22: { // Estructura Arbol 2
			fondoRojo();
			Tarjetas<string>::mostrarEstructuraArbol2();
			pausar();
			break;
		}

		case 23: { // Comparar busqueda
			fondoRojo();
			cout << "\n=== COMPARAR BUSQUEDA ===" << endl;
			string numTarjeta;
			double monto;
			cout << "Numero: ";
			getline(cin, numTarjeta);
			cout << "Monto: $";
			cin >> monto;
			limpiarBuffer();
			Tarjetas<string>::compararBusquedaEnArboles(numTarjeta, monto);
			pausar();
			break;
		}

		case 24: { // Transferir credito
			fondoRojo();
			cout << "\n=== TRANSFERIR CREDITO ===" << endl;
			string origen, destino;
			double monto;
			cout << "Tarjeta Origen: ";
			getline(cin, origen);
			cout << "Tarjeta Destino: ";
			getline(cin, destino);
			cout << "Monto: $";
			cin >> monto;
			limpiarBuffer();

			TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(origen);
			if (tarjeta != nullptr) tarjeta->transferirCredito(destino, monto);
			else cout << "Tarjeta no encontrada" << endl;
			pausar();
			break;
		}

		case 25: { // Transferir dinero
			fondoRojo();
			cout << "\n=== TRANSFERIR DINERO ===" << endl;
			string origen, destino;
			double monto;
			cout << "Tarjeta Origen: ";
			getline(cin, origen);
			cout << "Tarjeta Destino: ";
			getline(cin, destino);
			cout << "Monto: $";
			cin >> monto;
			limpiarBuffer();

			TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(origen);
			if (tarjeta != nullptr) tarjeta->transferirDinero(destino, monto);
			else cout << "Tarjeta no encontrada" << endl;
			pausar();
			break;
		}

		case 26: { // Mostrar mis transferencias
			fondoRojo();
			cout << "\n=== MIS TRANSFERENCIAS ===" << endl;
			cout << "1. Credito\n2. Debito" << endl;
			int tipo;
			string numTarjeta;
			cout << "Tipo: ";
			cin >> tipo;
			limpiarBuffer();
			cout << "Numero: ";
			getline(cin, numTarjeta);

			if (tipo == 1) {
				TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) tarjeta->mostrarMisTransferencias();
				else cout << "Tarjeta no encontrada" << endl;
			}
			else {
				TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
				if (tarjeta != nullptr) tarjeta->mostrarMisTransferencias();
				else cout << "Tarjeta no encontrada" << endl;
			}
			pausar();
			break;
		}

		case 27: { // Red completa
			fondoRojo();
			Tarjetas<string>::mostrarGrafoCompleto();
			pausar();
			break;
		}

		case 28: { // BFS
			fondoRojo();
			cout << "\n=== RECORRIDO BFS ===" << endl;
			string inicio;
			cout << "Tarjeta inicial: ";
			getline(cin, inicio);
			Tarjetas<string>::recorridoBFS(inicio);
			pausar();
			break;
		}

		case 29: { // DFS recursivo
			fondoRojo();
			cout << "\n=== RECORRIDO DFS (RECURSIVO) ===" << endl;
			string inicio;
			cout << "Tarjeta inicial: ";
			getline(cin, inicio);
			Tarjetas<string>::recorridoDFS(inicio);
			pausar();
			break;
		}

		case 30: { // Verificar camino
			fondoRojo();
			cout << "\n=== VERIFICAR CAMINO ===" << endl;
			string origen, destino;
			cout << "Origen: ";
			getline(cin, origen);
			cout << "Destino: ";
			getline(cin, destino);
			if (Tarjetas<string>::existeCamino(origen, destino))
				cout << "EXISTE camino" << endl;
			else cout << "NO EXISTE camino" << endl;
			pausar();
			break;
		}

		case 31: { // Analizar red
			fondoRojo();
			cout << "\n=== ANALIZAR RED ===" << endl;
			string numTarjeta;
			cout << "Numero Tarjeta Credito: ";
			getline(cin, numTarjeta);
			TarjetaCredito<string, double>* tarjeta = tablaTarjetasCredito.buscarRef(numTarjeta);
			if (tarjeta != nullptr) tarjeta->analizarRedTransferencias();
			else cout << "Tarjeta no encontrada" << endl;
			pausar();
			break;
		}

		case 32: { // Analizar patrones
			fondoRojo();
			cout << "\n=== ANALIZAR PATRONES ===" << endl;
			string numTarjeta;
			cout << "Numero Tarjeta Debito: ";
			getline(cin, numTarjeta);
			TarjetaDebito<string, double>* tarjeta = tablaTarjetasDebito.buscarRef(numTarjeta);
			if (tarjeta != nullptr) tarjeta->analizarPatronesRetiro();
			else cout << "Tarjeta no encontrada" << endl;
			pausar();
			break;
		}

		case 0:
			resetearFondo(); // ← Resetear al salir
			cout << "Volviendo al menu principal..." << endl;
			break;

		default:
			cout << "Opcion invalida." << endl;
			pausar();
			break;
		}

	} while (opcion != 0);
}

void menuReportes(ListaEnlazada<Cliente<string>>& listaClientes, ListaEnlazada<Cuenta<string, double>>& listaCuentas, ListaEnlazada<Servicios<string, double>>& listaDeServicios, ListaEnlazada<ServicioContratado<string>>& listaServiciosContratados) {
	cout << "\n=== REPORTES DEL SISTEMA ===" << endl;
	cout << "Total de Clientes: " << listaClientes.getTamanio() << endl;
	cout << "Total de Cuentas: " << listaCuentas.getTamanio() << endl;
	cout << "Total de Servicios: " << listaDeServicios.getTamanio() << endl;
	cout << "Total de Servicios Contratados: " << listaServiciosContratados.getTamanio() << endl;

	cout << "\n�Desea ver detalles? (s/n): ";
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

void menuTrasacciones(ListaEnlazada<Transaccion<string, double>>& listaTransacciones, HashTable<Servicios<string, double>>& tablaDeServicios) {
	int opcion;
	do {
		dibujarMenuTransaccion();
		gotoxy(5, 10);
		cout << "\n=== GESTION DE TRANSACCIONES ===" << endl;
		cout << "1. Mostrar Transacciones (NUM.Cuenta)" << endl;
		cout << "2. Filtrar Transacciones" << endl;
		cout << "3. Regresar a Menu Principal" << endl;
		cin >> opcion;
		limpiarBuffer();
		system("cls");
		dibujarMenuTransaccion();
		gotoxy(5, 10);
		switch (opcion) {
		case 1:
		{
			cout << "\n--- Mostrar Historial de Transacciones ---" << endl;
			string num_cuenta;
			cout << "Ingrese Numero de Cuenta: ";
			getline(cin, num_cuenta);
			Servicios<string, double>* servicio = tablaDeServicios.buscar(num_cuenta);
			if (servicio == nullptr) {
				cout << "ERROR: Servicio no encontrado.\n";
				break;
			}
			servicio->mostrarHistorialTransacciones();
			system("cls");
			pausar();
			break;

		};
		case 2:
		{
			cout << "\n--- Filtrar Historial de Transacciones ---" << endl;
		};
		case 3:
		{
			cout << "\n--- Regresar a Menu Principal ---" << endl;
		};
		default:
			break;
		}
	} while (opcion != 3);


};

int main() {

	// Estructuras de Datos Principales


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

	ListaEnlazada<Transaccion<string, double>> listaTransacciones;
	HashTable<Credito<string, double>> tablaCreditos(10);
	// Hash Tables para Tarjetas
	HashTable<TarjetaCredito<string, double>> tablaTarjetasCredito(10);
	HashTable<TarjetaDebito<string, double>> tablaTarjetasDebito(10);

	// Configuraci�n inicial
	Cuenta<string, double>::setTablaServiciosGlobal(tablaDeServicios);
	Seguros<string, double>::setTablaServiciosGlobal(tablaDeServicios);

	int opcionPrincipal;
	do {
		dibujarMenu();
		gotoxy(5, 10);
		mostrarMenu();
		
		cin >> opcionPrincipal;
		system("cls");
		limpiarBuffer();

		switch (opcionPrincipal) {
		case 1:
			
			menuClientes(tablaClientes);
			break;
		case 2:
			dibujarMenuCuentas();
			gotoxy(5, 10);
			menuCuentas(tablaCuentas, tablaDeServicios);
			system("cls");
			break;
		case 3:
			dibujarMenuSeguros();
			gotoxy(5, 10);
			menuSeguros(tablaSeguros, tablaDeServicios, tablaClientes);
			system("cls");
			break;
		case 4:
			//Gestionar Creditos
			dibujarMenuCreditos();
			gotoxy(5, 10);
			menuCreditos(tablaClientes, tablaCreditos);
			break;
		case 5:
			menuTarjetas(tablaTarjetasCredito, tablaTarjetasDebito, tablaDeServicios);
			break;
		case 6:
			menuServiciosContratados(tablaServiciosContratados, tablaClientes, tablaDeServicios);
			break;
		/*case 7:
			//menuReportes(listaClientes, listaCuentas, listaDeServicios, listaServiciosContratados);
			break;*/
		case 7:
			dibujarMenuTransaccion();
			gotoxy(5, 10);
			menuTrasacciones(listaTransacciones, tablaDeServicios);
			system("cls");
			break;
		case 8:
			cout << "\n�Gracias por usar el Sistema Bancario! Hasta pronto." << endl;
			break;
		default:
			cout << "Opcion no valida! Intente de nuevo." << endl;
			pausar();
		}
	} while (opcionPrincipal != 8);

	return 0;
};
