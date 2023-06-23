#include "Tabla.h"

#include <iostream>
#include <string>
// recibe una referencia de tabla del menu para simplemente leer los metodos de la clase Tabla
void menu(Tabla& tabla) {
	int opcion;

	do {
		cout << "-------------Menu------------" << endl;
		cout << "1. Cargar archivo de Registro" << endl;
		cout << "2. Imprimir Tabla" << endl;
		cout << "3. Fusion de columnas" << endl;
		cout << "4. Guardar fusion de columnas" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese la opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1: {
			tabla.cargarArchivoRegistros();
			break;
		}
		case 2: {
			tabla.imprimirTabla();
			break;
		}
		case 3: {
			tabla.fusionarColumnas();
			break;
		}
		case 4: {
			tabla.guardarFusionColumna();
			break;
		}
		case 5: {
			cout << "Saliendo del programa..." << endl;
			tabla.~Tabla();
			break;
		}
		default: {
			cout << "Opción invalida. Intente nuevamente." << endl;
			break;
		}
		}

		cout << endl;
	} while (opcion != 5);
}
// se crea el objeto tabla que es mandado al menu para que pueda accedera a los metodos que estan dentro de la clase tabla
int main() {
	Tabla tabla;
	menu(tabla);
	return 0;
}