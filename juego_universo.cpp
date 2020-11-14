//autor Escalera walter samuel
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAXI 10000

using namespace std;

//Constantes
const int FILA=10;
const int COLUMNA=10;
const int MAXIMO=50;
const int MAX=50;

//Estrucutras
typedef int t_tablero[FILA][COLUMNA];
typedef char cadena[MAXIMO];// vector de caracteres
typedef struct persona{ //regidtro
				char nombre [MAXIMO];
                char apellido[MAXIMO];  
                char apodo[MAXIMO];
                int  cant_primo;
                int  cant_capicua;
				int  suma_primo;  
				int  suma_capicua;
                int puntaje;  
};

typedef persona t_jugador[MAX]; //un vector q guarda un registto
typedef persona t_seleccion_jugadores[MAX];// seleccion un jugador del registro persona 
typedef int t_atrapados[FILA*COLUMNA];// guarda los numero en el tablero


/*DECLRACION DE FUNCIONES Y PROCEDIMIENTOS**/
//Menu
void menu_princial(int &opc);
void menu_juego(int &opc);

//Tablero
void generar_tablero(t_tablero &t, int num);
bool verificar_repetidos(t_tablero t, int num);
void mostrar_tablero(t_tablero t);

//Persona
persona crear_jugador();

//Jugadores
void registrar_jugador(t_jugador &tj, int &ocup, persona p);
void mostrar_jugador(persona p);
void cambio(persona &x, persona &y);
void ordenar_jugadores(t_jugador &tj, int ocup);
void mostrar_jugadores(t_jugador tj,int ocup);
void seleccionar_jugadores(t_jugador tj,int ocup,t_seleccion_jugadores &tsj);
bool validar_seleccionado(t_seleccion_jugadores tsj, cadena apodo);

//Juego
int tirar_dado();
void turno_jugador(t_tablero t,t_seleccion_jugadores &tsj,int jugador, t_atrapados &ta, int &casillero, int &ocup_atrapados);
void calcular_puntaje(t_seleccion_jugadores &tsj,int jugador,int casillero, int d1, int d2);
int calcular_puntaje_dorado(t_seleccion_jugadores tsj, int jugador);

//Inicio de juego
void juego_cazadores(t_seleccion_jugadores &tsj,t_tablero &t, t_atrapados &ta, int &casillero, int &ocup_atrapado);

//Validacion de casilleros
int numero_amigo(int n);
bool capicua(int n);
bool primo(int n);
bool numero_perfecto(int n);

//Casiileros atrapados
void mostrar_atrapados(t_atrapados ta, int ocup_atrapados);
bool validar_repetidos_atrapados(t_atrapados ta, int num, int ocup_atrapados);

main(){
	int opc, num, ocup_tablero=-1,casillero, ocup_atrapados=-1; //vector vacio
	bool band1=false,band2=false;
	char resp;
	t_tablero t;
	t_jugador tj;
	t_seleccion_jugadores tsj;
	t_atrapados ta;
	do{
		system("cls");
		menu_princial(opc);
		switch(opc){
			system("cls");
			case 1:generar_tablero(t, num);
				   cout<<"\n Generando TABLERO ...\n TIC TAC TIC TAC TIC TAC \n [SUCCESS] TABLERO GENERADO!!!\n \n";
				   band1=true;
                   mostrar_tablero(t);
				break;
			case 2:if(band1){
                   	    do{
                   	        system("cls");
                            if(ocup_tablero != MAX-1){
                                cout<<"\n*************REGISTRO DE JUGADOR*************\n";
                                registrar_jugador(tj,ocup_tablero,crear_jugador());        
                                if(ocup_tablero != MAX-1){
									cout << "\n Desea cargar otro Jugador? [S/N]: " ;
	                                cin >> resp;
	                                resp=toupper(resp);
								}else{
									cout<<"\n No se puede Registrar mas Jugadores "<<endl;
								}
							}else{
				            	  cout<<"\n REGISTRO LLENO "<<endl;
							}
						}while(resp!='N' && ocup_tablero!= MAX-1);
                                ordenar_jugadores(tj,ocup_tablero);
				        }
					else{
				    	cout<<"\n[WARNING] Primero debe generar el tablero\n\n";
					}
				break;
			case 3:mostrar_jugadores(tj,ocup_tablero);
				   break;
			case 4:if(band1==true && ocup_tablero>=1){
						system("cls");  
						do{
							menu_juego(opc);
							switch(opc){
								case 1: seleccionar_jugadores(tj,ocup_tablero,tsj);
                                        band2=true;
										break;
								case 2: if(band2==true){
											juego_cazadores(tsj,t,ta,casillero,ocup_atrapados);
										}else{
											cout<<"\nPrimero debe elegir la opcion 1\n";
										}
										break;
								case 3: cout<<"\nHAS CUMPLIDO TU MISIÓN, PERO LA GUERRA CONTINUA ...\n";
										break;
								default: cout<<"\n[ERROR] Opcion Incorrecta!!!\n\n";
							}
							cout<<"\n";
                            system("pause");
                            system("cls"); 
						}while(opc!=3);
					}else{
				            if(band1==false){
				             	cout<<"\n[WARNING] Primero debe generar el tablero\n";
							}else{
								cout<<"\n[WARNING] Debe registrar al menos 2 jugadores\n";
							}
					}
					break;
			case 5: cout<<"\nSALVASTE AL MUNDO UNA VEZ!!! HURRA APU 2008\n";
				break;
			default: cout<<"\n[ERROR] Opcion Incorrecta!!!\n\n";
		}
		system("pause");
	}while(opc!=5);
	system("pause");
}


