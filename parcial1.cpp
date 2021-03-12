#include <iostream>
#include <stdio.h>  
#include <string.h> 


using namespace std;
const char *nombe_archivo = "archivo.dat";

struct Trabajador{
	int codigo;
	char nombre[50];
	char apellido[50];
	float sueldo;
	
};

 void ingresar_trabajador();
void abrir_trabajador();
 void modificar_trabajador();
 void eliminar_indice();
 //void eliminar_trabajador();
int main (){
	abrir_trabajador();
 ingresar_trabajador();
	modificar_trabajador();
	eliminar_indice();
//	eliminar_trabajador();
	return 0;	
}
void buscar_codigo(){
	
	FILE* archivo = fopen(nombe_archivo, "rb");
	
	int indice=0,pos=0,cod=0;
	cout<<"BUSCAR CODIGO: ";
	cin>>cod;
	Trabajador trabajador;
	
	fread ( &trabajador, sizeof(trabajador), 1, archivo );
		
		do{
			
			if (trabajador.codigo == cod){
			pos = indice;
			}
	
		fread ( &trabajador, sizeof(Trabajador), 1, archivo );
		indice += 1;
		} while (feof( archivo ) == 0);
		
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Trabajador), SEEK_SET );

    fread ( &trabajador, sizeof( Trabajador ), 1, archivo );

    	cout << "Codigo: " << trabajador.codigo << endl;
        cout << "Nombre: " << trabajador.nombre << endl;
        cout << "Apellido: " << trabajador.apellido << endl;
        cout << "Sueldo (con bonificacion de Q.250.00) :" << trabajador.sueldo+250 << endl;
        cout << endl;
	
	fclose(archivo);
	system("PAUSE");
}


void buscar_indice(){
	FILE* archivo = fopen(nombe_archivo, "rb");
	
	int pos=0;
	cout<<"Que registro desea ver: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Trabajador), SEEK_SET );
	
	Trabajador trabajador;
	
    fread ( &trabajador, sizeof( Trabajador ), 1, archivo );

    	cout << "Codigo: " << trabajador.codigo << endl;
        cout << "Nombre: " << trabajador.nombre << endl;
        cout << "Apellido: " << trabajador.apellido << endl;
        cout << "Sueldo (con bonificacion de Q.250.00):  " << trabajador.sueldo+250 << endl;
        cout << endl;
	
	fclose(archivo);

	
}


void abrir_trabajador(){

	system("cls");
	FILE* archivo = fopen(nombe_archivo, "rb");
	if(!archivo) {
		archivo = fopen(nombe_archivo, "w+b");
	}
	Trabajador trabajador;
	int registro=0;
	fread ( &trabajador, sizeof(Trabajador), 1, archivo );
	cout<<"____________________________________________________________________"<<endl;
	cout << "id" <<"|"<< "CODIGO" <<"|"<< "NOMBRE"<<"| "<<"APELLIDO"<<"| "<<"SUELDO (con bonificacion de Q.250.00)"<<" "<<endl;	
		do{
		cout<<"____________________________________________________________________"<<endl;
		cout << registro <<" |  "<< trabajador.codigo <<" | "<< trabajador.nombre<<" |"<<trabajador.apellido<<"| "<<trabajador.sueldo+250<<endl;
        
        
	fread ( &trabajador, sizeof(Trabajador), 1, archivo );
		registro += 1;	
		} while (feof( archivo ) == 0);
		
    cout<<endl;
    
		fclose(archivo);
	}
void ingresar_trabajador(){
	
	char continuar;
	FILE* archivo = fopen(nombe_archivo, "ab"); // ab
	
	
		Trabajador trabajador;
		 string nombre,apellido;
		do{
			fflush(stdin);
			
		cout<<"Ingrese el Codigo:";
		cin>>trabajador.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(trabajador.nombre, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(trabajador.apellido, apellido.c_str()); 
		
		cout<<"Ingrese el sueldo:";
		cin>>trabajador.sueldo;
		cin.ignore();
		fwrite( &trabajador , sizeof(Trabajador), 1, archivo );
		
		
		cout<<"Desea Agregar otro Nombre s/n : ";
		cin>>continuar;
		} while((continuar=='s') || (continuar=='S') );
		
	
	fclose(archivo);
	abrir_trabajador();	
	buscar_codigo();
}
void modificar_trabajador(){
	
	FILE* archivo = fopen(nombe_archivo, "r+b");
	
		int id;
		string nombre,apellido;	
    	Trabajador trabajador;
    
		cout << "Ingrese el ID que desea Modificar: ";
    		cin >> id;
    		fseek ( archivo, id * sizeof(Trabajador), SEEK_SET );  
	
		cout<<"Ingrese el Codigo:";
		cin>>trabajador.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(trabajador.nombre, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(trabajador.apellido, apellido.c_str()); 
		 
		cout<<"Ingrese el sueldo:";
		cin>>trabajador.sueldo;
		cin.ignore();
		
		fwrite( &trabajador, sizeof(Trabajador), 1, archivo );
		
	fclose(archivo);
	abrir_trabajador();
		system("PAUSE");
}
void eliminar_indice()
{
	FILE* archivo = fopen(nombe_archivo, "rb");
	FILE * auxiliar=fopen("auxiliar.dat","wb");
	int indice;
	Trabajador trabajador;
	cout<<"Ingrese el indice a Eliminar: ";cin>>indice;
	fread(&trabajador,sizeof(Trabajador),1,archivo);
	int des= fseek(archivo,indice* sizeof(Trabajador), SEEK_SET);
	while(!feof(archivo))
	{
		fwrite(&trabajador,sizeof(Trabajador),1,auxiliar);
		if(des==indice)
		{
			int pos=ftell(auxiliar)*sizeof(Trabajador);
			fseek(auxiliar,pos,SEEK_SET);
		}
		fread(&trabajador,sizeof(Trabajador),1,archivo);
	}
	cout<<"Trabajador ELIMINADO"<<endl;
	fclose(archivo);
	fclose(auxiliar);
	remove("archivo.dat");
	rename("auxiliar.dat","archivo.dat");
}
