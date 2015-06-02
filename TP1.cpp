#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define MAX_EQUIPOS 100 // cantidad de equipos

using namespace std;

/* ******************************************************************
 *                     	   CONSTANTES
 * *****************************************************************/

enum  {
	Salir, // 0
	Agregar,// 1
	Eliminar,// 2
	Ver,// 3
};

/* ******************************************************************
 *                     	  TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
	char ID[4];
	char nombre[32];
	int PotAtaque;
	int PotDefensa;
} t_equipo;


/* ******************************************************************
 *                     	   PROTOTIPOS DE
 * 						     FUNCIONES
 * *****************************************************************/

void Pasar_Archivo_Vector(t_equipo[], int&);

void MenuPrincipal (t_equipo[], int&);

void Agregar_equipo(t_equipo[], int&);

void Ingresar_equipo (t_equipo&);

void Modificar_equipo(t_equipo[], int, t_equipo);

void Eliminar_equipo(t_equipo[], int&);

void Ver_equipo(t_equipo[], int);

void Grabar_Archivo (t_equipo[], int);


/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main (){

int cantequipos = 0;
t_equipo equipo[MAX_EQUIPOS];


	Pasar_Archivo_Vector (equipo, cantequipos);
	MenuPrincipal(equipo, cantequipos);
	Grabar_Archivo (equipo, cantequipos);

return 0;
}

/* ******************************************************************
 *                     		FUNCIONES
 * *****************************************************************/

void Pasar_Archivo_Vector (t_equipo vector[], int &cant){

t_equipo team;
FILE *archivo;
int i;

	archivo = fopen ("Equipos.bin", "a+b");

	if (archivo != NULL){
		
	fread (&team, sizeof(t_equipo),1,archivo);

		while (!feof(archivo)){

			vector[cant] = team;
			cant++;
			fread (&team, sizeof(t_equipo),1,archivo);
		}
	}
	if (cant < MAX_EQUIPOS){
		
		strcpy(team.ID, "000");
		team.PotAtaque = 0;
		team.PotDefensa = 0;
		
		for (i =cant; i <MAX_EQUIPOS; i++){
			
			vector[i] = team;
		}
	
	}
	
	fclose(archivo);
}

void MenuPrincipal (t_equipo vector[], int &cant){

int numero;

			cout<<"1. Agregar Equipo"<<endl;
			cout<<"2. Eliminar Equipo"<<endl;
			cout<<"3. Ver Equipo"<<endl;
			cout<<"0. Salir"<<endl;
			cout<<"Elija una opción: ";

			cin>>numero;

			switch (numero){

						case Agregar: 	cout<<endl;
										Agregar_equipo (vector, cant);
												break;
						case Eliminar: 	cout<<endl;
										Eliminar_equipo (vector, cant);
												break;
						case Ver: 		cout<<endl;
										Ver_equipo (vector, cant);
												break;
						case Salir: 	cout<<"Salir"<<endl;
												break;
						default:
										cout<<"Opción incorrecta"<<endl;
												break;
			}
			
		if (numero != 0){
			cout<<endl;
			MenuPrincipal(vector, cant);
		}
}


void Agregar_equipo (t_equipo vector[], int &cant){

t_equipo team;
int i;
bool existe = false;

		Ingresar_equipo (team);

		for (i =0; i <cant; i++){

			if (strcmp(vector[i].ID,team.ID) ==0){

				existe = true;
				Modificar_equipo(vector, i, team);
			}
		}

		if ((!existe) and (cant<MAX_EQUIPOS)){

			vector[cant] = team;
			cant++;
		}else{

			if ((!existe) and (cant>=MAX_EQUIPOS)){

				cout<<endl<<"Ya hay "<<MAX_EQUIPOS<<" equipos, no puede agregar más"<<endl;
			}

		}

}

void Ingresar_equipo (t_equipo &team){

		cout<<"Ingrese ID"<<endl;
		cin>>team.ID;
		cout<<"Ingrese nombre"<<endl;
		cin>>team.nombre;
		cout<<"Ingrese potencia de ataque"<<endl;
		cin>>team.PotAtaque;
		cout<<"Ingrese potencia de defensa"<<endl;
		cin>>team.PotDefensa;

}

void Modificar_equipo(t_equipo vector[], int posicion, t_equipo team){

char modificar;

		cout<<endl<<"Desea modificar el equipo S/N"<<endl;
		cin>>modificar;

		if (modificar == 'S'){

			vector[posicion] = team;
		}

}

void Eliminar_equipo (t_equipo vector[], int &cant){

char identificador[4];
int i, j;
bool existe = false;

		cout<<"Ingrese ID"<<endl;
		cin>>identificador;

		for (i =0; i <cant and !existe; i++){

				if (strcmp(vector[i].ID,identificador)==0){
						
					existe = true;

					for (j = i; j <cant; j++){

						vector[j] = vector[j+1];
					}
				}
		}

		if (!existe){
				cout<<endl<<"No existe el equipo que desea eliminar"<<endl;
		}else{
				cant--;
		}
}


void Ver_equipo (t_equipo vector[], int cant){

int i;
		if (cant >0){

			cout<<endl<<"Lista de equipos:"<<endl;

			for (i =0; i <cant; i++){
					
					cout<<endl;
					cout<<"ID equipo: "<<vector[i].ID<<endl;
					cout<<"Nombre equipo: "<<vector[i].nombre<<endl;
					cout<<"Potencia ataque equipo: "<<vector[i].PotAtaque<<endl;
					cout<<"Potencia defensa equipo: "<<vector[i].PotDefensa<<endl;
			}

		}else{

			cout<<endl<<"No hay equipos"<<endl;

		}
	
}

void Grabar_Archivo (t_equipo vector[], int cant){

int i;
t_equipo team;
FILE *archivo;

	archivo = fopen ("Equipos.bin", "wb");
	
	for (i = 0; i <cant; i++){

		team = vector[i];
		fwrite (&team, sizeof(t_equipo),1,archivo);

	}
	
	fclose(archivo);
}
