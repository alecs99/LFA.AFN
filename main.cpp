#include <iostream>
#include <fstream>

using namespace std;

class AFN {
    int nr_stari, nr_tranzitii, stare_initiala;
    struct stare {
        int in;
        int out;
        char c;
    } *s;
    int *fin;
public:
    AFN() {
        ifstream f("/Users/alc/CLionProjects/LFA/Proiect 1/automat.txt");
        f >> nr_stari;
        fin = new int[nr_stari];
        int i;
        for (i = 0; i < nr_stari; i++) {
            f >> fin[i];
        }
        f >> nr_tranzitii;
        f >> stare_initiala;
        s = new stare[nr_tranzitii];
        for (i = 0; i < nr_tranzitii; i++)
            f >> s[i].in >> s[i].c >> s[i].out;
        f.close();
    }

    int verificare(int c_cuv, int stare_cur, char cuvant[]) {
        int i = 0;
        if (strcmp(cuvant, "lambda") == 0) {
            if (fin[stare_cur] == 1)
                return 1;
            else return 0;
        }
        if (c_cuv == strlen(cuvant)) {
            if (fin[stare_cur] == 1)
                return 1;
            return 0;
        }
        for (i = 0; i < nr_tranzitii; i++) {
            if ((cuvant[c_cuv] == s[i].c) && (s[i].in == stare_cur)) {
                int stare_in = stare_cur;
                stare_cur = s[i].out;
                if (verificare(c_cuv + 1, stare_cur, cuvant) == 1)
                    return 1;
                else stare_cur = stare_in;
            }
        }
        return 0;
    }

    void citire(char cuvant[]) {
        if (verificare(0, stare_initiala, cuvant) == 1) {
            cout << "Cuvant acceptat";
        } else cout << "Cuvant gresit";


    }
};

int main() {

    AFN a;
    int x;
    char cuvant[100];
    cout << "Scrie cuvant:";
    cin >> cuvant;
    a.citire(cuvant);
    return 0;
}