/* Menus**/
void menu_princial(int &opc){
 
  cout<<"\n****** PRINCIPAL ******"<<endl;
  cout<<"1- Generar Tablero"<<endl;
  cout<<"2- Registrar Jugadores"<<endl;
  cout<<"3- Listar Jugadores"<<endl;
  cout<<"4- Jugar"<<endl;
  cout<<"5- Salir"<<endl;
  cout<<"***********************"<<endl;
  cout<<"Elija una opcion: ";
  cin>>opc;     
}

void menu_juego(int &opc){
    cout<<"\n****** COMIENZA LA AVENTURA ******"<<endl;
    cout<<"1- Seleccionar Jugadores "<<endl;
    cout<<"2- Lanzamiento de Dado "<<endl;
    cout<<"3- Salir "<<endl;
    cout<<"**********************************"<<endl;
    cout<<"Elija una opcion: ";
    cin>>opc;
}

/*Tablero**/
void generar_tablero(t_tablero &t, int num){
    srand(time(NULL));
    for(int i=0;i<FILA;i++){
        for(int j=0;j<COLUMNA;j++){
            t[i][j]=1+rand()%9999; //metodo rand realiza numero aleatorio
            while(!verificar_repetidos(t,num)){
                  num=1+rand()%9999;
            }
           // t[i][j]=num;
        }
    }      
}
//verifica que en el tablero no se cargue valores repetidos
bool verificar_repetidos(t_tablero t, int num){
    for(int i=0;i<FILA;i++){
        for(int j=0;j<COLUMNA;j++){
            if(num==t[i][j]){
                return false;
            }
        }
    }
        return true;
}

//muestra el tablero con los datos cargados
void mostrar_tablero(t_tablero t){
    for(int i=0;i<FILA;i++){
        for(int j=0;j<COLUMNA;j++){
            cout<<" | "<<t[i][j];   //muestra los datos
        }
            cout<<"\n";
    }
}

/*Jugador**/
persona crear_jugador(){
   persona p;
   fflush(stdin);
   cout<<"\nApellido: ";
   gets(p.apellido);
   fflush(stdin);
   cout<<"\nNombre: ";
   gets( p.nombre);
   fflush(stdin);
   cout<<"\nApodo: ";
   gets (p.apodo);
   p.suma_primo=0;
   p.suma_capicua=0;
   p.cant_primo=0;
   p.cant_capicua=0;
   p.puntaje=0;
   
   return p;  
}

// Muestra el dato del jugador
void mostrar_jugador(persona p){
    cout<<"\nJUGADOR REGISTRADO\n"<<endl;
    cout<<"- Apellido: "<<p.apellido<<endl;                
    cout<<"- Nombre: "<<p.nombre<<endl;
    cout<<"- Apodo: "<<p.apodo<<endl;
    cout<<"- Puntaje: "<<p.puntaje<<endl;
}

//Registra jugador no repetido en el vector tj  
void registrar_jugador(t_jugador &tj, int &ocup, persona p){
        persona aux;
        bool existe=false;
        if(ocup==MAX-1)
        {
                cout<<"\n REGISTRO LLENO "<<endl;
        }else{         
                 if(ocup==-1){
                        ocup++;
                        tj[ocup]=p;
                        mostrar_jugador(p);
                 }else{
                        for(int i=0; i<=ocup; i++){
                                if(strcmp(tj[i].apellido,p.apellido)==0) {//copara dos valores
                                   if(strcmp(tj[i].nombre,p.nombre)==0){
                                       if(strcmp(tj[i].apodo,p.apodo)==0){
                                            existe = true;
                                            i=ocup;
                                        }
                                    }  
                                }
                        }
                        if(existe){
                                cout<<"\n JUGADOR EXISTENTE \n";
                                }else{
                                    ocup++;
                                    tj[ocup]=p;
                                    mostrar_jugador(p);
                        }
                }
        }
}

