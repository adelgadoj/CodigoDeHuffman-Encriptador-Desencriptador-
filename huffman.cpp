#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;
struct letras
{
    char letra;
    int num;
};
struct nodo
{
    char letra;
    string peso;
    int frecuencia;
    struct nodo *sig;
    struct nodo *izq, *der;
};
struct arbol
{
    nodo *head;
};
void agregarletra(char letra, letras dicionario[52]){

    for(int i=0 ; i<52 ; i++)
    {
        if (letra == dicionario[i].letra)
            dicionario[i].num++;
    }
}
void verFrecuencias(letras dicionario[52]){
    cout<<"\n\nFRECUENCIAS:"<<endl;
    for(int i=0; i<52 ; i++){
        if (dicionario[i].num > 0){
            cout << dicionario[i].letra << " -> ";
            cout << dicionario[i].num << endl;
        }
    }
}
//ORDENAMIENTO DE LA LISTA DE FRECUENCIAS
void ordenar(letras lista[52]){
    letras aux1;

    for(int i = 0 ; i <52 ; i++){
        for(int j= 0 ; j <52; j++){
            if(lista[j].num > lista[j+1].num){ //SI EL SIGUIENTE ES MAYOR SE INSTERCAMBIA
                aux1 = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = aux1;
            }
        }
    }
}
// Esta funcion llena la lista con las letras del abecedario y valor de 0
void llenarLetras(letras v[52]){
    for (int i = 0; i < 26; i++)
    {
        v[i].letra = i + 97;
        v[i].num = 0;
    }
    for (int j = 0 ; j < 26; j++)
    {
        v[j+26].letra = j + 65;
        v[j+26].num = 0;
    }
}
// Construye una lista de las letras y frecuencias antes de ordenar el arbol
void insertarNodo(arbol *Tree, letras diccionario){
    nodo *nuevo = new nodo(); //CREAMOS UN NODO NUEVO 
    nuevo->letra = diccionario.letra;
    nuevo->frecuencia = diccionario.num;
    nuevo->sig = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nodo *aux1 = Tree->head; //CREAMOS UN NODO AUXILIAR QUE APUNTE A LA CABEZA
    nodo *aux2;
    while (aux1 != NULL)    
    {
        aux2 = aux1;
        aux1 = aux1->sig;
    }
    if (Tree->head == aux1)
    {
        Tree->head = nuevo;
    }
    else
    {
        aux2->sig = nuevo;
    }
    nuevo->sig = aux1;

}

//Si la frecuencia de la letra es mayor a 0 se agrega al arbol
void agregarLetrasArbol(arbol *Tree, letras diccionario[52]){
    for (int i = 0; i < 52; i++)
    {
        if (diccionario[i].num > 0)
        { 
                insertarNodo(Tree,diccionario[i]);
        }
    }
}
//FUNCION PARA VER EL ARBOL ANTES DE ORDENARSE
void verArbol(arbol *Tree){
    cout<<"\nARBOL TIPO LISTA: "<<endl;
    nodo *aux = Tree->head;
    if (aux == NULL)
    {
        cout << "NO TIENE NODOS..." << endl;
    }
    while (aux != NULL)
    {
        cout << aux->letra << "|" << aux->frecuencia<< " --> ";
        aux = aux->sig;
    }
}
void mostrarArbol(nodo *cabeza, int num)
{
    if (cabeza == NULL)
        return;
    mostrarArbol(cabeza->der, num + 1);

    for (int i = 0; i < num; i++)
        cout << "   ";

    cout << cabeza->frecuencia << " " << cabeza->letra << " " << cabeza->peso << endl;

    mostrarArbol(cabeza->izq, num + 1);
}
//Construyendo el arbol de HUFFMAN
void insertarNuevo(arbol *Arbol){
    verArbol(Arbol);

    nodo *nuevo = new nodo();
    nodo *a1 = Arbol->head;
    nodo *a2 = Arbol->head->sig;
    nuevo->frecuencia = a1->frecuencia + a2->frecuencia;
    nuevo->der = a2;
    nuevo->izq = a1;
    nuevo->peso = "0";
    nuevo->letra = ' ';
    nodo *aux1 = Arbol->head; //CREAMOS UN NODO AUXILIAR QUE APUNTE A LA CABEZA
    nodo *aux2;
    while ((aux1 != NULL) && (aux1->frecuencia < nuevo->frecuencia))
    {
        aux2 = aux1;
        aux1 = aux1->sig;
    }
    if (Arbol->head == aux1)
    {
        Arbol->head = nuevo;
    }
    else
    {
        aux2->sig = nuevo;
    }
    nuevo->sig = aux1;
    Arbol->head = Arbol->head->sig->sig;
    a1->sig = NULL;
    a1->peso = "0";
    a2->sig = NULL;
    a2->peso = "1";
}

