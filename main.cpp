#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Generar numero random a partir de dos parametros de rango
int random(int min, int max) {
    return min + (rand() % (max - min + 1));
}

void print(string s) {
    cout << s << endl;
}

class TransporteAereo {
    protected:
        int matricula;
        string nombreAerolinea;
    
    public:
        int getMatricula() {
                return matricula;
        }
};

class Avion : public TransporteAereo {
    private:
        int posicion;
        string estado;
        bool descompuesto;
    public:
        // Metodo para crear un avion
        Avion(int n = 0) {
            if (n == 0) {
                matricula = 0;
                nombreAerolinea = "Sin aerolinea";
            } else {
                matricula = random(1000, 9999);
                nombreAerolinea = (n = 2) ? "Aeromexico" : (n = 1) ? "Volaris" : "Interjet";   
                print("Avion creado con matricula: " + to_string(matricula) + " y aerolinea: " + nombreAerolinea);
            }
        }

        

        void SetPlanePosition(int pos, string est) {
            posicion = pos;
            estado = est;
        }

        void descomponer() {
            descompuesto = true;
        }
};

class Ovni : public TransporteAereo {
    private:
        int posicion;
        string estado;
    public:
        Ovni() {
            matricula = random(10, 99);
            nombreAerolinea = "Unknown";
            print("Ovni creado con matricula: " + to_string(matricula));
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
            print("Temperatura: " + to_string(temperatura));
            print("Situacion: " + situacion);
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
        int espacioAereoCount;
        int PistaAterrizajeCount;
        int PistaDespegueCount;
        bool hayOvni;

    public:
        Aeropuerto(string n) {
            nombre = n;
            espacioAereoCount = 0;
            PistaAterrizajeCount = 0;
            PistaDespegueCount = 0;
            hayOvni = false;
        }

        void getClimaActual() {
            ClimaActual.CambiarClima();
        }
        
        void simularLlegadaAviones() {
            // Si hay un ovni, detener el tráfico aéreo
            if (hayOvni) {
                print("Trafico aereo detenido por OVNI");
                hayOvni = false;
                return;
            }

            // Generacion de aeronaves
            int n = random(1, 20);
            if (n <= 15) { // SI SE DETECTA UN AVION
                print("Avion detectado");
                Avion tempPlane = Avion(n%3);

                if (espacioAereoCount < 5) {
                    EspacioAereo[espacioAereoCount++] = tempPlane;
                    print("Avion con matricula " + to_string(tempPlane.getMatricula()) + " aproximandose");
                } else {
                    print("Espacio aereo lleno, avion con matricula " + to_string(tempPlane.getMatricula()) + " volando a otro aeropuerto");
                }

            } else if (n <= 20) { // SI SE DETECTA UN OVNI
                print("Ovni detectado");
                Ovni tempOvni = Ovni();
                if (espacioAereoCount < 5) {
                    EspacioAereo[espacioAereoCount++] = tempOvni;
                    hayOvni = true;
                    print("OVNI con matricula " + to_string(tempOvni.getMatricula()) + " aproximandose");
                } else {
                    print("Espacio aereo lleno, OVNI con matricula " + to_string(tempOvni.getMatricula()) + " volando a otro planeta");
                }
            } else {
                print("No se detecto nada");
            }
        }

        void simularEspacioAerero() {

            if (espacioAereoCount == 0 ) {
                print("Espacio aereo vacio");
                return;
            }

            

            // Verificar si hay aviones en la pista de aterrizaje
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
        
};

int main(int argc, char const *argv[]) {
    srand(time(0)); // Semilla para los números aleatorios
    string input;
    Aeropuerto aeropuertoMx("AICM");

    while (true) {
        // delay de 1 segundo
        for (int i=0; i<1000000000; i++);
        print("---------------------------------------------------------");

        aeropuertoMx.getClimaActual();
        aeropuertoMx.simularPistaDespegue();
        aeropuertoMx.simularPistaAterrizaje();
        aeropuertoMx.simularEspacioAerero();
        aeropuertoMx.simularLlegadaAviones();
    }

    return 0;
}
