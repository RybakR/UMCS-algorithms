#include <iostream>
#include <queue>
#include <vector>
#include <float.h>
#include <iomanip>

using namespace std;
typedef pair<unsigned int, double> para;

struct adapter{
    bool operator ()(para&a, para&b){
        if(a.second > b.second) return true;
        if(a.second < b.second) return false;
        return false;
    }
};

typedef priority_queue<para, vector<para>, adapter> kolejka_priorytetowa;
long double koszt = 0;

class lista{
public:
    int val;
    vector<para> sasiad;
};

void dijkstra(lista *graf[], int wierzcholki, int iloscSklepow, int doOdwiedzenia[]){  //O(VlogV)
    kolejka_priorytetowa *kolejka = new kolejka_priorytetowa;
    double *koszta = new double[wierzcholki];
    double waga;
    lista *pom;
    int index;
    int w;

    for(int i=0; i<wierzcholki; i++)
        koszta[i] = DBL_MAX;

    kolejka->push(make_pair(0,0));
    koszta[0] = 0;

    while(!kolejka->empty()){
        w = kolejka->top().first;
        kolejka->pop();
        pom = graf[w];

        for(unsigned int i=0; i<pom->sasiad.size(); i++){
            index = pom->sasiad[i].first;
            waga = pom->sasiad[i].second;

            if(koszta[index] > koszta[w] + waga){
                koszta[index] =  koszta[w] + waga;
                kolejka->push(make_pair(index,koszta[index]));
            }
        }
    }

    for(int i=0; i<iloscSklepow; i++)
        koszt += koszta[doOdwiedzenia[i]];

    delete []koszta;
    delete kolejka;
    delete pom;
}

int main(){
    ios_base::sync_with_stdio(false);
    unsigned int wierzcholki,krawedzie, A,B, iloscSklepow;
    double dlugoscA, dlugoscB, czasA, czasB, waga; //l0,t0 czas i dlugosc z A do B; l1, t1 to czas i dlugosc z B do A;

    cin >> wierzcholki >> krawedzie;

    lista **przod = new lista*[wierzcholki];
    lista **tyl = new lista*[wierzcholki];

    for(unsigned int i=0; i<wierzcholki; i++){
        przod[i] = new lista();
        tyl[i] = new lista();
    }

    for(unsigned int i=0; i<krawedzie; i++){
        cin >> A >> B >> dlugoscA >> czasA >> dlugoscB >> czasB;

        waga = (dlugoscA*0.49) + (czasA*0.18);
        przod[A]->sasiad.push_back(make_pair(B,waga));
        tyl[B]->sasiad.push_back(make_pair(A,waga));

        waga = (dlugoscB*0.49) + (czasB*0.18);
        przod[B]->sasiad.push_back(make_pair(A,waga));
        tyl[A]->sasiad.push_back(make_pair(B,waga));
    }

    cin >> iloscSklepow;

    int *doOdwiedzenia = new int[iloscSklepow];
    for(unsigned int i=0; i<iloscSklepow; i++)
        cin >> doOdwiedzenia[i];

    dijkstra(przod, wierzcholki, iloscSklepow, doOdwiedzenia);
    dijkstra(tyl, wierzcholki, iloscSklepow, doOdwiedzenia);

    long double wynik = (koszt/(double)iloscSklepow);
    cout << fixed << setprecision(3) << wynik;

    delete [] przod;
    delete [] tyl;
    delete [] doOdwiedzenia;
    return 0;
}