#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Dificultad {
    float dificultad;
    int indiceDeDesviacion;
};

void darBienvenida(string clavadiststa_1, string pais, int year) {
    cout << "\n" << clavadiststa_1 << " " << year << " -- " << pais << endl;
}

int generarNum1al100() {
    return rand()%100;
}

float generarDificultadAleatoria(int n1, int n2) {
    return rand()%(n2-n1+1) + n1;
}

float generarCalificacionAleatoria(int n1, int n2) {
    return rand()%(n2-n1+1) + n1;
}

Dificultad generarDificultad() {
    Dificultad resultado;
    int probabilidadDif = generarNum1al100();

    if (probabilidadDif <= 5) {
        resultado.dificultad = generarDificultadAleatoria(14, 20);
    } else if (probabilidadDif <= 15) {
        resultado.dificultad = generarDificultadAleatoria(20, 25);
        resultado.indiceDeDesviacion = 1;
    } else if (probabilidadDif <= 30) {
        resultado.dificultad = generarDificultadAleatoria(25, 30);
        resultado.indiceDeDesviacion = 1;
    } else if (probabilidadDif <= 60) {
        resultado.dificultad = generarDificultadAleatoria(30, 35);
        resultado.indiceDeDesviacion = 2;
    } else if (probabilidadDif <= 80) {
        resultado.dificultad = generarDificultadAleatoria(35, 40);
        resultado.indiceDeDesviacion = 2;
    } else if (probabilidadDif <= 95) {
        resultado.dificultad = generarDificultadAleatoria(40, 45);
        resultado.indiceDeDesviacion = 3;
    } else {
        resultado.dificultad = generarDificultadAleatoria(45, 47);
        resultado.indiceDeDesviacion = 3;
    }
    return resultado;
}

float generarCalificacion(int desviacion) {
    float calificacion = 0;
    int probabilidadCal = generarNum1al100();

    int probabilidades[6] = {5,10,15,30,20,15};
    desviacion > 6 ? desviacion = 6 : desviacion;

    for (int i = 0; i < desviacion; ++i) {
        int temp = probabilidades[0];
        int j = 1;
        while (j < 6 && probabilidades[j] > temp) {
            probabilidades[j - 1] = probabilidades[j];
            j++;
        }
        probabilidades[j - 1] = temp;
    }

    int probabilidadesK[6] = {};
    probabilidadesK[0] = probabilidades[0];
    for (int i = 1; i < 6; ++i) {
        probabilidadesK[i] = probabilidadesK[i-1] + probabilidades[i];
    }

    if (probabilidadCal <= probabilidadesK[0]) {
        calificacion += generarCalificacionAleatoria(0, 20);
    } else if (probabilidadCal <= probabilidadesK[1]) {
        calificacion += generarCalificacionAleatoria(20, 40);
    } else if (probabilidadCal <= probabilidadesK[2]) {
        calificacion += generarCalificacionAleatoria(40, 55);
    } else if (probabilidadCal <= probabilidadesK[3]) {
        calificacion += generarCalificacionAleatoria(55, 65);
    } else if (probabilidadCal <= probabilidadesK[4]) {
        calificacion += generarCalificacionAleatoria(65, 85);
    } else if (probabilidadCal <= probabilidadesK[5]) {
        calificacion += generarCalificacionAleatoria(85, 90);
    } else {
        calificacion += generarCalificacionAleatoria(90, 100);
    }
    return calificacion;
}

float generarCalificaciones(float calificacion) {
    int probabilidadVar = generarNum1al100();

    int var;
    if (probabilidadVar <= 20) {
        var = 0;
    } else if (probabilidadVar <= 50) {
        var = 5;
    } else if (probabilidadVar <= 70) {
        var = 10;
    } else if (probabilidadVar <= 84) {
        var = 15;
    } else if (probabilidadVar <= 94) {
        var = 20;
    } else {
        var = 25;
    }

    if (probabilidadVar % 2 == 0 && calificacion < var) {
        var *= -1;
    }

    if (calificacion < 0) {
        calificacion *= -1;
    }

    return calificacion + var;
}

int generarTotal(float calificaciones[7]) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (calificaciones[i] > calificaciones[j]) {
                float temp = calificaciones[i];
                calificaciones[i] = calificaciones[j];
                calificaciones[j] = temp;
            }
        }
    }

    float calificacionesFiltradas[5];
    for (int i = 1; i < 6; ++i) {
        calificacionesFiltradas[i - 1] = calificaciones[i];
    }

    float suma = 0;
    for (int i = 0; i < 5; ++i) {
        suma += calificacionesFiltradas[i];
    }

    return suma;
}

int main() {
    cout << "Bienvenido a mi programa" << endl;
    
    srand(time(0));
    string clavadiststa[7] = {"Alejandra Orozco", "Participant2", "Participant3", "Participant4", "Participant5", "Participant6", "Participant7"};
    string pais[7] = {"Mexico", "Country2", "Country3", "Country4", "Country5", "Country6", "Country7"};
    int year[7] = {2006, 2007, 2008, 2009, 2010, 2011, 2012};

    float calificacionesTotales[7][6][7]; // Array tridimensional para almacenar todas las calificaciones

    float gross_scores[7];
    for (int i = 0; i < 7; ++i) {
        int score = 0;
        
        darBienvenida(clavadiststa[i], pais[i], year[i]);
        
        for (int j = 0; j < 6; ++j) {
            float calificaciones[7];

            Dificultad dificultad = generarDificultad();
            cout << "DD: " << dificultad.dificultad / 10 << "  --  ";
            
            float calificacion = generarCalificacion(dificultad.indiceDeDesviacion);

            for (int k = 0; k < 7; ++k) {
                calificaciones[k] = generarCalificaciones(calificacion);
                calificacionesTotales[i][j][k] = calificaciones[k]; // Guardar calificación en el array tridimensional
                cout << calificaciones[k] / 10 << ", ";
            }
            
            int total = generarTotal(calificaciones) / 10;
            cout << " --  Total: " << total;
            
            int points = total * dificultad.dificultad / 20;
            cout << " --  Points: " << points;

            score += points;
            cout << " --  Score: " << score << endl;
        }
        gross_scores[i] = score;
    }

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (gross_scores[i] > gross_scores[j]) {
                float temp = gross_scores[i];
                gross_scores[i] = gross_scores[j];
                gross_scores[j] = temp;

                string temp2 = clavadiststa[i];
                clavadiststa[i] = clavadiststa[j];
                clavadiststa[j] = temp2;
            }
        }
    }
    
    cout << "\nGanadores: " << endl;
    cout << "1. " << clavadiststa[0] << " -- " << gross_scores[0] << endl;
    cout << "2. " << clavadiststa[1] << " -- " << gross_scores[1] << endl;
    cout << "3. " << clavadiststa[2] << " -- " << gross_scores[2] << endl;

    // Mostrar todas las calificaciones almacenadas
    cout << "\nCalificaciones de cada participante en cada clavado:\n";
    for (int i = 0; i < 7; ++i) {
        cout << "Clavadista " << clavadiststa[i] << ":\n";
        for (int j = 0; j < 6; ++j) {
            cout << "  Clavado " << j + 1 << ": ";
            for (int k = 0; k < 7; ++k) {
                cout << calificacionesTotales[i][j][k] / 10 << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
