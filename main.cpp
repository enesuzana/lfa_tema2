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

struct Element{
    int s[10];
    int contorAFD;
    char lit;
};

struct Stare{
    int stariLambda[100];
    Element stariAFD[2];
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

bool checkFinal(int verif, int finale[], int nrFin){
    for(int i = 0 ; i < nrFin ; i++){
        if(verif == finale[i]){
            return true;
        }
    }
    return false;
}

void emptyy(int checked[], int nrStari){
    for(int i = 0 ; i < nrStari; i++){
        checked[i] = 0;
    }
}

//returneaza o coada cu starile in care ajung din 'stare' folosind litera 'lit'
queue<int> toLitera(int stare, char lit, Muchie m[], int nrTranz){
    int viz[10] = {0};
    queue<int> q;
    for(int i = 0 ; i < nrTranz; i++){
        if( m[i].rad == stare && m[i].litera == lit){
            if(!viz[m[i].dest]){
                q.push(m[i].dest);
                viz[m[i].dest] = 1;
            }
        }
    }

    return q;
}

//returneaza o coada cu starile in care ajung din stare folosind vectorul lambda al fiecarei stari
queue<int> toLambda(int stare, Stare st[], int nrStari){
    queue<int> q;
    for( int i = 0; i < st[stare].contor; i++){
        q.push(st[stare].stariLambda[i]);
    }
    return q;
}

int main(){
    int nrStari = 7, nrFinale = 2, nrMuchii = 19;
    int finale[nrFinale] = {2, 6};
    int nrFin = 2;
    char alfabet[] = "ab";
    char cuvant[] = "abbba";


    queue <int> q;
    Muchie m[19];
    Stare st[8]; //AFN-LAMBDA

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

        //aflam <qi> pentru fiecare stare, multimea starilor in care ajunge printr-un nr de lambda tranzitii

        for(i = 0 ; i < nrStari; i++){
            cout << "-------------------EMPTY QUEUE ---- INCEPE STAREA: " << i << "-------------------"<< endl;
            //vreau pt toate starile sa gasesc lambda
            queue<int> c;
            int viz[nrStari] = {0};
            viz[i] = 1;
            //deja am bagat fii directi, trec la ei;

            //bag fii directi in coada noua, ii vizitez
            for(int j = 1; j < st[i].contor; j++){
                if(st[i].stariLambda[j] != 1){
                    c.push(st[i].stariLambda[j]);
                    cout << "---Pushed " << st[i].stariLambda[j] << endl;
                    viz[st[i].stariLambda[j]] = 1;
                }
            }
            //parcurg in latime
            while( !c.empty()){
            //o saint checked[nrStari] = {0}; vreau fiii fiilor si tot asa
                int curent = c.front();
                c.pop();
                cout << "---Popped " << curent << endl;
                viz[curent] = 1;
                cout<< "Ne aflam pe " << curent << " are lambda fii: "<< endl;
                //pentru fiecare fiu in care "curent" ajunge cu Lambda
                for( int k = 0 ; k < st[curent].contor; k++){
                    cout << st[curent].stariLambda[k] << " ";
                    //adaug la lambdaStari vector al tatalui i pe curent
                    if( viz[st[curent].stariLambda[k]] != 1 ){ // daca e nevizitat, il adaug la vectorul parintelui initial
                        st[i].stariLambda[st[i].contor] = st[curent].stariLambda[k];
                        st[i].contor++; // cresc nr de elem din vector
                        cout << endl <<"  ****Am adaugat " << st[curent].stariLambda[k] <<" la starea " << i;
                        c.push(st[curent].stariLambda[k]); // adaug si la coada mea locala ca sa ii caut vecinii cu care formeaza si el lambda
                        viz[st[curent].stariLambda[k]] = 1;
                    }
                }
                cout << endl << endl;
            }
            cout << "------------------------------ " << i << " done -------------------"<< endl;
        }
        //afisare exemplu
        /*
        for( int h = 0 ; h < st[3].contor; h++){
            cout << st[3].stariLambda[h] << " ";
        }
        */
        //ACCEPTARE CUVANT:un cuv e acceptat daca intre oricare 2 litere avem oricat de multe lambda tranzitii
        int stareInit = 0;
        int checked[nrStari];
        if( st[stareInit].contor == 1 ){
            cout <<"INVALID!!";
            return 0;
        }
        //coada noua cu lambdaVector pt stareInit
        queue<int> iesLambda;
        queue<int> iesLitere;
        cout << " stInit  populare " << endl;
        for(i = 0 ; i < st[stareInit].contor; i++){
            iesLambda.push(st[stareInit].stariLambda[i]);// 023456
            cout << " Pushed in iesLambda " << st[stareInit].stariLambda[i] << endl;
        }
        //verificam cuvant
        for(int k = 0; k < strlen(cuvant); k++){
            //lambda
            cout << "#######SUNT PE LITERA " << cuvant[k] << endl;

            emptyy(checked, nrStari); // vector de vizitati
            //caut starile in care ajunge cu litera dorita, le bag in a doua coada
            cout << "^^^^^^^^Verific cu litera mea^^^^^^^^" << endl;
            checked[nrStari] = {0};
            while(!iesLambda.empty()){
                int luat = iesLambda.front();
                iesLambda.pop();
                cout << "* Popped out of iesLambda "<<  luat << endl;
                char lit = cuvant[k];
                for(int j = 0 ; j < nrMuchii; j++){
                    if( m[j].rad == luat && m[j].litera == lit ){
                        if(checked[m[j].dest] != 1){
                            iesLitere.push(m[j].dest);
                            cout << "* Pushed in iesLitere "<< m[j].dest << endl;
                            checked[m[j].dest] = 1;
                        }
                    }
                }
            }
            //la rand starile in care am ajuns cu LIT, dar acum cautam sa vedem unde merg cu lambda
            cout << "^^^^^^^^Verific cu LAMBDA^^^^^^^^"<< endl;
            emptyy(checked, nrStari);
            while(!iesLitere.empty()){
                int luat = iesLitere.front();
                iesLitere.pop();
                cout << "* Popped out of iesLitere "<< luat << endl;
                for(i = 0 ; i < st[luat].contor; i++){
                    if(checked[st[luat].stariLambda[i]] != 1){
                        iesLambda.push(st[luat].stariLambda[i]);// 023456
                        //iesLitere.push(st[luat].stariLambda[i]);
                        cout << "* Pushed in iesLambda "<< st[luat].stariLambda[i] << endl;
                        checked[st[luat].stariLambda[i]] = 1;
                    }
                }
            }
        }
        //ultimul vector e queue iesLambda populat, verific daca am macar o stare finala printre ele;
        bool conditie = false;
        for(int i = 0 ; i < iesLambda.size(); i++){
            int verif = iesLambda.front();
            iesLambda.pop();
            conditie = checkFinal(verif, finale, nrFin);
            if( conditie == true){
                cout << "ACCEPTAT!";

            }
        }
        if( conditie = false ){
            cout << "NEACCEPTAT";
        }

        for( int i = 0 ; i < nrStari; i++){
            cout << "------Suntem pe starea" << i << endl;
            int vizitati[nrStari];
            //extragem vector de Lambda pt i
            for( int contor = 0; contor < strlen(alfabet); contor++){
                    char litTemp = alfabet[contor]; // litera mea
                    //contor imi spune pe ce litera voi baga pt starea i urmatoarele
                    st[i].stariAFD[contor].lit = litTemp;
                    st[i].stariAFD[contor].contorAFD = 0;
                    emptyy(vizitati, nrStari);
            for(int k = 0;  k < st[i].contor; k++){
                int stare = st[i].stariLambda[k]; // extragem pe rand starile
                //caut pt fiecare litera in ce stare ajung pornind din 'stare' actuala
                    queue<int> coadaLit = toLitera(stare, litTemp, m, nrMuchii); // returnez o coada de stari in care ajung cu litera mea din stare
                    while(!coadaLit.empty()){
                        int extras = coadaLit.front();
                        coadaLit.pop();
                        queue<int> pushed = toLambda(extras, st, nrStari); // coada cu toate starile in care ajunge cu lambda
                        while( !pushed.empty()){ // bag starile cu lambda in starea i initiala, salvez, repet pt fiecare stare in care ajunsesem cu litera data
                            int bagat = pushed.front();
                            pushed.pop();
                            if(vizitati[bagat] != 1){
                                st[i].stariAFD[contor].s[st[i].stariAFD[contor].contorAFD] = bagat;
                                st[i].stariAFD[contor].contorAFD++;
                                vizitati[bagat] = 1;
                                cout << "I pushed "<< bagat <<" in stariAFD of " << i << "with char " << litTemp << endl;
                                cout<< "avem elemente nr: " << st[i].stariAFD[contor].contorAFD << endl;
                            }
                        }
                    }
                }
            }
        }

        cout << endl<< "FIECARE STARE -> LAMBDA LITERA LAMBDA " << endl;
        for(int c = 0 ; c < nrStari; c++){
            cout << "----------starea   " << c << endl;
            for( int i = 0 ; i < strlen(alfabet); i++){
                cout <<" LIT : " << alfabet[i] << endl;
                for( int j = 0; j < st[c].stariAFD[i].contorAFD; j++){
                    cout << st[c].stariAFD[i].s[j] << "  ";
                }
                cout << endl;
            }
             cout<< endl << "----------";
        }


        Muchie afd[nrMuchii];
        int next = nrStari;
        int numara = 0;
        queue<int> finale;

        // starea initiala ramane la fel ca in afn lambda
        char indiceA[st[0].stariAFD[0].contorAFD];
        for(int i = 0 ; i < st[0].stariAFD[0].contorAFD; i++){
            indiceA[i] = '0' + st[0].stariAFD[0].s[i];
            cout << indiceA[i];
        }
        char indiceB[st[0].stariAFD[1].contorAFD];
        cout << endl;
        for(int i = 0 ; i < st[0].stariAFD[1].contorAFD; i++){
            indiceB[i] = '0' + st[0].stariAFD[1].s[i];
            cout << indiceB[i];
        }
        cout << endl;
        //prima secventa de indici, din stare initiala am indiciiA, indicii B


        for( int i = 0 ; i < strlen(alfabet); i++){
                afd[numara].rad = stareInit;
                afd[numara].dest = next;
                afd[numara].litera = alfabet[i];
                finale.push(next);
                next++;
                numara++;
        }
        //am facut 2 muchii initiala ( stInit + fiu1, fiu2)

        //parcurg fiii prin ambele litere
        int vizz[nrStari];
        while(!finale.empty()){
                int pop = finale.front();
                finale.pop();
                emptyy(vizz, nrStari);
        for(int j = 0 ; j < strlen(alfabet); j++){
            char l = alfabet[j];  //litera curenta
            //
            afd[numara].rad = pop;
            afd[numara].litera = l;
            //muchia noua
            int vizitati[nrStari];
            emptyy(vizitati,nrStari);
            int p = 0;
            char verify[st[0].stariAFD[j].contorAFD]; // folosim ca sa vedem daca se repeta starile


            for( int i = 0 ; i < st[0].stariAFD[j].contorAFD; i++){
                int temp = st[0].stariAFD[j].s[i];
                queue<int> tmp;// bag in el toate starile lambdaCHARlambda
                for(int k = 0 ; k < st[temp].stariAFD[j].contorAFD; k++){
                    if( vizitati[st[temp].stariAFD[j].s[k]] != 1){
                        verify[p] = '0' + st[temp].stariAFD[j].s[k];
                        p++;
                        tmp.push(st[temp].stariAFD[j].s[k]);
                        cout << temp << "  pushed "<< st[temp].stariAFD[j].s[k] << endl;
                        vizitati[st[temp].stariAFD[j].s[k]] = 1;
                    }
                }
                if( l == 'a'){
                    if(strcmp(verify, indiceA) == 0){
                        //sunt engale, e muchie noua cu bucla
                        vizz[pop]++;
                        afd[numara].dest = pop;
                    }
                    else{
                        //diferite, creez stare noua
                        afd[numara].dest = next;
                        finale.push(next);
                        next++;
                    }
                }
                if( l == 'b'){
                    if(strcmp(verify, indiceB) == 0){
                        vizz[pop]++;
                        afd[numara].dest = pop;
                    }
                    else{
                        afd[numara].dest = next;
                        finale.push(next);
                        next++;
                    }
                }

            }
            if( vizz[pop] >= 2){ cout <<"END" ; break;}
            cout << "a doua lit" << endl;
            numara++;
        }
        }
        cout << endl;
        for( int i = 0 ; i < numara; i++){
            cout << afd[i].rad << "+" << afd[i].dest << " lit: " << (char)afd[i].litera << endl;
        }
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
    return 0;
}