//Ordena jugadores por apellido
void ordenar_jugadores(t_jugador &tj, int ocup){  //metodo seleccion
        int i,j;
        for(i=0;i<=ocup-1;i++){
                for(j=i+1;j<=ocup;j++){
                        if(strcmp(tj[i].apellido, tj[j].apellido)>0){
                                cambio(tj[i],tj[j]);
                        }
                }
        }
}

//Metodo implementado por ordenar jugadores
void cambio(persona &x, persona &y){
	persona aux;
  	aux=x;
  	x=y;
  	y=aux;
}

//Muestra el vector de jugadores
void mostrar_jugadores(t_jugador tj,int ocup){
int i;
 if (ocup==-1)
   cout << "NO SE REGISTRARON JUGADORES" << endl;
 else  
  for(i=0;i<=ocup;i++)
    {
      cout<<"\n JUGADOR REGISTRADO ["<<i+1<<"]"<<endl;    
      cout<<"\tApellido: "<<tj[i].apellido<<endl;                
      cout<<"\tNombre: "<<tj[i].nombre<<endl;
      cout<<"\tApodo: "<<tj[i].apodo<<endl;
      cout<<"\tPuntaje: "<<tj[i].puntaje<<endl;
      cout << endl;  
    }
}

/*JUEGO**/
//Selecciona dos jugadores del vector jugadores por apodo
void seleccionar_jugadores(t_jugador tj,int ocup,t_seleccion_jugadores &tsj){
        int i,j=1,k=0;
        char apodo[MAXI];
        bool band=false;
        do{
        	    fflush(stdin); //realiza la limpieza bufer de entrada
                cout<<"\nIngrese apodo del "<<j<<" jugador: ";
                gets(apodo);
                cout<<"\napodo:"<<apodo<<endl; //muestra el apodo ingresado
                for(i=0; i<=ocup; i++){
                        if(strcmp(tj[i].apodo,apodo)==0){
                                if(validar_seleccionado(tsj, apodo)){
                                        cout << "\nEl jugador ya esta seleccionado\n";
                                }else{
                                        tsj[k]=tj[i];
                                        k++;
                                        j++;
                                        band=true;
                                }
                        }
                }
                if(!band){
                        cout<<"\nNo existe el jugador con ese apodo!!\n";
                }else{
                        cout<<"\nJugador Seleccionado!!\n";
                        band=false;
                }
        }while(j!=3);
}

//Metodo implementado para validar jugadores existente
bool validar_seleccionado(t_seleccion_jugadores tsj, cadena apodo){
        if(strcmp(tsj[0].apodo, apodo)==0){
                return true;
        }else{
                return false;
        }
}

//Genera  un valor desde 0-9
int tirar_dado(){
    return rand()%10;
}

//Calcula el puntaje a partir de un numero("casillero") capturado de la tabla
void calcular_puntaje(t_seleccion_jugadores &tsj,int jugador,int casillero, int d1, int d2){
	int total=0;
  		if(primo(casillero)&&capicua(casillero)&&d1==d2){
			total=total+(casillero*4);
			tsj[jugador].suma_primo+= casillero;
			tsj[jugador].suma_capicua+= casillero;
			tsj[jugador].cant_capicua++;
			tsj[jugador].cant_primo++;
			cout<<" (PRIMO) (CAPICUA) (DIAGONAL PRINCIPAL)\n";
		}else{
		    if(primo(casillero)&&capicua(casillero)){
				total=total+(casillero*3);
				tsj[jugador].suma_primo+= casillero;
				tsj[jugador].suma_capicua+= casillero;
				tsj[jugador].cant_capicua++;
				tsj[jugador].cant_primo++;
				cout<<" (PRIMO) (CAPICUA)\n";
			}else{
				if(d1==d2){
					if(primo(casillero)){
						tsj[jugador].suma_primo+= casillero;
						tsj[jugador].cant_primo++;
						cout<<" (PRIMO) ";
					}else{
						if(capicua(casillero)){
							tsj[jugador].suma_capicua+= casillero;
							tsj[jugador].cant_capicua++;
							cout<<" (CAPICUA) ";
						}
					}
					total=total+(casillero*2);
					cout<<" (DIAGONAL PRINCIPAL)\n";
				}else{
					if(primo(casillero)){
						total=total+casillero;
				    	tsj[jugador].suma_primo+= casillero;
				    	tsj[jugador].cant_primo++;
				    	cout<<" (PRIMO)\n";
					}else{
						if(capicua(casillero)){
							total=total+casillero;
							tsj[jugador].cant_capicua++;
							tsj[jugador].suma_capicua+= casillero;
							cout<<" (CAPICUA)\n";
						}
					}
				}	
			}	
		}
	tsj[jugador].puntaje+=total;
	cout<<"\nPuntaje: "<<tsj[jugador].puntaje<<endl;
}

