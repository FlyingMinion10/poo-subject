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
        int turnosDescompuesto;
    public:
        // Metodo para crear un avion
        Avion(int n = 0) {
            if (n == 0) {
                matricula = 0;
                nombreAerolinea = "Sin aerolinea";
            } else {
                matricula = n;
                nombreAerolinea = (n == 2) ? "Aeromexico" : (n == 1) ? "Volaris" : "Interjet";   
                estado = "Volando";
                descompuesto = false;
                turnosDescompuesto = 0;
            }
        }

        void SetPlanePosition(int pos, string est) {
            posicion = pos;
            estado = est;
        }

        string getEstado() {
            return estado;
        }

        void descomponer(string pista) {
            if (descompuesto) {
                return;
            }
            int pd = random(1, 100);
            if (pd <= 10) {
                print("Avion #" + to_string(matricula) + " descompuesto en pista de " + pista);
                descompuesto = true;
                turnosDescompuesto = 2;
            }
        }
        
        bool avionDescompuesto() {
            if (descompuesto) {
                if (turnosDescompuesto == 0) {
                    descompuesto = false;
                }
                turnosDescompuesto--;
            } 
            return descompuesto;
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
            print("Clima: " + situacion + " a " + to_string(temperatura) + "°");
        }

        string getSituacion() {
            return situacion;
        }
};

class Aeropuerto {
    private:
        string nombre;
        vector<TransporteAereo*> EspacioAereo;
        Avion* PistaAterrizaje[5] = {nullptr}; // Usar punteros
        Avion* PistaDespegue[4] = {nullptr};   // Usar punteros
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

        void cambiarClimaActual() {
            ClimaActual.CambiarClima();
        }
        
        void simularLlegadaAviones(int turno) {
            if (hayOvni) {
                hayOvni = false;
                delete EspacioAereo.back();
                EspacioAereo.pop_back();
                print("OVNI se ha ido");
                return;
            }

            int n = random(1, 19);
            if (n <= 15) {
                TransporteAereo* tempPlane = new Avion(turno);
                if (EspacioAereo.size() < 5) {
                    EspacioAereo.push_back(tempPlane);
                    print("Avion detectado #" + to_string(tempPlane->getMatricula()) + " aproximandose");
                } else {
                    print("Avion detectado # " + to_string(tempPlane->getMatricula()) + " volando a otro aeropuerto");
                    delete tempPlane;
                }

            } else if (n <= 18) {
                print("OVNI ");
                TransporteAereo* tempOvni = new Ovni();
                if (EspacioAereo.size() < 5) {
                    print("OVNI detectado, tráfico aéreo detenido");
                    EspacioAereo.push_back(tempOvni);
                    hayOvni = true;
                } else {
                    print("OVNI detectado, tráfico aéreo detenido");
                    delete tempOvni;
                }
            } else {
                print("No se detecto nada");
            }
        }

        int posicionAterrizaje() {
            int bestPos = 4;
            for (int i = 4; i >= 0; i--) {
                if (PistaAterrizaje[i] == nullptr) {
                    bestPos = i;
                } else {
                    break;
                }
            }
            return bestPos;
        }
        
        int posicionDespegue() {
            int bestPos = 3;
            for (int i = 3; i >= 0; i--) {
                if (PistaDespegue[i] == nullptr) {
                    bestPos = i;
                } else {
                    break;
                }
            }
            return bestPos;
        }

        void simularEspacioAerero() {
            if (hayOvni || EspacioAereo.empty() || ClimaActual.getSituacion() == "Lluvioso") {
                return;
            }

            if (pistaAterrizajeCount >= 5) {
                print("Pista de aterrizaje llena");
                return;
            }

            TransporteAereo* transporte = EspacioAereo.front();
            if (transporte->getTipo() == "Avion") {
                Avion* AvionAterrizando = dynamic_cast<Avion*>(transporte);
                if (AvionAterrizando) {
                    print("Avion #" + to_string(AvionAterrizando->getMatricula()) + " aterrizando");
                    int pos = posicionAterrizaje();
                    PistaAterrizaje[pos] = AvionAterrizando;
                    AvionAterrizando->SetPlanePosition(pos, "Pista de aterrizaje");
                    pistaAterrizajeCount++;
                    EspacioAereo.erase(EspacioAereo.begin());
                }
            } else {
                print("Transporte no identificado para aterrizar");
            }
        }

