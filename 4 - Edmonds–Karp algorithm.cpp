#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
typedef pair<int, int> para;

class Graf{
public:
    int val;
    vector<para> sasiad;
};
bool BFS(Graf tab[], int wierzcholki, int start, int koniec, para sciezka[], para indeksy[]){
    queue<int> *kolejka = new queue<int>;
    bool *odwiedzeni = new bool[wierzcholki];
    int nastepnik, pom, waga;

    for(int i=0; i<wierzcholki; i++)
        odwiedzeni[i] = false;

    sciezka[start] = make_pair(-1,0);
    odwiedzeni[start] = true;
    kolejka->push(start);


    while(!kolejka->empty()){
          pom = kolejka->front();
          kolejka->pop();
          if(pom == koniec) break;

          for(unsigned int i = 0; i < tab[pom].sasiad.size(); i++){
              nastepnik = tab[pom].sasiad[i].first;
              waga = tab[pom].sasiad[i].second;

              if((!odwiedzeni[nastepnik]) && (waga>0)){
                  sciezka[nastepnik] = make_pair(pom,waga);
                  indeksy[nastepnik] = make_pair(pom,i);
                  odwiedzeni[nastepnik] = true;
                  kolejka->push(nastepnik);
              }
         }
    }

    if(odwiedzeni[koniec] == true){
        delete []odwiedzeni;
        delete kolejka;
        return true;
    } else {
        delete []odwiedzeni;
        delete kolejka;
        return false;
    }
}

void EdmondsKarp(Graf kopia[], int wierzcholki, int start, int koniec){
    //cout << "KONIEC TO: " << koniec << endl;
    para *sciezka = new para[wierzcholki];
    para *indeksy = new para[wierzcholki];
    int janusz = zapytajJanusza(koniec);
    int max = 0;

    while(BFS(kopia,wierzcholki,start,koniec,sciezka,indeksy)){
        int tmp = sciezka[koniec].second;
        int minimum = 2147483647;
        int pom = koniec;

        while(pom > -1){
            if((tmp != 0) && (tmp < minimum))
                minimum = tmp;

            pom = sciezka[pom].first;
            tmp = sciezka[pom].second;
        }

        pom = koniec;
        tmp = sciezka[koniec].second;
        while(pom > -1){
           if(tmp != 0)
                kopia[indeksy[pom].first].sasiad[indeksy[pom].second].second -= minimum;
           pom = sciezka[pom].first;
           tmp = sciezka[pom].second;
        }

        max += minimum;
        if(max >= janusz) break;
    }

    if(max < janusz){
        cout << koniec << " NIE " << max << endl;
    }
    else cout << koniec << " OK" << endl;

    delete []sciezka;
    delete []indeksy;
}

int main(){
    ios_base::sync_with_stdio(false);
    int wierzcholki, krawedzie, start ,A,B, wydajnosc;
    cin >> wierzcholki >> krawedzie >> start;
    Graf *tab = new Graf[wierzcholki];

    for(int i=0; i<krawedzie; i++){
        cin >> A >> B >> wydajnosc;
        tab[A].val = A;
        tab[B].val = B;
        tab[A].sasiad.push_back(make_pair(B,wydajnosc));
    }

    for(int i=wierzcholki-1; i>=0; i--)
        if(tab[i].sasiad.empty()){
            Graf *kopia = new Graf[wierzcholki];
            for(int j=0; j<wierzcholki; j++){
                kopia[j] = tab[j];
            }
            EdmondsKarp(kopia,wierzcholki,start,i);
            delete []kopia;
        }

    delete []tab;
    return 0;
}