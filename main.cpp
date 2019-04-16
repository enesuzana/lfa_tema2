#include <iostream>
#include <queue>
#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("tranzitii.in");
#define lambda '#'

struct Muchie{
    int rad;
    int dest;
    char litera;
};

struct Stare{
    queue<int> stariLambda;
};

bool verificaAlfabet( char cuvant[10], char alfabet[10]){
    for( int i = 0; i < strlen(cuvant); i++){
        char *p = strchr(alfabet, cuvant[i]);
        if( p == NULL){
            cout << "Cuv are o litera ce nu apartine alfabetului."<< endl;
            return false;
        }
    }
    return true;
}

int main(){
    int nrStari = 7, nrFinale = 2, nrMuchii = 19;
    int finale[nrFinale] = {2, 6};
    int stareInit = 0;
    char alfabet[] = "ab#";
    char cuvant[] = "baa";
    int i = 0;


    queue <int> q;
    Muchie m[nrMuchii];
    Stare st[nrStari];

    if(!verificaAlfabet( cuvant, alfabet )){
        return 0;
    }
    else{
        while( !fin.eof() ){
            fin >> m[i].rad >> m[i].dest >> m[i].litera;
            if(m[i].litera == lambda){
                st[m[i].rad].stariLambda.push(m[i].dest);
            }
            i++;
        }
        for( int i = 0 ; i < nrMuchii; i++ ){cout << m[i].rad << " " << m[i].dest << " " << m[i].litera << endl;}

        q.push(stareInit);
        int contor = 1;
        for(int k = 0; k < strlen(cuvant); k++ ){
            int x = contor;
            contor = 0;
            for( int i = 0 ; i < x; i++ ){
                int curent = q.front();
                cout << "------ Ne aflam pe ---> " << curent << endl;
                char lit = cuvant[k];
                cout << "Gasim muchie cu litera "<< lit << " in:" << endl;
                q.pop();

                for( int j = 0 ; j < nrMuchii; j++){
                    if( m[j].rad == curent && m[j].litera == lit){
                        cout << m[j].dest <<endl ;
                        q.push( m[j].dest );
                        contor++;
                    }
                }

                if( q.empty()){
                    cout<<"Nu mai exista muchie din " << curent <<" cu orice alta stare, deci nu e acceptat.";
                    return 0;
                }
                cout << endl;
            }
        }
    int y;
    while( !q.empty()){
        y = q.front();
        q.pop();
        for( int i = 0 ; i < nrFinale; i++){
            if( finale[i] == y){
                cout << "StareaFinala gasita : "<< y <<". Deci, cuvantul este acceptat." << endl;
                return 0;
            }
        }
    }
    cout << y <<"Cuvantul poate fi tranpus, dar nu exista stare finala pentru el";
    }
    return 0;
}
