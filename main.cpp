#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int probabilidades[6] = {5,10,15,30,20,15};

void darBienvenida(string clavadiststa_1, string pais, int year) {
    cout << clavadiststa_1 << " "<< year << " -- " << pais << endl;
}

int generarNum1al100() {
    return rand()%100;
}

float generarDificultadAleatoria(int n1, int n2) {
    return rand()%(n2-n1+1) + n1;
}

void indiceDeDesviacion(int x) {
    // Asegurarse de que x no sea mayor que el tamaño del array
    if (x > 6) {
        x = 6;
    }

    for (int i = 0; i < x; ++i) {
        // Guardar el primer elemento
        int temp = probabilidades[0];

        // Encontrar la posición correcta para colocar el elemento guardado
        int j = 1;
        while (j < 6 && probabilidades[j] > temp) {
            probabilidades[j - 1] = probabilidades[j];
            j++;
        }
        probabilidades[j - 1] = temp;
    }
}


float generarDificultad() {
    float dificultad;
    int probabilidadDif = generarNum1al100();

    if (probabilidadDif <= 5) {
        dificultad = generarDificultadAleatoria(14, 19);
    } else if (probabilidadDif <= 15) {
        dificultad = generarDificultadAleatoria(20, 25);
        indiceDeDesviacion(1);
    } else if (probabilidadDif <= 30) {
        dificultad = generarDificultadAleatoria(25, 30);
        indiceDeDesviacion(1);
    } else if (probabilidadDif <= 60) {
        dificultad = generarDificultadAleatoria(30, 35);
        indiceDeDesviacion(2);
    } else if (probabilidadDif <= 80) {
        dificultad = generarDificultadAleatoria(35, 40);
        indiceDeDesviacion(2);
    } else if (probabilidadDif <= 95) {
        dificultad = generarDificultadAleatoria(40, 45);
        indiceDeDesviacion(3);
    } else {
        dificultad = generarDificultadAleatoria(45, 47);
        indiceDeDesviacion(3);
    }
    return dificultad;
}

float generarCalificacionAleatoria(int n1, int n2) {
    return rand()%(n2-n1+1) + n1;
}


int main() {
    cout << "Bienvenido a mi programa" << endl;
    
    srand(time(0));
    string clavadiststa[7] = {"Alejandra Orozco", "Participant2", "Participant3", "Participant4", "Participant5", "Participant6", "Participant7"};
    string pais[7] = {"Mexico", "Country2", "Country3", "Country4", "Country5", "Country6", "Country7"};
    int year[7] = {2006, 2007, 2008, 2009, 2010, 2011, 2012};
    // Array de calificaciones
    float calificaciones[7];

    darBienvenida(clavadiststa[0], pais[0], year[0]);
    
    float dificultad = generarDificultad();
    
    int probabilidadCal = generarNum1al100();
    float calificacion;

    

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
    
    // cout << "Probabilidad Dif: " << probabilidadDif << endl;
    // cout << "Dificultad: " << dificultad << endl;
    // Imprimir calificaciones filtradas
    // cout << "probabilidades: ";
    // for (int i = 0; i < 6; ++i) {
    //     cout << probabilidades[i] << " ";
    // }
    // cout << endl;
    // cout << "probabilidadesK: ";
    // for (int i = 0; i < 6; ++i) {
    //     cout << probabilidadesK[i] << " ";
    // }
    // cout << endl;
    // cout << "Probabilidad Cal: " << probabilidadCal << endl;
    // cout << "Calificacion: " << float(calificacion)/10 << endl;
    
    // Llenar array de calificaciones
    for (int i = 0; i < 7; ++i) {
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

        if (probabilidadVar % 2 == 0) {
            var *= -1;
        }

        calificaciones[i] = calificacion + var;
    }
    
    // Ordenar calificaciones
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (calificaciones[i] > calificaciones[j]) {
                float temp = calificaciones[i];
                calificaciones[i] = calificaciones[j];
                calificaciones[j] = temp;
            }
        }
    }

    // Eliminar primera y ultima calificacion
    float calificacionesFiltradas[5];
    for (int i = 1; i < 6; ++i) {
        calificacionesFiltradas[i - 1] = calificaciones[i];
    }
    
    // Imprimir calificaciones filtradas
    cout << "Calificaciones filtradas: ";
    for (int i = 0; i < 5; ++i) {
        cout << calificacionesFiltradas[i] / 10 << " ";
    }
    cout << endl;



    return 0;
}
