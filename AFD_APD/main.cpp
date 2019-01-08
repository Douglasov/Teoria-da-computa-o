/*Programa criado com intuito de ler uma estrutura de um AFD ou APD de um arquivo e testar palavras conforme esse AFD ou APD
Obs:neste pograma lambda e representado por **/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#include <windows.h>
#include <vector>
#include <locale.h>


using namespace std;


class apd
{
private:
    string ***transicao;//matriz de trasição em determinada transição para quais estado deve ir
    string ***etransicao;//matriz de trasição em determinada transição qual simbolo deve empilhar
    string ***dtransicao;//matriz de trasição em determinada transição qual simbolo deve desempilhar
    string *simpilha;//alfabeto dos simbolos
    string *palavras;//palavras a testar no apd
    int Npav;
    int Nestado;
    int Nalfabeto;
    int Nestadosfinais;
    int Nsimpilha;
    int pilhalambda;
    int letralambda;
    string estadoinicial;
    string *estadosfinais;
    vector<char> pilha;

public:
    //construtor que conforme o arquivo colocado no programa aloca as matrizes de transição,alfabetos e outros
    apd(char nomearq[])
    {
        char caractere;
        Nestado=0;
        Nalfabeto=0;
        Nsimpilha=0;
        ifstream ifs;
        ifs.open(nomearq);
        {
            //alocando o vetor conde contera ps estadps finais
            while(caractere!='\n')
            {
                caractere = (char) ifs.get();
                if(caractere==' '||caractere=='\n')
                {
                    Nestado++;
                }
            }
            caractere=0;

            estadosfinais=new string[Nestado];

            //vendo o tamanho do alfabeto dos simbolos
            while(caractere!='\n')
            {
                caractere = (char) ifs.get();
                if(caractere==' '||caractere=='\n')
                {
                    Nalfabeto++;
                }
            }
            caractere=0;


            //vendo o tamanho do alfabeto da pilha e alocando
            while(caractere!='\n')
            {
                caractere = (char) ifs.get();
                if(caractere==' '||caractere=='\n')
                {
                    Nsimpilha++;
                }
            }
            ifs.close();
            simpilha=new string[Nsimpilha];
        }


        //alocando matriz de transições

        transicao= new string **[Nsimpilha];

        for (int i=0; i<Nsimpilha; i++)
        {
            transicao[i]=new string *[Nestado+1];
            for (int j=0; j<Nestado+1; j++)
                transicao[i][j]=new string [Nalfabeto+1];
        }


        //alocando matriz de simbolos para empilhar
        etransicao= new string **[Nsimpilha];

        for (int i=0; i<Nsimpilha; i++)
        {
            etransicao[i]=new string *[Nestado+1];
            for (int j=0; j<Nestado+1; j++)
                etransicao[i][j]=new string [Nalfabeto+1];
        }


        //alocando matriz de simbolos para desempilhar
        dtransicao= new string **[Nsimpilha];

        for (int i=0; i<Nsimpilha; i++)
        {
            dtransicao[i]=new string *[Nestado+1];
            for (int j=0; j<Nestado+1; j++)
                dtransicao[i][j]=new string [Nalfabeto+1];
        }

    }