//Recorre el arbol y va dando un codigo a cada nodo
void llenaPesoArbol(nodo *cabeza, string ant)
{
    if (cabeza == NULL) return;
    ant = ant + cabeza->peso;
    cabeza->peso = ant ;
    //cout << cabeza->frecuencia <<" " << cabeza->letra <<" "<< cabeza->peso << endl;
    llenaPesoArbol(cabeza->izq, ant);
    llenaPesoArbol(cabeza->der, ant);
    
}
//Busca el codigo de una letra en el Arbol
void buscaCodigo(char letra, nodo *head ,string &cadena){
    if (head == NULL)
        return;
    else if(letra == head->letra){
        //cout << head->letra << " " << head->peso << endl;
        cadena = cadena + head->peso;    
        }
    
    buscaCodigo(letra,head->izq, cadena);
    buscaCodigo(letra,head->der, cadena);
}
//Encriptacion de una cadena
void encripta(nodo *cabeza, string &cadena){
    char *palabra = new char();
    cout<<"INGRESA PALABRA: ";
    cin>>palabra;
    int tam;
    tam = strlen(palabra);
    cout<<"\nINGRESO : "<<palabra <<" tamano: "<<tam<<endl;
    for(int i=0 ; i < tam ; i++){ //La funcion busca el codigo de cada caracter en el arbol
                                  //y lo agrega a una cadena
        buscaCodigo(palabra[i], cabeza ,cadena);
    }
}
//Crea un archivo txt con la estructura del arbol
void construirDiccionario(nodo *cabeza, ofstream &archivo){
    if (cabeza == NULL)
        return;
    else if (cabeza->letra != ' ')
    {
        cout << cabeza->letra << " " << cabeza->peso << endl;
        archivo << cabeza->letra << " " << cabeza->peso << endl;
    }

    construirDiccionario(cabeza->izq, archivo);
    construirDiccionario(cabeza->der, archivo);
}
//Lee un archivo TXT con la estruc. Del árbol y va creando un nuevo nodo con el código y la letra
void creaNodoNuevo(char frase[80], int tam , int cont, nodo &nuevo){
   
    string a;
    for(int i = 0 ; i < tam ; i++){
        if(frase[i] > 49){
            nuevo.frecuencia = cont;
            nuevo.letra = frase[i];
        }
            
        else if (frase[i] == 48 || frase[i] == 49)
        {
            a = a + frase[i];
        }
        //cout<<a:
    }   
    //cout<<"\nAGREGANDO... " << a <<endl;
    nuevo.peso = a;
}
//Agregar nodo al final del arbol tipo lista
void pushFinal(arbol *&lista , nodo letra){
    nodo *nuevo = new nodo();
    nuevo->letra = letra.letra;
    nuevo->peso = letra.peso;
    nodo *aux = lista->head;
    nodo *aux2;
    while (aux != NULL)
    {
        aux2 = aux;
        aux = aux->sig;
    }
    if (lista->head == aux)
    {
        lista->head = nuevo;
    }
    else
    {
        aux2->sig = nuevo;
    }
    nuevo->sig = aux;
}
//Construye un arbol tipo lista a partir de la estructura leida de un .TXT
void leerDiccionario(arbol *lista , ifstream &archivo){
    char c[80];
    int t;
    int cont = 0;
    ofstream salida;
    nodo node;
    nodo prueba;
    while (true)
    {
        
        if(archivo.eof()) break;
        archivo.getline(c, 80, '\n');
        t = strlen(c);
        //cout << "\nfrase leida: " <<c << "  " << t << endl;
        
        creaNodoNuevo(c, t, cont, node);
        cont++;
        //cout<<"\nletra del nodo nuevo: "<<node.letra;
        //cout<<"\n codigo del nodo : "<<node.peso;
        pushFinal(lista, node);
        
    }
}
//Decodificar una cadena
void decodifica(string codi, arbol *clave){
    //cout<<"codigo: "<<codi<<endl;
    int l;
    l = codi.length();
    string cadena;
    string cadena2;
    for(int i = 0; i<l ; i++){
        cadena = cadena + codi[i];
        nodo *temp = clave->head;
        while (temp != NULL)
        {
            //cout<<temp->peso<<" "<< cadena <<endl;
            if (temp->peso == cadena)
            {
                //cout << "coincidencia";
                cadena = "";
                cadena2 = cadena2 + temp->letra;
                break;
            }
            temp = temp->sig;
        }
    }
    cout<<"CADENA DECODIFICADA: "<<cadena2<<endl;
}
int main(int argc , char *argv[])
{
    char c;
    int t = 52;
    letras v[t];
    llenarLetras(v); // construyendo lista de frecuencias vacia
    ifstream fe;
    fe.open("datos.txt");
    
    while(true){ 
        fe>>c;
        if (fe.eof()){break;} 
        cout << c <<" ";
        agregarletra(c, v); // Sumamos 1 por cada caracter
    }

    fe.close();
    verFrecuencias(v);
    ordenar(v); //ordenamos la lista de frecuencias 
    verFrecuencias(v);
    arbol *huffman; //creamos un arbol
    huffman = new arbol();
    agregarLetrasArbol(huffman,v); //creamos una lista enalazada de las letras
    verArbol(huffman); //mostramos la lista que hicimos en  el arbol
    while (huffman->head->sig != NULL)
    {
        insertarNuevo(huffman); //Creamos un nuevo nodo con la suma de los 2 primeros y lo agregamos a la lista
    }
    cout<<"\n::::::ARBOL:::::"<<endl;
    mostrarArbol(huffman->head, 0);
   
    cout<<"\n LLENARE PESOS... "<<endl; //coloca el codigo correspondiente a cada nodo
    huffman->head->peso = "";
    string anterior;
    llenaPesoArbol(huffman->head, anterior);
    cout<<endl;
    mostrarArbol(huffman->head, 0);

    int r;
    int tcha;
    string cadenaE;
    string cadenaD;
    ofstream MensajeEncriptado;
    ofstream diccionario;
    ifstream arbolCodificado;
    ifstream fraseEncriptada;
    nodo *listaLetras = new nodo();
    arbol *lista; 
    lista = new arbol();

    while (true)
    {   
        cout<< "\n\tMENU CODIGO HUFFMAN:"<<endl;
        cout << "\nELIGE OPCION: " << endl;
        cout << "1)Encriptar cadena" << endl;
        cout << "2)Desencriptar cadena" << endl;
        cout << "3)SALIR" << endl;
        cin >> r;
        switch (r)
        {
        case 1:
            MensajeEncriptado.open("msjEncrip.txt");
            encripta(huffman->head, cadenaE);
            cout<<"MENSAJE ENCRIPTADO: "<<cadenaE<<endl;
            diccionario.open("diccionario.txt");
            construirDiccionario(huffman->head,diccionario);
            diccionario.close();
            MensajeEncriptado << cadenaE;
            MensajeEncriptado.close();
            cadenaE = "";
            system("PAUSE");
            system("cls");
            break;
        case 2:
            fraseEncriptada.open("fraseEncriptada.txt");
            fraseEncriptada >> cadenaD;
            cout<<"CADENA OBTENIDA DEL FICHERO: "<<cadenaD<<endl;
            arbolCodificado.open("diccionario.txt");
            leerDiccionario(lista ,arbolCodificado);
            decodifica(cadenaD, lista);
            arbolCodificado.close();
            fraseEncriptada.close();
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            exit(1);
        default:
            break;
        }
    }
    return 0;
}