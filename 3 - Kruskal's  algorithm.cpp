#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
unsigned int suma =0;
unsigned int rozmiar = 0;
list<unsigned int> pom ;

class Krawedz{
public:
    unsigned int punktA;
    unsigned int punktB;
    unsigned int waga;

    Krawedz(unsigned int a, unsigned int b, unsigned int w){
        punktA = a;
        punktB = b;
        waga = w;
    }
};

struct adapter{
    bool operator ()(Krawedz a, Krawedz b){
        return(a.waga > b.waga);
    }
};

typedef priority_queue<Krawedz, vector<Krawedz>, adapter> kolejka_priorytetowa;

class zbiory{
public:
    list<unsigned int> *zbior = new list<unsigned int> [rozmiar+1];
    unsigned int *lvl = new unsigned int[rozmiar+1];

    zbiory(){
        for(unsigned int i=0; i<rozmiar; i++){
            zbior[i].push_back(i);
            lvl[i] = i;
        }
    }

    void zlacz(unsigned int x, unsigned int y){
          zbior[lvl[x]].merge(zbior[lvl[y]]);
          lvl[y] = lvl[x];
          pom = zbior[lvl[x]];
          while(!pom.empty()){
              lvl[pom.front()] = lvl[x];
              pom.pop_front();
          }
    }

    bool znajdz(unsigned int x, unsigned int y){
        return lvl[x] == lvl[y];
    }

    void dilit(){
        delete []zbior;
        delete []lvl;
    }
};


void algorytmKruskala(kolejka_priorytetowa kolejka, unsigned int wierzcholki){
    rozmiar = wierzcholki;
    zbiory zbior;
    unsigned int a,b,waga;

    while(!kolejka.empty()){
        a = kolejka.top().punktA;
        b = kolejka.top().punktB;
        waga = kolejka.top().waga;
        kolejka.pop();

        if(!zbior.znajdz(a,b)){
            zbior.zlacz(a,b);
            suma += waga;
        }
    }

    zbior.dilit();
}

int main(){
ios_base::sync_with_stdio(false);
    unsigned int wierzcholki, krawedzie, A,B, koszt;
    cin >> wierzcholki >> krawedzie;
    bool *interesuje = new bool[wierzcholki];
    kolejka_priorytetowa kolejka;

    for(unsigned int i=0; i<wierzcholki; i++){
        cin >> interesuje[i];
    }

    for(unsigned int i=0; i<krawedzie; i++){
        cin >> A >> B >> koszt;
        if(interesuje[A] && interesuje[B]){
           Krawedz pom(A,B,koszt);
           kolejka.push(pom);
        }
    }

    if(kolejka.empty()){
        cout << 0;
        return 0;
    }

    algorytmKruskala(kolejka,wierzcholki);
    cout << suma;
    delete [] interesuje;
    return 0;
}