    void preenchevar(char nomearq[])
    {
        string caracter;
        Nestadosfinais=0;
        char caractere='0';
        ifstream ifs;

        for(int l=0; l<Nsimpilha; l++)
        {
            transicao[l][0][0]='0';
            etransicao[l][0][0]='0';
            dtransicao[l][0][0]='0';
        }

        ifs.open(nomearq);
        {
            //pegando a lista de estados do automato e colocando na primeira coluna das matrizes de transição
            for(int i = 1; i < Nestado+1; ++i)
            {
                caractere =(char) ifs.get();
                do
                {
                    if(caractere!=' '&&caractere!='\n')
                    {
                        caracter=caracter+caractere;
                    }
                    caractere =(char) ifs.get();
                }
                while(caractere!=' '&&caractere!='\n');
                for(int h=0; h<Nsimpilha; h++)
                {
                    transicao[h][i][0] =caracter;
                    etransicao[h][i][0]=caracter;
                    dtransicao[h][i][0]=caracter;
                }
                caracter="\0";
            }

            //pegando o alfabeto dos simbolos e alocando na primera linha linha das matrizes de transição
            for(int j = 1; j < Nalfabeto+1; ++j)
            {
                caractere =(char) ifs.get();
                do
                {
                    if(caractere!=' '&&caractere!='\n')
                    {
                        caracter=caracter+caractere;
                    }
                    caractere =(char) ifs.get();
                }
                while(caractere!=' '&&caractere!='\n');
                for(int h=0; h<Nsimpilha; h++)
                {
                    transicao[h][0][j] =caracter;
                    etransicao[h][0][j] =caracter;
                    dtransicao[h][0][j] =caracter;
                    if(transicao[h][0][j]=="*")
                    {
                        letralambda=j;
                    }
                }
                caracter="\0";
            }

            //pegando alfabeto da pilha e alocando no seu vetor;
            for(int i = 0; i < Nsimpilha; ++i)
            {
                caractere =(char) ifs.get();
                do
                {
                    if(caractere!=' '&&caractere!='\n')
                    {
                        caracter=caracter+caractere;
                    }
                    caractere =(char) ifs.get();
                }
                while(caractere!=' '&&caractere!='\n');
                simpilha[i]=caracter;
                if(simpilha[i]=="*")
                {
                    pilhalambda=i;
                }
                caracter="\0";

            }


            caractere=(char) ifs.get();

            //pegando transições de estado e colocando na matriz de transição de estados;
            for(int i = 0; i < Nsimpilha; ++i)
            {
                for(int j = 1; j < Nestado+1; ++j)
                {
                    for(int k = 1; k < Nalfabeto+1; ++k)
                    {

                        do
                        {
                            if(caractere!=' '&&caractere!='\n')
                            {
                                caracter=caracter+caractere;
                            }
                            caractere =(char) ifs.get();
                        }
                        while(caractere!=' '&&caractere!='\n');
                        transicao[i][j][k] =caracter;
                        caracter="\0";
                    }
                }
            }
            caractere=(char) ifs.get();


            //pegando os simbolos que empilham conforme a transição de estado e colocando na matriz de transição de estados;
            for(int i = 0; i < Nsimpilha; ++i)
            {
                for(int j = 1; j < Nestado+1; ++j)
                {
                    for(int k = 1; k < Nalfabeto+1; ++k)
                    {

                        do
                        {
                            if(caractere!=' '&&caractere!='\n')
                            {
                                caracter=caracter+caractere;
                            }
                            caractere =(char) ifs.get();
                        }
                        while(caractere!=' '&&caractere!='\n');
                        etransicao[i][j][k] =caracter;
                        caracter="\0";
                    }
                }
            }
            caractere=(char) ifs.get();


            //pegando os simbolos que desempilham conforme a transição de estado e colocando na matriz de transição de estados;
            for(int i = 0; i < Nsimpilha; ++i)
            {
                for(int j = 1; j < Nestado+1; ++j)
                {
                    for(int k = 1; k < Nalfabeto+1; ++k)
                    {

                        do
                        {
                            if(caractere!=' '&&caractere!='\n')
                            {
                                caracter=caracter+caractere;
                            }
                            caractere =(char) ifs.get();
                        }
                        while(caractere!=' '&&caractere!='\n');
                        dtransicao[i][j][k] =caracter;
                        caracter="\0";
                    }
                }
            }


            caractere=(char) ifs.get();


            //pegando estado inicial
            do
            {
                if(caractere!=' '&&caractere!='\n')
                {
                    caracter=caracter+caractere;
                }
                caractere =(char) ifs.get();
            }
            while(caractere!=' '&&caractere!='\n');
            estadoinicial=caracter;
            caracter="\0";

            caractere =(char) ifs.get();

            //pegando estado final
            do
            {
                do
                {
                    if(caractere!=' '&&caractere!='\n')
                    {
                        Nestadosfinais++;
                        caracter=caracter+caractere;
                    }
                    caractere =(char) ifs.get();

                }
                while(caractere!=' '&&caractere!='\n');
                estadosfinais[Nestadosfinais-1]=caracter;
                caracter="\0";
            }
            while(caractere!='\n');


            caractere =(char) ifs.get();



            //identificando o numero de palavras
            do
            {
                if(caractere!=' '&&caractere!='\n')
                {
                    caracter=caracter+caractere;
                }
                caractere =(char) ifs.get();
            }
            while(caractere!=' '&&caractere!='\n');
            Npav=stoi(caracter);
            caracter="\0";

            //alocando a quantidade de palvras em string
            palavras=new string[Npav];
            //Pegando as palavras
            for(int i=0; i<Npav; i++)
            {
                do
                {
                    if(caractere!=' '&&caractere!='\n')
                    {
                        caracter=caracter+caractere;
                    }
                    caractere =(char) ifs.get();
                }
                while(caractere!=' '&&caractere!='\n'&&ifs.good());
                palavras[i]=caracter;
                caracter="\0";

            }
            ifs.close();
        }
    }

