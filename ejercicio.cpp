#include <iostream>
using namespace std;

class Protaginsta {
    private:
        string name;
};

class Book {
    private:
        string titulo;
        Protaginsta prota;

    public:
        Book(string t){
            titulo = t;
            cout << "Constructor no default" << endl;
        }

        Book(){
            cout << "Constructor default" << endl;
        }

        string getTitulo() {
            return titulo;
        }
};

class Escritor {
    private:
        string name;
        int yearBirth;
        
        int cantidadLibros;

    public:

        Book booksWritten[4];

        Escritor(string n, int y) {
            name = n;
            yearBirth = y;
            cantidadLibros = 0;
        }
        void setName(string n) {
            name = n;
        }

        void setYearBirth(int y) {
            yearBirth = y;
        }

        string getName() {
            return name;
        }

        int getYearBirth() {
            return yearBirth;
        }

        bool checkLibroExiste(Book libro) {
            for (int i=0; i<4; i++) {
                if (booksWritten[i].getTitulo() == libro.getTitulo()) {
                    return true;
                }
            }
            return false;
        }

        bool addBook(Book b) {

            if (cantidadLibros<4){
                for (int i=0; i<cantidadLibros; i++) {
                    if (booksWritten[i].getTitulo() == b.getTitulo()) {
                        return false;
                    };
                }
            }
            return true;
        }
};



int sumar(int& n1, int& n2) {
    n1 = 8;
    int total = n1 + n2;
    return total;
}

int main() {
    // Comentario opcionales
    // int x = 9;
    // int* apuntador;
    // cout << &x << "\n";
    // apuntador = &x;
    // cout << apuntador << "\n";
    // int y = 1;
    // cout << &x << "\n";
    // cout << sumar(x, y) << "\n";

    Escritor e("Pacheco", 1947);
    // Escritor p("Rulfo", 1956);
    Book c("Harry");

    cout <<&c << endl;
    cout << &e.booksWritten[0] << endl;

    e.addBook(c);
    
    return 0;
}