        void simularPistaAterrizaje() {
            string situacion = ClimaActual.getSituacion();
            if (hayOvni || pistaAterrizajeCount == 0) {
                return;
            }
            
            if (pistaDespegueCount < 4) { 
                // Tomar avion en la posicion 0 de la pista de aterrizaje
                if (PistaAterrizaje[0] != nullptr) {
                    Avion* AvionEnCola = PistaAterrizaje[0];
                    AvionEnCola->descomponer("aterrizaje");
                    if (AvionEnCola->avionDescompuesto()) {
                        return;
                    }
                    // Cambiar el avion de pista
                    int pos = posicionDespegue();
                    PistaDespegue[pos] = AvionEnCola;
                    PistaAterrizaje[0] = nullptr;
                    print("Avion #" + to_string(AvionEnCola->getMatricula()) + " cambiando a pista de despegue");
                    
                    // Actualizar contadores y posiciones
                    pistaAterrizajeCount--;
                    pistaDespegueCount++;
                    AvionEnCola->SetPlanePosition(pos, "Pista de despegue");
                }
                // Mover aviones en la pista de aterrizaje
                for (int i = 0; i < pistaAterrizajeCount - 1; i++) {
                    Avion* AvionEnMovimiento = PistaAterrizaje[i+1];
                    AvionEnMovimiento->descomponer("aterrizaje");
                    if (AvionEnMovimiento->avionDescompuesto()) {
                        break;
                    }
                    PistaAterrizaje[i] = AvionEnMovimiento;
                    PistaAterrizaje[i+1] = nullptr;
                }
            } else {
                print("Pista de despegue llena");
            }
        }

        void simularPistaDespegue() {
            if (hayOvni || pistaDespegueCount == 0 || ClimaActual.getSituacion() == "Lluvioso") {
                return;
            }

            if (PistaDespegue[0] != nullptr) {
                Avion* AvionVolando = PistaDespegue[0];
                AvionVolando->descomponer("despegue");
                if (AvionVolando->avionDescompuesto()) {
                    return;
                }
                print("Avion #" + to_string(AvionVolando->getMatricula()) + " despegando");
                pistaDespegueCount--;
                delete AvionVolando;
                PistaDespegue[0] = nullptr;
            }
            
            for (int i = 0; i < pistaDespegueCount; i++) {
                print("Dentro del for"+to_string(i));
                Avion* AvionEnMovimiento = PistaDespegue[i+1];
                AvionEnMovimiento->descomponer("aterrizaje");
                if (AvionEnMovimiento->avionDescompuesto()) {
                    break;
                }
                PistaDespegue[i] = AvionEnMovimiento;
                PistaDespegue[i+1] = nullptr;
            }
        }

        void imprimirEspacios() {
            
            cout <<"PD [ ";
            for (int i = 0; i < 4; i++) {
                if (PistaDespegue[i] != nullptr) {
                    cout << to_string(PistaDespegue[i]->getMatricula()) << ", ";
                }
            }
            cout << "]" << endl;

            cout << "PA [ ";
            for (int i = 0; i < 5; i++) {
                if (PistaAterrizaje[i] != nullptr) {
                    cout << to_string(PistaAterrizaje[i]->getMatricula()) << ", ";
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

    for (int turno = 0; turno < 30; turno++) {
        for (int i = 1; i < 1000000000; i++);
        print("---------------------------------------------------------");
        aeropuertoMx.cambiarClimaActual();
        aeropuertoMx.simularPistaDespegue();
        aeropuertoMx.simularPistaAterrizaje();
        aeropuertoMx.simularEspacioAerero();
        aeropuertoMx.simularLlegadaAviones(turno);
        aeropuertoMx.imprimirEspacios();
    }

    return 0;
}
