#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Generar numero random a partir de dos parametros de rango
int random(int min, int max) {
    return min + (rand() % (max - min + 1));
}

class TransporteAereo {
    protected:
        int matricula;
        string nombreAerolinea;
};

class Avion : public TransporteAereo {
    private:
        int posicion;
        string estado;
    public:
        // Metodo para crear un avion
        Avion(int m, string n) {
            matricula = m;
            nombreAerolinea = n;
            posicion = 0;
        }

        void setPlanePosition(int p) {
            posicion = p;
        }

        int getPlanePosition() {
            return posicion;
        }
};

class Ovni : public TransporteAereo {
    private:
        int posicion;
        string estado;
    public:
        Ovni(int t, string p) {
            int matricula;
            string nombreAerolinea;
            posicion = 0;
        }

        void setPlanePosition(int p) {
            posicion = p;
        }

        int getPlanePosition() {
            return posicion;
        }
};

class Clima {
    private:
        int temperatura;
        string situacion;

    public:
        Clima() {
            situacion = "Soleado";
        }

        void CambiarClima() {
            // Generar temperatura aleatoria entre 12 y 35
            temperatura = random(12, 35);
            
            // Generar un número aleatorio entre 1 y 100 para la situación del clima
            int s = random(1, 100);

            // Asignar la situación del clima basada en el número aleatorio y situación actual
            if (situacion == "Soleado") {
                if (s <= 35) {
                    situacion = "Nublado";
                } else if (s <= 50) {
                    situacion = "Lluvioso";
                }
            } else if (situacion == "Nublado") {
                if (s <= 15) {
                    situacion = "Nublado";
                } else if (s <= 50) {
                    situacion = "Soleado";
                } else {
                    situacion = "Lluvioso";
                }
            } else if (situacion == "Lluvioso") {
                if (s <= 30) {
                    situacion = "Lluvioso";
                } else if (s <= 80) {
                    situacion = "Soleado";
                } else {
                    situacion = "Nublado";
                }
            }

            // Mostrar la temperatura y la situación del clima
            cout << "Temperatura: " << temperatura << endl;
            cout << "Situacion: " << situacion << endl;
        }

        string getSituacion() {
            return situacion;
        }
};

class Aeropuerto {
    private:
        string nombre;
        vector<TransporteAereo*> EspacioAereo;
        vector<Avion> PistaAterrizaje;
        vector<Avion> PistaDespegue;
        Clima ClimaActual;

    public:
        Aeropuerto(string n) {
            nombre = n;
            PistaAterrizaje.resize(5);
            PistaDespegue.resize(4);
        }

        void getClimaActual() {
            ClimaActual.CambiarClima();
        }
        
        void simularPistaAterrizaje() {
            string situacion = ClimaActual.getSituacion();
            if (situacion == "Lluvioso") {
                cout << "Pista de aterrizaje no despejada" << endl;
            } else {
                cout << "Pista de aterrizaje despejada" << endl;
            }
        }

        void simularPistaDespegue() {
            string situacion = ClimaActual.getSituacion();
            if (situacion == "Lluvioso") {
                cout << "Pista de despegue no despejada" << endl;
            } else {
                cout << "Pista de despegue despejada" << endl;
            }
        }
        
        void simularEspacioAerero() {
            // Generacion de aeronaves
            int n = random(1, 20);
            if (n <= 15) {
                cout << "Avion detectado" << endl;
                Avion avion(random(1000, 9999), "Aeromexico");
                EspacioAereo.push_back(new Avion(avion));
            } else if (n <= 20) {
                cout << "OVNI detectado" << endl;
                Ovni ovni(random(10, 99), "Unknown");
                EspacioAereo.push_back(new Ovni(ovni));
            } else {
                cout << "No se detecto nada" << endl;
            }
            // Todos los aviones en el espacio aereo se mueven 1 posicion hacia adelante
            
        }
};

int main(int argc, char const *argv[]) {
    srand(time(0)); // Semilla para los números aleatorios
    string input;
    Aeropuerto aeropuerto("AICM");

    while (true) {
        cout << "Ingrese 0 para salir o cualquier otra tecla para continuar: ";
        cin >> input;
        if (input == "0") {
            break;
        }

        aeropuerto.getClimaActual();
        aeropuerto.simularEspacioAerero();
        aeropuerto.simularPistaDespegue();
        aeropuerto.simularPistaAterrizaje();
    }

    return 0;
}
