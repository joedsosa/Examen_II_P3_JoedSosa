#include "Columna.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
class Tabla {
public:
    Columna<string>* nombres;
    Columna<string>* apellidos;
    Columna<int>* edades;
    Columna<float>* notasExamenP;
    Columna<float>* notasAcumulativo;
    Columna<float>* notasExamenF;

    Tabla() {
        nombres = new Columna<string>();
        apellidos = new Columna<string>();
        edades = new Columna<int>();
        notasExamenP = new Columna<float>();
        notasAcumulativo = new Columna<float>();
        notasExamenF = new Columna<float>();

    }
    ~Tabla() {
        delete nombres;
        delete apellidos;
        delete edades;
        delete notasExamenP;
        delete notasAcumulativo;
        delete notasExamenF;
    }
//Metodo para cargar el archivo usando el token para separar las comas y agregarlos al vector de template con su tipo respectivo
    void cargarArchivoRegistros() {
        ifstream archivo("RegistrosUNITEC.txt");
        if (!archivo) {
            cout << "No se pudo abrir el archivo de registros." << endl;
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nombre, apellido, edadStr, notaPStr, notaAStr, notaFStr;

            if (getline(ss, nombre, ',') &&
                getline(ss, apellido, ',') &&
                getline(ss, edadStr, ',') &&
                getline(ss, notaPStr, ',') &&
                getline(ss, notaAStr, ',') &&
                getline(ss, notaFStr)) {

                int edad = stoi(edadStr);
                float notaEP = stof(notaPStr);
                float notaA = stof(notaAStr);
                float notaEF = stof(notaFStr);

                nombres->datosColumna.push_back(nombre);
                apellidos->datosColumna.push_back(apellido);
                edades->datosColumna.push_back(edad);
                notasExamenP->datosColumna.push_back(notaEP);
                notasAcumulativo->datosColumna.push_back(notaA);
                notasExamenF->datosColumna.push_back(notaEF);
            }
        }

        archivo.close();

        cout << "Registros cargados exitosamente." << endl;
    }
//Metodo para imprimir la tabla con las columnas alineadas en el CMD
    void imprimirTabla() {
        if (nombres->datosColumna.empty()) {
            cout << "No existe la tabla, abra el archivo de registros." << endl;
            return;
        }

        cout << "Tabla de registros:" << endl;
        cout << left << setw(15) << "Nombres" << setw(15) << "Apellidos" << setw(10) << "Edades"
            << setw(8) << "E1" << setw(8) << "A" << setw(8) << "EF" << endl;

        for (size_t i = 0; i < nombres->datosColumna.size(); i++) {
            cout << left << setw(15) << nombres->datosColumna[i] << setw(15) << apellidos->datosColumna[i]
                << setw(10) << edades->datosColumna[i] << setw(8) << notasExamenP->datosColumna[i]
                << setw(8) << notasAcumulativo->datosColumna[i] << setw(8) << notasExamenF->datosColumna[i] << endl;
        }
    }
    //fusiona las columnas con su respectiva info para  generar el txt y verificar si reprobo o aprobo
    void fusionarColumnas() {
        if (nombres->datosColumna.empty()) {
            cout << "No existe la tabla, abra el archivo de registros." << endl;
            return;
        }

        Columna<string>* nombresCompletos = new Columna<string>();
        Columna<int>* edadesFusionadas = new Columna<int>();
        Columna<float>* notasFinales = new Columna<float>();

        for (size_t i = 0; i < nombres->datosColumna.size(); i++) {
            string nombreCompleto = nombres->datosColumna[i] + " " + apellidos->datosColumna[i];
            nombresCompletos->datosColumna.push_back(nombreCompleto);
            edadesFusionadas->datosColumna.push_back(edades->datosColumna[i]);
            // se extraen las notas una por una segun la posicion donde estan gracias al for, y luego se suman para despues en el otro metodo 
            float notaFinal = (notasExamenP->datosColumna[i] + notasAcumulativo->datosColumna[i] + notasExamenF->datosColumna[i]);
            notasFinales->datosColumna.push_back(notaFinal);
        }
        nombres = nombresCompletos;
        edades = edadesFusionadas;
        notasExamenF = notasFinales;

        cout << "Columnas fusionadas exitosamente." << endl;
    }
    void guardarFusionColumna() {
        if (nombres->datosColumna.empty()) {
            cout << "Debe realizar la fusion antes de guardarla." << endl;
            return;
        }

        ofstream archivo("RegistrosFusionados.txt");
        if (!archivo) {
            cout << "No se pudo crear el archivo RegistrosFusionados.txt." << endl;
            return;
        }

        archivo << "NombreCompleto,Edad,NotaFinal,EstadoClase" << endl;

        for (size_t i = 0; i < nombres->datosColumna.size(); i++) {
            string nombreCompleto = nombres->datosColumna[i];
            int edad = edades->datosColumna[i];
            float notaFinal = notasExamenF->datosColumna[i];

            string estadoClase = " ";
            if (notaFinal > 60) {
                estadoClase = "Aprobo";
            }
            else {
                estadoClase = "Reprobo";
            }

            archivo << nombreCompleto << "," << edad << "," << notaFinal << "," << estadoClase << endl;
        }

        archivo.close();

        cout << "Fusion de columnas guardada exitosamente en RegistrosFusionados.txt." << endl;
    }

   
    
};
