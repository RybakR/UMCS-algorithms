#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int h1,h2, m1, m2, nr, minuty1, minuty2;
    double suma =0;
    char dwukropek;

    cin >> h1 >> dwukropek >> m1;
    cin >> h2 >> dwukropek >> m2;
    cin >> nr;
    minuty1 = h1*60 + m1;
    minuty2 = h2*60 + m2;

    int wylosowanaH,wylosowanaM;

    for(int i=0; i<1000000; i++){
        wylosowanaH = (rand() % (minuty2-minuty1)) + minuty1;
        wylosowanaM = (rand() % 60) + 0;

        if(Grazyna(wylosowanaH/60,wylosowanaM) == nr)
            suma++;
    }

    double wynik = double(suma)/1000000.00;
    cout << fixed << setprecision(2) << wynik << endl;
    return 0;
}