//  
#include <iostream>
#include <string>
using namespace std;

// generar numero random a partir de dos parametros de rango
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
};

class Ovni : public TransporteAereo {
    // Class implementation
};

class Clima {
    // Class implementation
    private:
        int temperatura;
        string situacion;
        
    public:
        Clima CambiarClima() {
            // Generar temperatura aleatoria entre 12 y 35
            temperatura = random(12, 35);
            
            // Generar un número aleatorio entre 1 y 3 para la situación del clima
            int s = random(1, 100);

            if (situacion == "Soleado") {
                
                // Asignar la situación del clima basada en el número aleatorio
                if (s <= 35) {
                    situacion = "Nublado";
                } else if (s <= 40) {
                    situacion = "Lluvioso";
                } else {
                    situacion = "Soleado";
                }
            } else if (situacion == "Nublado") {
                
                // Asignar la situación del clima basada en el número aleatorio
                if (s <= 15) {
                    situacion = "Nublado";
                } else if (s == 50) {
                    situacion = "Soleado";
                } else {
                    situacion = "Lluvioso";
                }
            } else if (situacion == "Lluvioso") {
                
                // Asignar la situación del clima basada en el número aleatorio
                if (s <= 30) {
                    situacion = "Lluvioso";
                } else if (s == 80) {
                    situacion = "Soleado";
                } else {
                    situacion = "Nublado";
                }
            }
            
            // Mostrar la temperatura y la situación del clima
            cout << "Temperatura: " << temperatura << endl;
            cout << "Situacion: " << situacion << endl;
            
            // Devolver el objeto Clima con los valores actualizados
            return *this;
        }

        string getSituacion() {
            return situacion;
        }
};

class Aeropuerto {
    private:
        string nombre;
        TransporteAereo EspacioAereo[5];
        Avion PistaAterrizaje[5];
        Avion PistaDespegue[4];
        Clima ClimaActual;
    public:
        Aeropuerto(string n) {
            nombre = n;
        }
        void getClimaActual() {
            // Implementacion
            ClimaActual.CambiarClima();
        }

        void simularPistaDespegue() {
            // Implementacion
            string situacion = ClimaActual.getSituacion();
            if (situacion == "Lluvioso") {
                cout << "Pista de despegue despejada" << endl;
            } else {
                cout << "Pista de despegue no despejada" << endl;
            }
        }

        void simularPistaAterrizaje() {
            // Implementacion
            string situacion = ClimaActual.getSituacion();
            if (situacion == "Lluvioso") {
                cout << "Pista de despegue despejada" << endl;
            } else {
                cout << "Pista de despegue no despejada" << endl;
            }

            // if (pista de despegue llena) { despegar } else { esperar }
        }

        void simularEspacioAerero() {
            // Implementacion
            // if (pista de aterrizaje llena) { despegar } else { esperar }
        }
};

int main(int argc, char const *argv[]) {
    string input;
    Aeropuerto aeropuerto("AICM");
    
    while (true) {
        cin >> input;
        if (input == "0") { break; }

        aeropuerto.getClimaActual();
        aeropuerto.simularPistaDespegue();
        aeropuerto.simularPistaAterrizaje();
        aeropuerto.simularEspacioAerero();
        // Pista
    }

    return 0;
};
