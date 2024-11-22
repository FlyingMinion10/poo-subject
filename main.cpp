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
        virtual string getTipo() const = 0; // Método virtual puro para obtener el tipo de transporte
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
                nombreAerolinea = (n == 2) ? "Aeromexico" : (n == 1) ? "Volaris" : "Interjet";   
                estado = "Volando";
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

        string getTipo() const override {
            return "Avion";
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
        }

        string getTipo() const override {
            return "Ovni";
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
        vector<TransporteAereo*> EspacioAereo;
        Avion PistaAterrizaje[5];
        Avion PistaDespegue[4];
        Clima ClimaActual;
        int pistaAterrizajeCount;
        int pistaDespegueCount;
        bool hayOvni;

    public:
        Aeropuerto(string n) {
            nombre = n;
            pistaAterrizajeCount = 0;
            pistaDespegueCount = 0;
            hayOvni = false;
        }

        ~Aeropuerto() {
            for (auto transporte : EspacioAereo) {
                delete transporte;
            }
        }

        void getClimaActual() {
            ClimaActual.CambiarClima();
        }
        
        void simularLlegadaAviones() {
            // Si hay un ovni, detener el tráfico aéreo
            if (hayOvni) {
                hayOvni = false;
                // Eliminar el ultimo objeto de Espacio aereo, que es el ovni
                delete EspacioAereo.back();
                EspacioAereo.pop_back();
                print("OVNI se ha ido");
                return;
            }

            // Generacion de aeronaves
            int n = random(1, 20);
            if (n <= 15) { // SI SE DETECTA UN AVION
                TransporteAereo* tempPlane = new Avion(n % 3);
                // Si el espacio aereo no está lleno, agregar el avion
                if (EspacioAereo.size() < 5) {
                    EspacioAereo.push_back(tempPlane);
                    print("Avion detectado con matricula " + to_string(tempPlane->getMatricula()) + " aproximandose");
                } else {
                    delete tempPlane;
                    print("Avion detectado con matricula " + to_string(tempPlane->getMatricula()) + " volando a otro aeropuerto");
                }

            } else if (n <= 20) { // SI SE DETECTA UN OVNI
                TransporteAereo* tempOvni = new Ovni();
                cout << "OVNI detectado, tráfico aéreo detenido" << endl;
                EspacioAereo.push_back(tempOvni);
                hayOvni = true;
            } else {
                print("No se detecto nada");
            }
        }

        int posicionAterrizaje() {
            // Determinar la mejor posicion para aterrizar
            int bestPos = 4;
            for (int i = 4; i >= 0; i--) {
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
            for (int i = 3; i >= 0; i--) {
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
            if (EspacioAereo.empty()) {
                return;
            }

            TransporteAereo* transporte = EspacioAereo.front();
            if (transporte->getTipo() == "Avion" && pistaAterrizajeCount < 5) { // Verificar si hay espacio en la pista de aterrizaje
                Avion* AvionAterrizando = dynamic_cast<Avion*>(transporte);
                print("Avion con matricula " + to_string(AvionAterrizando->getMatricula()) + " aterrizando");
                
                // Aterrizar avion en la ultima posicion
                int pos = posicionAterrizaje();
                PistaAterrizaje[pos] = *AvionAterrizando;

                // Modificadores de estado
                AvionAterrizando->SetPlanePosition(pos, "Aterrizando");
                pistaAterrizajeCount++;

                // Eliminar el avion del espacio aereo
                EspacioAereo.erase(EspacioAereo.begin());
                delete transporte;
            } else {
                print("Pista de aterrizaje llena o transporte no identificado para aterrizar");
            }
        }

        void simularPistaAterrizaje() {
            string situacion = ClimaActual.getSituacion();
            if (hayOvni || pistaAterrizajeCount == 0) {
                return;
            }
            
            if (pistaDespegueCount < 4) { 
                Avion AvionEnCola = PistaAterrizaje[0];
                print("Avion con matricula " + to_string(AvionEnCola.getMatricula()) + " cambiando a pista de despegue");
                
                // Formarse en la pista de despegue
                int pos = posicionDespegue();
                PistaDespegue[pos] = AvionEnCola;
                
                // Modificadores de estado
                AvionEnCola.SetPlanePosition(pos, "Despegando");
                pistaDespegueCount++;
                
                // Eliminar avion de la pista de aterrizaje
                for (int i = 0; i < 4; i++) {
                    PistaAterrizaje[i] = PistaAterrizaje[i + 1];
                }
                pistaAterrizajeCount--;
            } else {
                print("Pista de despegue llena");
            }
        }

        void simularPistaDespegue() {
            if (hayOvni || pistaDespegueCount == 0) {
                return;
            }

            if (pistaDespegueCount > 0) {
                Avion AvionVolando = PistaDespegue[0];
                print("Avion con matricula " + to_string(AvionVolando.getMatricula()) + " despegando");
                
                // Eliminar avion de la pista de despegue
                for (int i = 0; i < 3; i++) {
                    PistaDespegue[i] = PistaDespegue[i + 1];
                }
                pistaDespegueCount--;
            }
        }

        void imprimirEspacios() {
            
            cout <<"PD [ ";
            for (int i = 0; i < 4; i++) {
                if (PistaDespegue[i].getMatricula() != 0) {
                    cout << to_string(PistaDespegue[i].getMatricula()) << ", ";
                }
            }
            cout << "]" << endl;

            cout << "PA [ ";
            for (int i = 0; i < 5; i++) {
                if (PistaAterrizaje[i].getMatricula() != 0) {
                    cout << to_string(PistaAterrizaje[i].getMatricula()) << ", ";
                }
            }
            cout << "]" << endl;

            cout <<"EA [ ";
            for (size_t i = 0; i < EspacioAereo.size(); i++) {
                cout << to_string(EspacioAereo[i]->getMatricula()) << ", ";
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
        for (int i = 0; i < 1000000000; i++);
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
