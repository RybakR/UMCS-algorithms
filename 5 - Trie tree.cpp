using namespace std;

struct TrieNode{
    char literka;
    bool czyKoniec;
    bool czyDzieci;
    TrieNode *dzieci[26];

    TrieNode(){
        czyKoniec = false;
        czyDzieci = false;
        for(unsigned int i=0; i<26; i++){
            dzieci[i] = nullptr;
        }
    }
};

TrieNode *root;

void szukaj(TrieNode *cos, string prefiks){
    prefiks += cos->literka;
    
    if(cos->czyKoniec){
        cout << prefiks << endl;
    }

    for(unsigned int i=0; i<26; i++){
        if(cos->dzieci[i]){
           szukaj(cos->dzieci[i], prefiks);
         }
    }

}

bool trieSearch(TrieNode *start, string slowo){
    TrieNode *poczatek = start;

    for (unsigned int i=0; i<slowo.length(); i++) {
        if(!poczatek->dzieci[slowo[i]-'a']){
            return false;
        }

        poczatek = poczatek->dzieci[slowo[i]-'a'];
    }

    if(poczatek->czyKoniec)
        cout << slowo << endl;

    if(!poczatek->czyDzieci){
        return true;
    }
    else {
        for(unsigned int i=0; i<26; i++){
            if(poczatek->dzieci[i]){
               szukaj(poczatek->dzieci[i], slowo);
            }
        }
        return true;
    }
}

void trieInsert(string slowo){
    TrieNode *poczatek = root;

    for (unsigned int i=0; i<slowo.length(); i++) {
        if(!poczatek->dzieci[slowo[i]-'a']){
            poczatek->dzieci[slowo[i]-'a'] = new TrieNode();
            poczatek->dzieci[slowo[i]-'a']->literka = slowo[i];
            poczatek->czyDzieci = true;
        }
        poczatek = poczatek->dzieci[slowo[i]-'a'];
    }
    poczatek->czyKoniec = true;
}

int main(){
    ios_base::sync_with_stdio(false);
    string nazwaUtworu;
    unsigned int N;
    char operacja;

    cin >> N;
    root = new TrieNode;

    for(unsigned int i=0; i<N; i++){
        cin >> operacja;

        if(operacja == 'A'){
            cin >> nazwaUtworu;
            trieInsert(nazwaUtworu);
        }
        else{
            cin >> nazwaUtworu;
            if(!trieSearch(root,nazwaUtworu))
                cout << "-" << endl;
         }
    }
    return 0;
}