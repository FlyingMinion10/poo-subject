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
        virtual ~TransporteAereo() {} // Add a virtual destructor
        virtual int getMatricula() {
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
                estado = "Volando";
                // print("Avion creado # " + to_string(matricula) + " de " + nombreAerolinea);
            }
        }

        void SetPlanePosition(int pos, string est) {
            posicion = pos;
            estado = est;
        }

        string getEstado() {
            return estado;
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
            // print("Ovni creado con matricula: " + to_string(matricula));
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
            // print("Clima: " + situacion + " a " + to_string(temperatura) + "°");
        }

        string getSituacion() {
            return situacion;
        }
};

class Aeropuerto {
    private:
        string nombre;
        // TransporteAereo EspacioAereo[5];
        vector<TransporteAereo> EspacioAereo;
        Avion PistaAterrizaje[5];
        Avion PistaDespegue[4];
        Clima ClimaActual;
        int espacioAereoCount;
        int pistaAterrizajeCount;
        int pistaDespegueCount;
        bool hayOvni;

    public:
        Aeropuerto(string n) {
            nombre = n;
            espacioAereoCount = 0;
            pistaAterrizajeCount = 0;
            pistaDespegueCount = 0;
            hayOvni = false;
        }

        void getClimaActual() {
            ClimaActual.CambiarClima();
        }
        
        void simularLlegadaAviones() {
            // Si hay un ovni, detener el tráfico aéreo
            if (hayOvni) {
                hayOvni = false;
                // Eliminar el ultimo objeto de Espacio aereo, que es el ovni
                EspacioAereo.pop_back();
                espacioAereoCount--;
                print("OVNI se ha ido");
                return;
            }

            // Generacion de aeronaves
            int n = random(1, 20);
            if (n <= 15) { // SI SE DETECTA UN AVION
                // print("Avion detectado");
                Avion tempPlane = Avion(n%3);
                cout << "Avion detectado ";
                // Si el espacio aereo no está lleno, agregar el avion
                if (espacioAereoCount < 5) {
                    EspacioAereo.push_back(tempPlane);
                    espacioAereoCount++;
                    print("con matricula " + to_string(tempPlane.getMatricula()) + " aproximandose");
                } else {
                    print("con matricula " + to_string(tempPlane.getMatricula()) + " volando a otro aeropuerto");
                }

            } else if (n <= 20) { // SI SE DETECTA UN OVNI
                Ovni tempOvni = Ovni();
                cout << "OVNI detectado ";
                // Si el espacio aereo no está lleno, agregar el ovni
                if (espacioAereoCount < 5) {
                    EspacioAereo.push_back(tempOvni);
                    espacioAereoCount++;
                    hayOvni = true;
                    print("con matricula " + to_string(tempOvni.getMatricula()) + " en cola");
                    print("Trafico aereo detenido por OVNI");
                } else {
                    print("con matricula " + to_string(tempOvni.getMatricula()) + " volando a otro planeta");
                }
            } else {
                print("No se detecto nada");
            }
        }

        int posicionAterrizaje() {
            // Determinar la mejor posicion para aterrizar
            int bestPos = 4;
            for (int i=4; i==0; i = i-1) {
                // Revisar si la posicion i está vacia
                if (PistaAterrizaje[i].getMatricula() == 0) {
                    bestPos = i;
                } else {
                    break;
                }
            }
            return bestPos;
        }
        
        int posicionDespegue() {
            // Determinar la mejor posicion para despegar
            int bestPos = 3;
            for (int i=3; i==0; i = i-1) {
                // Revisar si la posicion i está vacia
                if (PistaDespegue[i].getMatricula() == 0) {
                    bestPos = i;
                } else {
                    break;
                }
            }
            return bestPos;
        }

        void simularEspacioAerero() {

            // Si no hay aviones en el espacio aereo, no hacer nada
            if (hayOvni) {
                return;
            }

            if (espacioAereoCount == 0) {
                print("Espacio aereo vacio");
                return;

            } else if (pistaAterrizajeCount < 5) { // Verificar si hay aviones en la pista de aterrizaje
                Avion AvionAterrizando;

                try {
                    AvionAterrizando = dynamic_cast<Avion&>(EspacioAereo[0]);
                } catch (const std::bad_cast& e) {
                    print("Error al aterrizar avion");
                    return;
                }
                int pos = posicionAterrizaje();
                
                // Aterrizar avion en la ultima posicion
                PistaAterrizaje[pos] = AvionAterrizando;

                // Modificadores de estado
                AvionAterrizando.SetPlanePosition(pos, "Aterrizando");
                pistaAterrizajeCount++;

                // Eliminar el avion del espacio aereo
                EspacioAereo.erase(EspacioAereo.begin());
                espacioAereoCount--;
            } else {
                print("Pista de aterrizaje llena");
            }

            
        }

        void simularPistaAterrizaje() {
            string situacion = ClimaActual.getSituacion();
            // Si no hay aviones en el espacio aereo, no hacer nada
            if (hayOvni) {
                return;
            }
            
            if (pistaAterrizajeCount == 0) {
                print("Pista de aterrizaje vacia");
                return;

            } else if (pistaDespegueCount < 4) { 
                
                // Poner aviones en la pista de despegue
                Avion AvionEnCola = PistaAterrizaje[0];
                print("Avion con matricula " + to_string(AvionEnCola.getMatricula()) + " cambiando a pista de despegue");
                int pos = posicionDespegue();
                PistaDespegue[pos] = AvionEnCola;
                
                // Modificadores de estado
                AvionEnCola.SetPlanePosition(pos, "Despegando");
                pistaDespegueCount++;
                
                // Eliminar avion de la pista de aterrizaje
                for (int i=0; i<4; i++) {
                    PistaAterrizaje[i] = PistaAterrizaje[i+1];
                }
                pistaAterrizajeCount--;
            } else {
                print("Pista de aterrizaje llena");
            }
        }

        void simularPistaDespegue() {
            string situacion = ClimaActual.getSituacion();
            // Si no hay aviones en la pista de despegue, no hacer nada
            if (hayOvni) {
                return;
            }

            if (pistaDespegueCount > 0) {
                // Despegar aviones en la primera posicion de la pista de despegue
                Avion AvionVolando = PistaDespegue[0];
                print("Avion con matricula " + to_string(AvionVolando.getMatricula()) + "Despegando");
                
                // Eliminar avion de la pista de despegue
                for (int i=0; i<3; i++) {
                    PistaDespegue[i] = PistaDespegue[i+1];
                }
                pistaDespegueCount--;
            } else {
                print("Pista de despegue vacia");
            }
        }

        void imprimirEspacios() {
            cout <<"EA [ ";
            for (int i=0; i<espacioAereoCount; i++) {
                cout << to_string(EspacioAereo[i].getMatricula()) << ", ";
            }
            cout << "]" << endl;

            cout << "PA [ ";
            for (int i=0; i<5; i++) {
                if (PistaAterrizaje[i].getMatricula() != 0) {
                    cout << to_string(PistaAterrizaje[i].getMatricula()) << ", ";
                }
            }
            cout << "]" << endl;

            cout <<"PD [ ";
            for (int i=0; i<4; i++) {
                if (PistaDespegue[i].getMatricula() != 0) {
                    cout << to_string(PistaDespegue[i].getMatricula()) << ", ";
                    
                }
            }
            cout << "]" << endl;
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
        aeropuertoMx.imprimirEspacios();
    }

    return 0;
}
