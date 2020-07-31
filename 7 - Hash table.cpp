#include <iostream>
#include <vector>
#include <string>
using namespace std;

int index;
unsigned int arrSiz = 997;

struct tmp{
    pair<string, string> glowna;
    vector<pair<string, string>> kolejne;
};

int haszuj(string klucz){
    int ind = 0;

    for(unsigned int i=0; i<klucz.length(); i++){
        ind +=  int(klucz[i]);
    }

    return ind%arrSiz;
}

int main(){
    ios_base::sync_with_stdio(false);
    string miejsce, nazwaKsiazki;
    unsigned int N;
    char operacja;
    cin >> N;

    tmp *tablica = new tmp[arrSiz];
    for (unsigned int i=0; i<arrSiz; i++)
        tablica[i].glowna = make_pair("-","-");

    for(unsigned int i=0; i<N; i++){
        cin >> operacja;

        if(operacja == 'A'){
            cin >> nazwaKsiazki;
            cin >> miejsce;
            index = haszuj(nazwaKsiazki);

            if(tablica[index].glowna.first == "-")
                tablica[index].glowna = make_pair(nazwaKsiazki,miejsce);
            else{
                tablica[index].kolejne.push_back(make_pair(nazwaKsiazki,miejsce));
            }
        }
        else{
           cin >> nazwaKsiazki;
           index = haszuj(nazwaKsiazki);

           if(tablica[index].glowna.first == "-"){
               cout << "-" << endl;
           }
           else if(tablica[index].glowna.first == nazwaKsiazki){
               cout << tablica[index].glowna.second << endl;
           }
           else {
               bool flaga = false;
               
               for(unsigned int i=0; i<tablica[index].kolejne.size(); i++){
                   if(tablica[index].kolejne[i].first == nazwaKsiazki){
                       flaga = true;
                       cout << tablica[index].kolejne[i].second << endl;
                       break;
                   }
               }
               
               if(!flaga)
                   cout << "-" << endl;
           }
        }
    }
    delete []tablica;
    return 0;
}