#include <iostream>
#include <fstream>
using namespace std;
const int constprod=5;

int pos_mayor(int cantmcliente[],int codigocliente)
{
    int mayor= cantmcliente[0], pos;
    for(int i=0;i < codigocliente;i++){
        if(cantmcliente[i] > mayor){
            mayor =cantmcliente[i];
            pos =i;
        }
    }
    return pos;
}

void punto1(string nom_prod[],string nom_cliente[],float kg[][constprod],int cont[],int cant_cliente,int cant_prod)
{
    cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados: " << endl;
    for(int i=0;i < cant_cliente;i++){
            cout << i << ") " << nom_cliente[i] <<'\t';
        for(int j=0;j < cant_prod;j++){
            if(kg[i][j] > 13000){
                cout <<nom_prod[j] <<'\t';
                cont[i]+= 1;
            }
        }
        cout<<endl;
    }
}

void punto2(string nom_prod[],string nom_cliente[],int cod_cliente, int list_var[],int posi[],float km[][constprod])
{
    int pos =pos_mayor(list_var,cod_cliente);
    cout << endl;
    cout << "Listado de Km recorridos por tipo de producto (ascendente)"<<endl;
    int n,temp;
    do{
        n =0;
        for(int i=0;i < constprod; i++){
            if(km[pos][i] > km[pos][i+1]){
                temp = km[pos][i];
                km[pos][i] = km[pos][i+1];
                km[pos][i+1] = temp;
                n++;

                temp =posi[i];
                posi[i] = posi[i+1];
                posi[i+1] =temp;
            }
        }
    }
    while(n!=0);
    for(int i=0;i < constprod;i++){
        cout << nom_prod[posi[i]] << '\t' << km[pos][i] << "km"<<endl;
    }

}

void punto3(string nom_prod[],string nom_cliente[],int cant_entregas[][constprod], float cant_km[][constprod],int cod_cliente,int posi[],int cont_cliente[])
{
	int contmayor=0, nazi=0;
    for(int i=1;i<cod_cliente;i++){
        if(i == pos_mayor(cont_cliente,cod_cliente)){
           contmayor+=cant_entregas[i][0];
        }
        else{
            contmayor+=cant_entregas[i][posi[0]];
        }
    }
    cout<<"\nCantidad de entregas para el tipo de producto "<<nom_prod[posi[4]]<<" "<<contmayor<<endl;
}

int main()
{
    const int constcliente=8;
    string nombrecliente[constcliente];
    string nombreprod[constprod];
    int entregastotal[constcliente][constprod]{0};  //indica cuantas entregas tiene cada producto.
    int cantmayor[constcliente]{0};//cuenta la cantidad de tipos de elemento que superan los 13.000
    int posicionamiento[constprod]{0,1,2,3,4};
    float pesototal[constcliente][constprod]{0};//peso total de cada uno de los viajes
    float distanciatotal[constcliente][constprod]{0};

    ifstream nombres;
    nombres.open("Nombres.txt");
    if(!nombres){
        cout << "error al intentar abrir el archivo de nombre.";
        return 1;
    }
    for(int i=0;i < constcliente;i++){
        nombres>> nombrecliente[i];
    }
    for(int i=0;i < constprod;i++){
        nombres >> nombreprod[i];
    }
    nombres.close();

    ifstream datos;
    datos.open("Datos.txt");
    if(!datos){
        cout << "error al intentar abrir el archivo de Datos";
        return 2;
    }
    int codcliente, codprod;
    float ptkg, dist;
    while(datos >> codcliente >> codprod >> ptkg >> dist){
        entregastotal[codcliente][codprod]+= 1;
        pesototal[codcliente][codprod]+= ptkg;
        distanciatotal[codcliente][codprod]+= dist;
    }
    datos.close();
    
    punto1(nombreprod,nombrecliente,pesototal,cantmayor,constcliente,constprod);
    punto2(nombreprod,nombrecliente,constcliente,cantmayor,posicionamiento,distanciatotal);
    punto3(nombreprod,nombrecliente,entregastotal,distanciatotal,constcliente,posicionamiento,cantmayor);
    return 0;
}
