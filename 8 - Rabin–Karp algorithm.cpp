#include <iostream>
#include <vector>
#include <string>
using namespace std;

int haszuj(string klucz, int v){
    int ind = 0;
    int pom;

    for(unsigned int i=0; i<klucz.length(); i++){
        pom = klucz[i] - '0';
        ind += (v*pom)%101;
    }
    return ind;
}

int main(){
    ios_base::sync_with_stdio(false);
    int v,n,p;
    cin >> v;
    int lancuch[v];

    for(int i=0; i<v; i++){
        cin >> n;
        lancuch[i] = n;
    }

    cin >> p;
    string subsekwencja = "";
    for (int i=0; i<p; i++) {
        cin >> n;
        subsekwencja += to_string(n);
    }

    string okno;
    int index = 0;
    int pozycja = 0;
    int itersuma = 0;
    int suma[2] = {-1,-1};
    int hasz = haszuj(subsekwencja,v);

    while(1){
        okno = "";
        for (int i=0; i<p; i++) {
            okno += to_string(lancuch[index+i]);
        }

        if(haszuj(okno,v) == hasz){
            if(okno.compare(subsekwencja) == 0){
                suma[itersuma] = index;

                if(suma[0] != -1 && suma[1] != -1){
                    pozycja = suma[0] + suma[1];
                    itersuma++;
                    if(itersuma == 2)
                        itersuma = 0;

                    while(pozycja < v){
                        suma[itersuma] = pozycja;
                        pozycja = suma[0] + suma[1];
                        itersuma++;
                        if(itersuma == 2)
                            itersuma = 0;
                    }

                    if(pozycja >= v){
                        pozycja -= v;
                        cout << pozycja << endl;
                        return 0;
                    }
                }

                itersuma++;
                if(itersuma == 2)
                    itersuma = 0;
            }
        }

        index++;
        if(index >= v) break;
    }
    
    cout << pozycja << endl;
    return 0;
}