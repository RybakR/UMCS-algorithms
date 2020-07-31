#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int x,y,z,n;
    double zapButelki,p;
    cin >> x >> y >> z >> p >> n;
    double wolneMiesjce = (x*y*z) - p*(x*y*z);  //gdzie (x*y*z) to objetosc akwarium

    for(int i=1; i<=n; i++){
        cin >> zapButelki;
        double objButelki = 0;
        
        for(double j=0; j<zapButelki; j+=0.001)
            objButelki += 2*pow(butelka(j),2);
        
        objButelki = objButelki * 0.5 * 0.001 * M_PI;
        wolneMiesjce -= objButelki;

        if(wolneMiesjce < 0){
            cout << i << endl;
            return 0;
        }
    }
    
    cout << "NIE" << endl;
    return 0;
}