//Realiza un turno por jugador, dependiendo si tiene un N° amigo en la tabla  o es N° perfercto obtendra turno adicionales
void turno_jugador(t_tablero t,t_seleccion_jugadores &tsj,int jugador, t_atrapados &ta, int &casillero, int &ocup_atrapados){
	bool band=true;
	int c_tiros=0;
	do{
		if(c_tiros!=3){
			int d1,d2;
			d1=tirar_dado();
			d2=tirar_dado();
			system("cls");
			cout<<"                JUGADOR "<<tsj[jugador].apodo<<"\nLanzando dados ...\n";
			cout<<"\nDado 1: "<<d1<<" - Dado 2: "<<d2<<endl;
			casillero=t[d1][d2];
		  	cout<<"\nNumero Encontrado: "<<casillero;
		  	if(!validar_repetidos_atrapados(ta,casillero,ocup_atrapados)){
		  		ocup_atrapados++;
		  		ta[ocup_atrapados]=casillero;
		  		calcular_puntaje(tsj,jugador,casillero,d1,d2);
		  		band=false;
		  		if(ocup_atrapados!=(FILA*COLUMNA)-1){
				  	if(!verificar_repetidos(t,numero_amigo(casillero))){  //numero amigo
		  				cout<<"\nTiene un numero amigo '"<<numero_amigo(casillero)<<"'\n";
		  				system("pause");
		  				d1=tirar_dado();
						d2=tirar_dado();
						system("cls");
						cout<<"\nTiene un tiro mas por numero amigo!!!\n";
						cout<<"                JUGADOR "<<tsj[jugador].apodo<<"\nLanzando dados ...\n";
						cout<<"\nDado 1: "<<d1<<" - Dado 2: "<<d2<<endl;
						casillero=t[d1][d2];
					  	cout<<"\nNumero Encontrado: "<<casillero;
					  	if(!validar_repetidos_atrapados(ta,casillero,ocup_atrapados)){
					  		ocup_atrapados++;
					  		ta[ocup_atrapados]=casillero;
					  		calcular_puntaje(tsj,jugador,casillero,d1,d2);
					  	}else{
					  		cout<<"\nEl numero no esta en juego, perdio su turno\n";
						}
				  	}
				}else{
					if(ocup_atrapados!=(FILA*COLUMNA)-2){ //tiro por numero perfecto
						if(numero_perfecto(casillero)){
			  				cout<<"\nEs un numero perfecto, tiene dos tiros!!!"<<endl;
			  				d1=tirar_dado();
							d2=tirar_dado();
							system("cls");
							cout<<"\nPrimer tiro!!!\n";
							cout<<"                JUGADOR "<<tsj[jugador].apodo<<"\nLanzando dados ...\n";
							cout<<"\nDado 1: "<<d1<<" - Dado 2: "<<d2<<endl;
							casillero=t[d1][d2];
						  	cout<<"\nNumero Encontrado: "<<casillero;
							  	if(!validar_repetidos_atrapados(ta,casillero,ocup_atrapados)){
							  		ocup_atrapados++;
							  		ta[ocup_atrapados]=casillero;
							  		calcular_puntaje(tsj,jugador,casillero,d1,d2);
							  	}else{
							  		cout<<"\nEl numero no esta en juego, perdio un turno\n";
								}
								c_tiros++;
								d1=tirar_dado();
								d2=tirar_dado();
								system("cls");
								cout<<"\Segundo tiro!!!\n";
								cout<<"                JUGADOR "<<tsj[jugador].apodo<<"\nLanzando dados ...\n";
								cout<<"\nDado 1: "<<d1<<" - Dado 2: "<<d2<<endl;
								casillero=t[d1][d2];
							  	cout<<"\nNumero Encontrado: "<<casillero;
								  	if(!validar_repetidos_atrapados(ta,casillero,ocup_atrapados)){
								  		ocup_atrapados++;
								  		ta[ocup_atrapados]=casillero;
								  		calcular_puntaje(tsj,jugador,casillero,d1,d2);
								  	}else{
								  		cout<<"\nEl numero no esta en juego, perdio un turno\n";
									}
								c_tiros++;
				  		}
					}
				}
				band=false;
			}else{
				if(ocup_atrapados!=(FILA*COLUMNA)-1){
					cout<<"\nVuelve a Tirar!!!\n";
					c_tiros++;
				}else{
					cout<<"\nNo tiene mas tiros\n";
					band=false;
				}
			}
			system("pause");
		}else{
			cout<<"\nTres intenetos fallidos se le descontaran -10pt\n";
			tsj[jugador].puntaje-=10;
			band=false;
			system("pause");
		}
	}while(band);
	cout<<"\n";
	mostrar_atrapados(ta,ocup_atrapados);
}


