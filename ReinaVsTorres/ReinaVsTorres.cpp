// Enunciado:
// Realizar un programa C++ que genere los movimientos posibles 
// (según las reglas del ajedrez) de una Reina amenazada por dos Torres enemigas
//
//
// Participantes:
// 1- John Luis Del Rosario Sánchez - ID 1106940
// 2- Ashly Marisell Paula Ynoa - ID 1108023
// 3- Elián Matos Díaz - ID 1106901
// 4- Juan Daniel Ubiera Méndez - ID 1107248
// 5- Kelvin Arístides García Espinal - ID 1107646


#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int lim_infx = 0, lim_supx = 7, lim_infy = 0, lim_supy = 7; //limites superiores e inferiores tanto en X como en Y
const int TABLERO_WIDTH = 8; //ancho del tablero
const int TABLERO_HEIGHT = 8; // altura del tablero
char tablero[TABLERO_HEIGHT][TABLERO_WIDTH], //tablero 8x8, primero tiene la altura y luego el ancho para facilitar su despliegue
letterToInt[8][2] = { {'a','1'},{'b','2'},{'c','3'},{'d','4'},{'e','5'},{'f','6'},{'g','7'},{'h','8'} };
//diccionario para convertir la letra al su numero correspondiente en el tablero


void MovimientoReina(int x, int y, int i, int j, int torres[2][2]) {
	int movX, movY; //el origen del movimiento
	movX = x + i; //direccion del movimiento en x
	movY = y + j; //direccion del movimiento en y
	if (movX < lim_infx || //validacion limite inferior en x
		movX > lim_supx || //validacion limite superior en x
		movY < lim_infy || //validacion limite inferior en y
		movY > lim_supy || //validacion limite superior en y
		(movX == torres[0][0] && movY == torres[0][1]) || //si el movimiento termina en una torre (evitar saltar torres)
		(movX == torres[1][0] && movY == torres[1][1])) return;

	if (movX == torres[0][0] || movX == torres[1][0] || movY == torres[0][1] || movY == torres[1][1]) { //si se encuentra amenazada
		tablero[movY][movX] = 'X';
	}
	else {
		tablero[movY][movX] = 'V';
	}

	MovimientoReina(movX, movY, i, j, torres); //recursion: seguir en la direccion del movimiento
}

void MostrarTablero() {
	cout << "    A   B   C   D   E   F   G   H" << endl; //letras de las colummnas
	cout << "  +---+---+---+---+---+---+---+---+" << endl;//barra superior
	for (int h = 0; h < TABLERO_HEIGHT; h++) {
		cout << h + 1 << " | "; //numero de las filas

		for (int w = 0; w < TABLERO_WIDTH; w++) {
			if (tablero[h][w] != ' ') {
				cout << tablero[h][w] << " | ";
				continue;
			}
			cout << "  | ";
		}

		cout << endl << "  +---+---+---+---+---+---+---+---+" << endl;
	}
}

void ReiniciarTablero() { //todos los valores del tablero se convierten en ' ', tambien sirve para iniciar el tablero
	for (int h = 0; h < TABLERO_HEIGHT; h++) {
		for (int w = 0; w < TABLERO_WIDTH; w++) {
			tablero[h][w] = ' ';
		}
	}
}

int CharToInt(char c) { //parse de caracter a entero
	return int(c - '0');
}

bool Validar(string str) { //validar input del usuario
	str[0] = tolower(str[0]); //convertir a minuscula la columna

	//validaciones
	if (str.length() != 2 || isdigit(str[0]) || (isdigit(str[1]) == false) || int(str[0]) < 97 || int(str[0]) > 104 || (str[1] - '0') < 1 || (str[1] - '0') > 8) {
		cout << "Fomato incorrecto, asegurese de insertar primero una letra de la A a la H y numeros del 1 al 8" << endl;
		ReiniciarTablero();
		system("PAUSE");
		return false;
	}

	return true;
}

void EditarPosicion(string str, int arr[2]) {

	for (int i = 0; i < TABLERO_WIDTH; i++) { //convertir la columna insertada a su equivalente en el tablero
		if (letterToInt[i][0] == str[0]) {
			str[0] = letterToInt[i][1];
		}
	}

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		arr[i] = CharToInt(str[i]) - 1;
	}
}

void RecorridosReina(int reina[2], int torres[2][2]) { //realiza los 8 recorridos de la reina
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (j == 0 && i == 0) continue;
			MovimientoReina(reina[0], reina[1], i, j, torres);
		}
	}
}


int main()
{
	ReiniciarTablero();//iniciar el tablero con espacios vacios
	do {
		system("CLS");

		int torres[2][2];//array bidimensional para la posicion de ambas torres
		int reina[2]; //posicion de la reina
		string input; //cadena insertada por teclado

		MostrarTablero(); //desplegar el tablero

		cout << "Inserte la posicion de la primera torre (ej. d3, D3): "; //pedir y validar posicion
		cin >> input;
		if (!Validar(input)) continue;
		EditarPosicion(input, torres[0]);//cambiar valores en el array

		tablero[torres[0][1]][torres[0][0]] = 'T'; //agregar torre al tablero

		cout << "Inserte la posicion de la segunda torre (ej. d3, D3): "; //pedir y validar posicion
		cin >> input;
		if (!Validar(input)) continue;
		EditarPosicion(input, torres[1]);//cambiar valores en el array

		if (torres[0][0] == torres[1][0] && torres[0][1] == torres[1][1]) { //verificar que las posiciones son distintas
			cout << "Dos torres no pueden ocupar el mismo lugar" << endl;
			system("PAUSE");
			ReiniciarTablero();
			continue;
		}

		tablero[torres[1][1]][torres[1][0]] = 'T'; //agregar torre al tablero

		cout << "Inserte la posicion de la Reina (ej. d3,D3): "; //pedir y validar posicion
		cin >> input;

		if (!Validar(input)) continue;

		EditarPosicion(input, reina);//cambiar valores en el array

		tablero[reina[1]][reina[0]] = 'R';

		if ((torres[0][0] == reina[0] && torres[0][1] == reina[1]) || (torres[1][0] == reina[0] && torres[1][1] == reina[1])) {
			cout << "La reina no puede ocupar el mismo lugar de una torre" << endl;
			system("PAUSE");

			ReiniciarTablero();
			continue;
		}

		RecorridosReina(reina, torres); //calculos de cada posicion de la reina
		MostrarTablero();

		cout << "Desea reiniciar el tablero?\n(1)Si\n(2)No\n>>"; //menu de cerrar el programa o seguir
		cin >> input;
		if (input == "1") continue;
		else if (input == "2") break;
		else {
			cout << "Valor invalido, reiniciando el programa" << endl;
			ReiniciarTablero();
			system("PAUSE");
		}
	} while (true);

}
