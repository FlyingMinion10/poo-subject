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

class Villano {
    private:
        string name;
        int age;
        int skill;
    public:
        
        Villano(string n, int a) {
            name = n;
            age = a;
            skill = random (0, 100);
            print(to_string(skill));
        }

        void printName() {
            cout << name << endl;
        }

        int getSkill() {
            return skill;
        }
};

class Superheroe {
    private:
        string name;
        int age;
        int skill;
    public:
        
        Superheroe(string n, int a) {
            name = n;
            age = a;
            skill = random (0, 100);
            print(to_string(skill));
        }

        void printName() {
            cout << name;
        }

        bool atacar(Villano v) {
            bool Win = v.getSkill() > skill ? false: true;
            return Win;
        }
};

void batalla(Superheroe S, Villano V) {
    srand(time(0)); // Semilla para los números aleatorios
    bool res = S.atacar(V);
    S.printName(); // Corrección aquí

    if (res == true) {
        cout << " ganó vs ";
    } else {
        cout << " perdio vs ";
    }
    V.printName();
}

int main () {
    Superheroe SH("Batman", 48);
    Villano vf("Joker", 32);
    Villano vs("Penguin", 61);

    batalla(SH, vf); 
    batalla(SH, vs);

    return 0;
}