//Valida si el numero no esta capturado por otro jugador 
bool validar_repetidos_atrapados(t_atrapados ta, int num, int ocup_atrapados){
	bool band=false;
	if(ocup_atrapados==-1){
		band=false;
	}else{
		for(int i=0;i<=ocup_atrapados && band==false;i++){
			if(ta[i]==num){
				band=true;
			}
		}
	}
	return band;
}

/* METODO PRINCIPAL**/
//Metodo permite empezar el juegp  
void juego_cazadores(t_seleccion_jugadores &tsj,t_tablero &t, t_atrapados &ta, int &casillero, int &ocup_atrapado){
	
	do{
		if(ocup_atrapado!=(FILA*COLUMNA)-1){ //primer jugador
			turno_jugador(t,tsj,0,ta,casillero,ocup_atrapado);
		}
		if(ocup_atrapado!=(FILA*COLUMNA)-1){ //segundo jugador
			turno_jugador(t,tsj,1,ta,casillero,ocup_atrapado);
		}
	}while(ocup_atrapado!=(FILA*COLUMNA)-1);
	
	if(calcular_puntaje_dorado(tsj,0)>calcular_puntaje_dorado(tsj,1)){
		system("cls");
		cout<<"************************************************************\n";
		cout<<tsj[0].apodo<<" WINS!!! -> Puntaje "<< calcular_puntaje_dorado(tsj,0)<<endl;
		cout<<"Ganador/a: "<<tsj[0].nombre<<" "<<tsj[0].apellido<<endl;
		cout<<"************************************************************\n";
		//cout<<"Puntaje: "<<tsj[0].puntaje<<endl;
	}else{
		system("cls");
		cout<<"************************************************************\n";
		cout<<tsj[1].apodo<<" WINS!!! -> Puntaje "<< calcular_puntaje_dorado(tsj,1)<<endl;
		cout<<"Ganador/a: "<<tsj[1].nombre<<" "<<tsj[1].apellido<<endl;
		cout<<"************************************************************\n";
		//cout<<"Puntaje: "<<tsj[1].puntaje<<endl;
	}
}

//Calcula el puntaje dorado
int calcular_puntaje_dorado(t_seleccion_jugadores tsj, int jugador){
	//Relazia el calculo del puntaje dorado de un jugador
	int total=((tsj[jugador].suma_primo*0.2)+(tsj[jugador].suma_capicua*0.3))+((tsj[jugador].suma_primo+tsj[jugador].suma_capicua)*0.5);
	return total;
}

//Muestra el vector de los numeros atrapado del tablero
void mostrar_atrapados(t_atrapados ta, int ocup_atrapados){
	for(int i=0; i<=ocup_atrapados; i++){
		cout<<ta[i]<<"|";
	}
}

/*VALIDACION DE NUMERO ("CASILLEROS")**/
//Devuelve un numero amigo que se encuentra en la tabla
int numero_amigo(int n){
	int suma=0;
	for(int i=1;i<n;i++){
		if(n %i==0) {
			suma=suma+i;
		}
	}
	return suma;
}

//Retorna si un numero es capicua o no
bool capicua(int n){
    int cap=n;
    int resto=0;
	int invertido=0;
   while(cap>0){
   	    resto=cap%10;
	    cap=cap/10;
	    invertido=invertido*10+resto; 
   }	

  if (n==invertido){
  	return true;
  }else{
  	return false;
  }
  
}

//Verifica si un numero es primo
bool primo(int n){
 if (n <= 1)
 return false;
 	for (int i = 2; i*i <= n; ++i) 
      if (n%i == 0) return false;
 return true;
}

//Verifica si un numero es perfecto o no
bool numero_perfecto(int n){
	 int i,mo, s=0;
	for(i=n;i>=1;i--){
	  mo=n%i;
	  if(mo==0 && i!=n){
	   s=s+i;
	  }
	 }
	 if(s==n){
	  return true;
	 }else{
	  return false;
	 }
}
