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
    int stariLambda[100];
    int contor;
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



    queue <int> q;
    Muchie m[19];
    Stare st[8];

    if(!verificaAlfabet( cuvant, alfabet )){
        return 0;
    }
    else{
        for( int k = 0 ; k < nrStari; k++){
            st[k].contor = 1;
        }
        int i = 0;
        while( fin >> m[i].rad >> m[i].dest >> m[i].litera ){
            st[m[i].rad].stariLambda[0]= m[i].rad; //bagam pe el insusi
            if(m[i].litera == lambda){
                st[m[i].rad].stariLambda[st[m[i].rad].contor] = m[i].dest;
                st[m[i].rad].contor++;
            }
            i++;
        }
        fin.close();
        for( int j = 0 ; j < nrMuchii; j++ ){cout << m[j].rad << " " << m[j].dest << " " << m[j].litera << endl;}

        for( int h = 0 ; h < st[5].contor; h++){
            cout << st[5].stariLambda[h] << " ";
        }
        for(i = 0 ; i < nrStari; i++){
            cout << "-------------------EMPTY QUEUE ---- INCEPE STAREA: " << i << "-------------------"<< endl;
            //vreau pt toate starile sa gasesc lambda
            queue<int> c;
            int viz[nrStari] = {0};
            viz[i] = 1;
            //deja am bagat fii directi, trec la ei;

            //bag fii directi in coada
            for(int j = 1; j < st[i].contor; j++){
                if(st[i].stariLambda[j] != 1){
                    c.push(st[i].stariLambda[j]);
                    cout << "---Pushed " << st[i].stariLambda[j] << endl;
                }
            }
            while( !c.empty()){
            //o sa vreau fiii fiilor si tot asa
                int curent = c.front();
                c.pop();
                cout << "---Popped " << curent << endl;
                viz[curent] = 1;
                cout<< "Ne aflam pe " << curent << " are lambda fii: "<< endl;
                for( int k = 0 ; k < st[curent].contor; k++){
                    cout << st[curent].stariLambda[k] << " ";
                    //adaug la lambdaStari vector al tatalui i pe curent
                    if( viz[st[curent].stariLambda[k]] != 1 ){
                        st[i].contor++;
                        st[i].stariLambda[st[i].contor] = st[curent].stariLambda[k];
                        cout << endl <<"  ****Am adaugat " << st[curent].stariLambda[k] <<" la starea " << i;
                        c.push(st[curent].stariLambda[k]);
                        viz[st[curent].stariLambda[k]] = 1;
                    }
                }
                cout << endl << endl;
            }
            cout << "------------------------------ " << i << " done -------------------"<< endl;
        }

        /*
        q.push(stareInit); //s
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
    */
    }
    return 0;
}
