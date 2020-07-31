#include <iostream>
#include <queue>
#include <vector>
#include <float.h>
#include <iomanip>

using namespace std;
typedef pair<unsigned int, float> para;
double koszt = 0;
bool flaga = false;
bool drugieWywolanie = false;

class lista{
public:
    int val;
    vector<para> sasiad;
};

void BF(lista *graf[], int wierzcholki, int krawedzie, int iloscSklepow, int doOdwiedzenia[]){
    double *koszta = new double[wierzcholki];
    for(int i=0; i<wierzcholki; i++)
        koszta[i] = DBL_MAX;

    int index;
    double waga;

    koszta[0] = 0;

    for(int i=0; i<=wierzcholki-1; i++){
        for(unsigned int j=0; j<graf[i]->sasiad.size(); j++){
            index = graf[i]->sasiad[j].first;
            waga = graf[i]->sasiad[j].second;

            if(koszta[index] > koszta[graf[i]->val] + waga)
                koszta[index] =  koszta[graf[i]->val] + waga;

        }
    }

    for(int i=0; i<iloscSklepow; i++)
        koszt += koszta[doOdwiedzenia[i]];

    if(drugieWywolanie == true){
        for(int i=0; i<=wierzcholki-1; i++){
            for(unsigned int j=0; j<graf[i]->sasiad.size(); j++){
                index = graf[i]->sasiad[j].first;
                waga = graf[i]->sasiad[j].second;

                if(koszta[index] > koszta[graf[i]->val] + waga)
                    flaga = true;
            }
        }
    }

    delete []koszta;
}

int main(){
    ios_base::sync_with_stdio(false);
    unsigned int wierzcholki,krawedzie, A,B, iloscSklepow;
    float dlugoscA, dlugoscB, czasA, czasB, zyskA, zyskB, waga;
    cin >> wierzcholki >> krawedzie;

    lista **przod = new lista*[wierzcholki];
    lista **tyl = new lista*[wierzcholki];

    for(unsigned int i=0; i<wierzcholki; i++){
        przod[i] = new lista();
        tyl[i] = new lista();
    }

    for(unsigned int i=0; i<krawedzie; i++){
        cin >> A >> B >> dlugoscA >> czasA >> zyskA >> dlugoscB >> czasB >> zyskB;

        waga = (dlugoscA*0.49) + (czasA*0.18) - zyskA;
        przod[A]->val = A;
        przod[A]->sasiad.push_back(make_pair(B,waga));
        tyl[B]->val = B;
        tyl[B]->sasiad.push_back(make_pair(A,waga));

        waga = (dlugoscB*0.49) + (czasB*0.18) - zyskB;
        przod[B]->val = B;
        przod[B]->sasiad.push_back(make_pair(A,waga));
        tyl[A]->val = A;
        tyl[A]->sasiad.push_back(make_pair(B,waga));
    }

    cin >> iloscSklepow;

    int *doOdwiedzenia = new int[iloscSklepow];
    for(unsigned int i=0; i<iloscSklepow; i++)
        cin >> doOdwiedzenia[i];

    BF(przod, wierzcholki, krawedzie, iloscSklepow, doOdwiedzenia);
    drugieWywolanie = true; //janusz musi kupic wsio zeby wrocic, inaczej grazynka go ochrzani
    BF(tyl, wierzcholki, krawedzie, iloscSklepow, doOdwiedzenia);

    
    if(!flaga){
        double wynik = (koszt/(double)iloscSklepow);
        cout << fixed << setprecision(3) << wynik;
    }
    else cout << "DO DOMU!";

    delete [] przod;
    delete [] tyl;
    delete [] doOdwiedzenia;
    return 0;
}