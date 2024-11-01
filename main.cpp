#include <iostream>
using namespace std;

void darBienvenida(string clavadiststa_1, string pais, int year) {
    cout << "Bienvenido a mi programa" << clavadiststa_1 << endl;
    cout << "País: " << pais << " Año: " << year << endl;
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

int main() {

    srand(time(0));
    string clavadiststa_1 = "Alejandra Orozco";
    string pais = "Mexico";
    int year = 2006;
    // Array de calificaciones
    float calificaciones[7];


    darBienvenida(clavadiststa_1, pais, year);
    
    int probabilidadDif = generarNum1al100();
    int probabilidadCal = generarNum1al100();
    
    float dificultad;
    float calificacion;

    if (probabilidadDif <= 5) {
        dificultad = generarDificultadAleatoria(14, 19);
        probabilidadCal = 0;
    } else if (probabilidadDif <= 15) {
        dificultad = generarDificultadAleatoria(20, 25);
        probabilidadCal = -5;
    } else if (probabilidadDif <= 30) {
        dificultad = generarDificultadAleatoria(25, 30);
        probabilidadCal = -10;
    } else if (probabilidadDif <= 60) {
        dificultad = generarDificultadAleatoria(30, 35);
        probabilidadCal = -15;
    } else if (probabilidadDif <= 80) {
        dificultad = generarDificultadAleatoria(35, 40);
        probabilidadCal = -20;
    } else if (probabilidadDif <= 95) {
        dificultad = generarDificultadAleatoria(40, 45);
        probabilidadCal = -25;
    } else {
        dificultad = generarDificultadAleatoria(45, 47);
        probabilidadCal = -30;
    }

    if (probabilidadCal < 0) {
        probabilidadCal += 100;
    }

    if (probabilidadCal <= 5) {
        calificacion += generarCalificacionAleatoria(0, 20);
    } else if (probabilidadCal <= 15) {
        calificacion += generarCalificacionAleatoria(20, 40);
    } else if (probabilidadCal <= 30) {
        calificacion += generarCalificacionAleatoria(40, 55);
    } else if (probabilidadCal <= 60) {
        calificacion += generarCalificacionAleatoria(55, 65);
    } else if (probabilidadCal <= 80) {
        calificacion += generarCalificacionAleatoria(65, 85);
    } else if (probabilidadCal <= 95) {
        calificacion += generarCalificacionAleatoria(85, 90);
    } else {
        calificacion += generarCalificacionAleatoria(90, 100);
    }
    
    // cout << "Probabilidad Dif: " << probabilidadDif << endl;
    // cout << "Dificultad: " << float(dificultad)/10 << endl;
    // cout << "Probabilidad Cal: " << probabilidadCal << endl;
    cout << "Calificacion: " << float(calificacion)/10 << endl;
    
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