    //função para imprimir as matrizes de transição.estados finais,iniclal e as palavras;
    void imprimemattran()
    {
        for(int k = 0; k < Nsimpilha; ++k)
        {
            for(int i = 0; i < Nestado+1; ++i)
            {
                for(int j = 0; j < Nalfabeto+1; ++j)
                {
                    cout<<transicao[k][i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl<<endl;
        }

        cout<<endl;

        for(int k = 0; k < Nsimpilha; ++k)
        {
            for(int i = 0; i < Nestado+1; ++i)
            {
                for(int j = 0; j < Nalfabeto+1; ++j)
                {
                    cout<<etransicao[k][i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl<<endl;
        }
        cout<<endl;

        for(int k = 0; k < Nsimpilha; ++k)
        {
            for(int i = 0; i < Nestado+1; ++i)
            {
                for(int j = 0; j < Nalfabeto+1; ++j)
                {
                    cout<<dtransicao[k][i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl<<endl;
        }

        cout<<endl<<estadoinicial<<endl<<endl;

        for(int i; i<Nestadosfinais; i++)
        {
            cout<<estadosfinais[i]<<" ";
        }
        cout<<endl<<endl<<Npav<<endl;
        for(int i=0; i<Npav; i++)
        {
            cout<<endl<<palavras[i]<<endl;
        }

    }

    //função para testar as palavras passadas utilizando o APD passado
    void testapalavras()
    {
        bool npass=true;
        bool npasspil=true;
        string estadoatual;
        string simbolo;
        int auxsim;
        int auxest;
        int auxspilha;
        string auxemp;
        string auxdes;
        string piltop;
        int simlamb;
        bool complete;
        //percorre testando todas as palavaras contidas no arquivo
        for(int i=0; i<Npav; i++)
        {
            //limpa a pilha a cada palavra testada
            while(!pilha.empty())
            {
                pilha.pop_back();
            }

            complete=false;
            npass=true;
            npasspil=true;
            estadoatual=estadoinicial;
            for(int j=0; j<palavras[i].length(); j++)
            {
                simbolo=palavras[i][j];

                //pega o indice do estado a ser utilizado na matriz de transição
                for(int e=0; e<Nestado+1; e++)
                {
                    if(estadoatual==transicao[0][e][0])
                    {
                        auxest=e;
                    }

                }

                //pega o indice do simbolo do alfabeto a ser utilizado na matriz de transição
                for(int a=0; a<Nalfabeto+1; a++)
                {
                    if(simbolo==transicao[0][0][a]||simbolo=="*")
                    {
                        auxsim=a;
                    }
                }

                //pegando o simbolo do topo da pilha para varificar na transição com letra lambda
                for(int l=0; l<Nsimpilha; l++)
                {
                    if(!pilha.empty())
                    {
                        piltop=pilha.back();
                        if(piltop==simpilha[l])
                        {
                            auxspilha=l;
                        }
                    }
                }

                //Verificando transições onde o simbolo do alfabeto da palavra é lambda e a aplicando caso exista, caso não exista verifica normalmente as transições

                if(transicao[auxspilha][auxest][letralambda]!="e"&&!pilha.empty())
                {
                    auxsim=letralambda;
                    if(!complete)
                    {
                        j--;
                    }
                }

                else
                {
                    //verificando o simbolo do topo da pilnha e comparando com a transição do estado
                    if(pilha.empty()||"e"!=transicao[pilhalambda][auxest][auxsim])
                    {
                        for(int l=0; l<Nsimpilha; l++)
                        {
                            if("*"==simpilha[l])
                            {
                                auxspilha=l;
                            }
                        }
                    }
                    else
                    {
                        for(int l=0; l<Nsimpilha; l++)
                        {
                            piltop=pilha.back();
                            if(piltop==simpilha[l])
                            {
                                auxspilha=l;
                            }
                        }
                    }

                }


                estadoatual=transicao[auxspilha][auxest][auxsim];
                auxemp=etransicao[auxspilha][auxest][auxsim];
                auxdes=dtransicao[auxspilha][auxest][auxsim];
                //cout<<estadoatual<<' '<<auxemp<<' '<<auxdes<<' '<<endl;
                //testando o automato conforme a transição
                for(int l=0; l<auxdes.length(); l++)
                {
                    //verificando o topo da pilha e comparando com o simbolo a desempilhar caso não seja possivel desempilhar sinaliza que a palavra não passou no teste;
                    if(auxdes[l]!='*')
                    {
                        if(pilha.empty()||(pilha.back()!=auxdes[l]))
                        {
                            npasspil=false;
                            cout<<palavras[i]<<" não passou no teste"<<endl;
                            break;
                        }
                        else
                        {
                            pilha.pop_back();
                        }
                    }
                }

                for(int l=0; l<auxemp.length(); l++)
                {
                    //empilhando conforme a transição de estado
                    if(auxemp[l]!='*')
                    {
                        pilha.push_back(auxemp[l]);
                    }
                }

                if(!npasspil)
                {
                    break;
                }

                //verificando transições com lambda para letra apos ter terminado de percorrer a palavra
                if(j==(palavras[i].length()-1))
                {
                    complete=true;
                    if(!pilha.empty())
                    {
                        for(int l=0; l<Nsimpilha; l++)
                        {

                            piltop=pilha.back();
                            if(piltop==simpilha[l])
                            {
                                auxspilha=l;
                            }

                        }

                        for(int e=0; e<Nestado+1; e++)
                        {
                            if(estadoatual==transicao[0][e][0])
                            {
                                auxest=e;
                            }

                        }

                        if(transicao[auxspilha][auxest][letralambda]!="e")
                        {
                            j--;
                        }

                    }
                }
            }

            //apos verificar os estados finais com o atual sinaliza se a palavraa passou ou não no teste com o automato
            if(npasspil)
            {
                for(int v=0; v<Nestadosfinais; v++)
                {
                    if((estadoatual==estadosfinais[v])&&pilha.empty())
                    {
                        npass=false;
                        cout<<palavras[i]<<" passou no teste"<<endl;
                        break;
                    }
                    else if(((Nestadosfinais-1==v)&&npass)||!pilha.empty())
                    {
                        npass=true;
                        cout<<palavras[i]<<" não passou no teste"<<endl;
                        break;
                    }
                    npass=true;
                }
            }
        }

    }

};


class afd
{
private:
    string **transicao;
    string *palavras;
    int Npav;
    int Nestado;
    int Nalfabeto;
    string estadoinicial;
    string estadofinal;
public:
    //função utilizada para alocar a matriz de transição
    afd(char nomearq[])
    {
        char caractere;
        Nestado=0;
        Nalfabeto=0;
        ifstream ifs;
        ifs.open(nomearq);
        {
            while(caractere!='\n')
            {
                caractere = (char) ifs.get();
                if(caractere==' '||caractere=='\n')
                {
                    Nestado++;
                }
            }
            caractere=0;

            while(caractere!='\n')
            {
                caractere = (char) ifs.get();
                if(caractere==' '||caractere=='\n')
                {
                    Nalfabeto++;
                }
            }
            ifs.close();
        }
        transicao= new string *[Nestado+1];

        for (int i=0; i<Nestado+1; i++)
        {
            transicao[i]=new string[Nalfabeto+1];
        }


    }


    //função utilizada para preencher a matriz com os dados do arquivo
    void preenchevar(char nomearq[])
    {
        char man[50];
        string caracter;
        char caractere='0';
        ifstream ifs;
        transicao[0][0]='0';
        ifs.open(nomearq);
        {
            //pegando estados e colocando na primeira coluna da matriz de transição
            for(int i = 1; i < Nestado+1; ++i)
            {
                caractere =(char) ifs.get();
                do
                {
                    if(caractere!=' '&&caractere!='\n')
                    {
                        caracter=caracter+caractere;
                    }
                    caractere =(char) ifs.get();
                }
                while(caractere!=' '&&caractere!='\n');
                transicao[i][0] =caracter;
                caracter="\0";
            }

            //pegando alfabeto e colocando na primeira linha da matriz de transição
            for(int j = 1; j < Nalfabeto+1; ++j)
            {
                caractere =(char) ifs.get();
                do
                {
                    if(caractere!=' '&&caractere!='\n')
                    {
                        caracter=caracter+caractere;
                    }
                    caractere =(char) ifs.get();
                }
                while(caractere!=' '&&caractere!='\n');
                transicao[0][j] =caracter;
                caracter="\0";
            }

            caractere=(char) ifs.get();
            //pegando estados de transições e colocando na matriz de transição
            for(int i = 1; i < Nestado+1; ++i)
            {
                for(int j = 1; j < Nalfabeto+1; ++j)
                {
                    do
                    {
                        if(caractere!=' '&&caractere!='\n')
                        {
                            caracter=caracter+caractere;
                        }
                        caractere =(char) ifs.get();
                    }
                    while(caractere!=' '&&caractere!='\n');
                    transicao[i][j] =caracter;
                    caracter="\0";
                }
            }


            //pegando estado inicial
            do
            {
                if(caractere!=' '&&caractere!='\n')
                {
                    caracter=caracter+caractere;
                }
                caractere =(char) ifs.get();
            }
            while(caractere!=' '&&caractere!='\n');
            estadoinicial=caracter;
            caracter="\0";

            caractere =(char) ifs.get();

            //pegando estado final
            do
            {
                if(caractere!=' '&&caractere!='\n')
                {
                    caracter=caracter+caractere;
                }
                caractere =(char) ifs.get();
            }
            while(caractere!=' '&&caractere!='\n');
            estadofinal=caracter;
            caracter="\0";


            caractere =(char) ifs.get();



            //numero de palavras
            do
            {
                if(caractere!=' '&&caractere!='\n')
                {
                    caracter=caracter+caractere;
                }
                caractere =(char) ifs.get();
            }
            while(caractere!=' '&&caractere!='\n');
            Npav=stoi(caracter);
            caracter="\0";


            palavras=new string[Npav];
            //Pegando palavras
            for(int i=0; i<Npav; i++)
            {
                do
                {
                    if(caractere!=' '&&caractere!='\n')
                    {
                        caracter=caracter+caractere;
                    }
                    caractere =(char) ifs.get();
                }
                while(caractere!=' '&&caractere!='\n'&&ifs.good());
                palavras[i]=caracter;
                caracter="\0";

            }

            ifs.close();
        }
    }

    //função para imprimir a matriz de transição,estados finais,inicial e a spalavras a serem testadas
    void imprimemattran()
    {
        for(int i = 0; i < Nestado+1; ++i)
        {
            for(int j = 0; j < Nalfabeto+1; ++j)
            {
                cout<<transicao[i][j]<<" ";
            }
            cout<<endl;
        }

        cout<<endl<<estadoinicial<<endl;
        cout<<endl<<estadofinal<<endl;
        cout<<endl<<Npav<<endl;
        for(int i=0; i<Npav; i++)
        {
            cout<<endl<<palavras[i]<<endl;
        }
    }

    //função para testar as palavras no AFD
    void testapalavras()
    {
        string estadoatual;
        string simbolo;
        int auxsim;
        int auxest;
        for(int i=0; i<Npav; i++)
        {
            estadoatual=estadoinicial;
            for(int j=0; j<palavras[i].length(); j++)
            {
                simbolo=palavras[i][j];
                //pega o indice do estado a ser utilizado na matriz de transição
                for(int e=0; e<Nestado+1; e++)
                {
                    if(estadoatual==transicao[e][0])
                    {
                        auxest=e;
                    }
                }
                //pega o indice do simbolo do alfabeto a ser utilizado na matriz de transição
                for(int a=0; a<Nalfabeto+1; a++)
                {
                    if(simbolo==transicao[0][a])
                    {
                        auxsim=a;
                    }
                }
                //fazendo a transição de estado
                estadoatual=transicao[auxest][auxsim];


            }
            //comparando com o estado final o atual
            if((estadoatual==estadofinal))
            {
                cout<<palavras[i]<<" passou no teste";
            }
            else
            {
                cout<<palavras[i]<<" não passou no teste";
            }
            cout<<endl;
        }

    }

};




int main()
{
    setlocale(LC_ALL,"");
    int op=3;
    char arq[100];
    //Nome para os arquivos textados nesse programa
    //Caso não tenha os arquivos base para os 6 automatos iniciais do programa não escolher a opções 1 ate 6
    char arq1[50]= {'A','F','D','1','.','t','x','t','\0'};
    char arq2[50]= {'A','F','D','2','.','t','x','t','\0'};
    char arq3[50]= {'A','F','D','3','.','t','x','t','\0'};
    char arq4[50]= {'A','P','D','1','.','t','x','t','\0'};
    char arq5[50]= {'A','P','D','2','.','t','x','t','\0'};
    char arq6[50]= {'A','P','D','3','.','t','x','t','\0'};
    apd *apd1=new apd(arq4);
    apd *apd2=new apd(arq5);
    apd *apd3=new apd(arq6);
    afd *afd1=new afd(arq1);
    afd *afd2=new afd(arq2);
    afd *afd3=new afd(arq3);
    while(op>0&&op<9)
    {
        system("CLS");
        cout<<"*****Caso não tenha os arquivos base para os 6 automatos iniciais do programa não escolher a opções 1 ate 6*****\n\n";
        cout<<"Digite a opcao para o devido autonomo que deseja testar ou qualquer outro numero fora as opcoes para sair:\n\n1-{a}{a}{a,b}*{a}{a}\n2-{a}{b}{a}{a,b}\n";
        cout<<"3-onde o numeros de b's é par e a's é impar\n4-{a^n}{b^n} onde n>0\n5-{0^i}{1^j}{2^k} onde j=i+k e j>0\n6-onde o numero de 0's da palavra é o dobro do numeros 1's\n";
        cout<<"7-Utilizar um arquivo com configuração de um AFD proprio\n8-Utilizar um arquivo com configuração de um APD proprio\n";
        cin>>op;
        switch(op)
        {
        case 1:
        {
            system("CLS");
            cout<<"No AFD com a forma {a}{a}{a,b}*{a}{a} as seguintes palavras passaram ou não no teste:\n\n";
            afd1->preenchevar(arq1);
            //afd1->imprimemattran();
            afd1->testapalavras();
            system("pause");
        }
        break;

        case 2:
        {
            system("CLS");
            cout<<"No AFD com a forma {a}{b}{a}{a,b}* as seguintes palavras passaram ou não no teste:\n\n";
            afd2->preenchevar(arq2);
            //afd2->imprimemattran();
            afd2->testapalavras();
            system("pause");
        }
        break;

        case 3:
        {
            system("CLS");
            cout<<"No AFD com a forma onde o numeros de b's é par e a's é impar as seguintes palavras passaram ou não no teste:\n\n";
            afd3->preenchevar(arq3);
            //afd3->imprimemattran();
            afd3->testapalavras();
            system("pause");
        }
        break;

        case 4:
        {
            system("CLS");
            cout<<"No APD com a forma {a^n}{b^n} onde n>0 as seguintes palavras passaram ou não no teste:\n\n";
            apd1->preenchevar(arq4);
            //apd1->imprimemattran();
            apd1->testapalavras();
            system("pause");
        }
        break;

        case 5:
        {
            system("CLS");
            cout<<"No AFD com a forma {0^i}{1^j}{2^k} onde j=i+k e j>0 as seguintes palavras passaram ou não no teste:\n\n";
            apd2->preenchevar(arq5);
            //apd2->imprimemattran();
            apd2->testapalavras();
            system("pause");
        }
        break;

        case 6:
        {
            system("CLS");
            cout<<"No AFD com a forma onde o numero de 0's da palavra é o dobro do numeros 1's as seguintes palavras passaram ou não no teste:\n\n";
            apd3->preenchevar(arq6);
            //apd3->imprimemattran();
            apd3->testapalavras();
            system("pause");
        }
        break;
        //permite configurar um AFD e suas palavras a serem testadas por um arquivo de texto que siga as regras determinadas no programa
        case 7:
        {
            system("CLS");
            cout<<"Digite o nome do arquivo com as configurações do AFD:\n";
            fflush(stdin);
            gets(arq);
            afd *afdT=new afd(arq);
            afdT->preenchevar(arq);
            cout<<"As seguintes palavras passaram ou não no teste:\n";
            //afdT->imprimemattran();
            afdT->testapalavras();
            system("pause");
        }
        break;
        //permite configurar um AFD e suas palavras a serem testadas por um arquivo de texto que siga as regras determinadas no programa
        case 8:
        {
            system("CLS");
            cout<<"Digite o nome do arquivo comas configurações do APD:\n";
            fflush(stdin);
            gets(arq);
            apd *apdT=new apd(arq);
            apdT->preenchevar(arq);
            cout<<"As seguintes palavras passaram ou não no teste:\n";
            //apdT->imprimemattran();
            apdT->testapalavras();
            system("pause");
        }
        break;
        }
    }





    return 0;
}
