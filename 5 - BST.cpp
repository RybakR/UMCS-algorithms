#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int,string> klucz;

struct Wezel{
public:
    Wezel *ojciec;
    Wezel *lewy;
    Wezel *prawy;
    klucz k;

    Wezel(){
       ojciec = NULL;
       lewy = NULL;
       prawy = NULL;
    }
};

Wezel* root;

void wsadz(Wezel *x){
    if(!root){
        root = x;
    }
    else{
        Wezel *pom;
        Wezel *poczatek = root;

        while(true){
            if(x->k.first > poczatek->k.first){
                pom = poczatek;
                poczatek = poczatek->prawy;

                if(!poczatek){
                    poczatek = x;
                    poczatek->ojciec = pom;
                    pom->prawy = poczatek;
                    break;
                }
            } else {
                pom = poczatek;
                poczatek = poczatek->lewy;

                if(!poczatek){
                    poczatek = x;
                    poczatek->ojciec = pom;
                    pom->lewy = poczatek;
                    break;
                }
            }
       }
    }
}

Wezel* znajdz(int x, Wezel *root){
    Wezel *pom = root;

    while(pom){
        if(pom->k.first == x){
           return pom;
        } else {
            if(x > pom->k.first){
               pom = pom->prawy;
            }
            else {
               pom = pom->lewy;
            }
        }
    }
    return NULL;
}

Wezel* mini(Wezel *poczatek){
    Wezel *pom = poczatek;
    while(pom->lewy) {
        pom = pom->lewy;
    }
    return pom;
}

void usunPrzyObu(Wezel *usuwam){
    if(!usuwam->lewy && !usuwam->prawy){
        if(usuwam == usuwam->ojciec->lewy){
            usuwam->ojciec->lewy = NULL;
        } else if(usuwam == usuwam->ojciec->prawy){
            usuwam->ojciec->prawy = NULL;
        }

        delete usuwam;
        return;
    }
    else if(usuwam->lewy && !usuwam->prawy){
        usuwam->lewy->ojciec = usuwam->ojciec;

        if(usuwam == usuwam->ojciec->lewy){
            usuwam->ojciec->lewy = usuwam->lewy;
        } else if(usuwam == usuwam->ojciec->prawy){
            usuwam->ojciec->prawy = usuwam->lewy;
        }

        delete usuwam;
        return;
    }
    else if(!usuwam->lewy && usuwam->prawy){
        usuwam->prawy->ojciec = usuwam->ojciec;

        if(usuwam == usuwam->ojciec->lewy){
            usuwam->ojciec->lewy = usuwam->prawy;
        } else if(usuwam == usuwam->ojciec->prawy){
            usuwam->ojciec->prawy = usuwam->prawy;
        }

        delete usuwam;
        return;
    }
   return;
}

Wezel* usun(Wezel *usuwam){
    Wezel *tmp = new Wezel;

    if(!usuwam->lewy && !usuwam->prawy){
        if(usuwam == root){
            return NULL;
        } else {
            tmp = usuwam->ojciec;
            if(usuwam == tmp->lewy){
                tmp->lewy = NULL;
            } else if(usuwam == usuwam->ojciec->prawy){
                tmp->prawy = NULL;
            }

            delete usuwam;
            return tmp;
        }
    }
    else if(usuwam->lewy && !usuwam->prawy){
        if(usuwam == root){
            root = usuwam->lewy;
            delete usuwam;
            return NULL;
        } else {
            tmp = usuwam->ojciec;
            usuwam->lewy->ojciec = tmp;

            if(usuwam == usuwam->ojciec->lewy){
                tmp->lewy = usuwam->lewy;
            } else if(usuwam == usuwam->ojciec->prawy){
               tmp->prawy = usuwam->lewy;
            }

            delete usuwam;
            return tmp;
        }
    }
    else if(!usuwam->lewy && usuwam->prawy){
        if(usuwam == root){
            root = usuwam->prawy;
            delete usuwam;
            return NULL;
        } else {
            tmp = usuwam->ojciec;
            usuwam->prawy->ojciec = tmp;

            if(usuwam == usuwam->ojciec->lewy){
                tmp->lewy = usuwam->prawy;
            } else if(usuwam == usuwam->ojciec->prawy){
                tmp->prawy = usuwam->prawy;
            }

            delete usuwam;
            return tmp;
        }
    }
    else if(usuwam->lewy && usuwam->prawy){
        if(usuwam == root){
            tmp = mini(usuwam->prawy);
            int k = tmp->k.first;
            swap(root->k.second, tmp->k.second);
            usunPrzyObu(tmp);
            root->k.first = k;
            return NULL;
        } else {
            tmp = mini(usuwam->prawy);
            int k = tmp->k.first;
            swap(usuwam->k.second, tmp->k.second);
            usunPrzyObu(tmp);
            usuwam->k.first = k;
            return usuwam->ojciec;
        }
    }

    return NULL;
}

int main(){
    ios_base::sync_with_stdio(false);
    int n,m, liczba;
    string tekst;
    Wezel *usuwam;
    Wezel *pom;
    root = NULL;
    klucz tmp;
    cin >> n >> m;

    for(int i=0; i<n; i++){
        cin >> liczba;
        cin >> tekst;
        pom = new Wezel();
        pom->k = make_pair(liczba,tekst);
        wsadz(pom);
    }

    int x;
    for(int i=0; i<m; i++){
        cin >> x;
        usuwam = znajdz(x, root);

        if(usuwam == NULL)
            cout << "NIE";
        else
           while(usuwam != NULL){
                cout << usuwam->k.second;
                usuwam = usun(usuwam);
           }

        cout << endl;
}
    delete usuwam;
    delete pom;
    delete root;
    return 0;
}