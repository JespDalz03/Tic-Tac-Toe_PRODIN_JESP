#include <iostream>

using namespace std;

// Declaración de funciones para modularizar el código
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(char tablero[3][3]);
bool realizarMovimiento(char tablero[3][3], int fila, int columna, char jugador);
bool verificarGanador(char tablero[3][3], char jugador);
bool verificarEmpate(char tablero[3][3]);

int main() {
    char continuar = 's';

    // Ciclo principal para permitir reiniciar el juego (Mejora opcional)
    while (continuar == 's' || continuar == 'S') {
        char tablero[3][3];
        char jugadorActual = 'X';
        bool juegoTerminado = false;
        int movimientos = 0;

        inicializarTablero(tablero);

        cout << "===================================\n";
        cout << "       BIENVENIDO AL TIC TAC TOE   \n";
        cout << "===================================\n";

        while (!juegoTerminado) {
            mostrarTablero(tablero);

            int casilla;
            cout << "Jugador " << jugadorActual << ", elige una casilla (1-9): ";
            cin >> casilla;

            // Validar que la entrada sea un número del 1 al 9
            if (casilla < 1 || casilla > 9) {
                cout << "¡Entrada invalida! Por favor elige un número entre 1 y 9.\n\n";
                continue;
            }

            // Convertir la casilla de 1-9 a coordenadas de la matriz [3][3]
            int fila = (casilla - 1) / 3;
            int columna = (casilla - 1) % 3;

            // Intentar realizar el movimiento validando si la casilla está libre
            if (realizarMovimiento(tablero, fila, columna, jugadorActual)) {
                movimientos++;

                // Verificar si el jugador actual ganó
                if (verificarGanador(tablero, jugadorActual)) {
                    mostrarTablero(tablero);
                    cout << "\n¡FELICIDADES! El jugador " << jugadorActual << " ha ganado la partida.\n";
                    juegoTerminado = true;
                }
                // Verificar si hay empate
                else if (verificarEmpate(tablero)) {
                    mostrarTablero(tablero);
                    cout << "\n¡Empate! El tablero esta lleno.\n";
                    juegoTerminado = true;
                }
                else {
                    // Cambiar de turno
                    jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
                }
            }
            else {
                cout << "¡Casilla ocupada! Elige otra.\n\n";
            }
        }

        cout << "\n¿Deseas jugar otra partida? (s/n): ";
        cin >> continuar;
        cout << "\n";
    }

    cout << "¡Gracias por jugar!\n";
    return 0;
}

// Inicializa el tablero con números del 1 al 9 para guiar al usuario
void inicializarTablero(char tablero[3][3]) {
    char contador = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = contador++;
        }
    }
}

// Muestra el tablero actual en pantalla con formato de cuadrícula
void mostrarTablero(char tablero[3][3]) {
    cout << "\n";
    cout << "  " << tablero[0][0] << " | " << tablero[0][1] << " | " << tablero[0][2] << " \n";
    cout << " ---+---+---\n";
    cout << "  " << tablero[1][0] << " | " << tablero[1][1] << " | " << tablero[1][2] << " \n";
    cout << " ---+---+---\n";
    cout << "  " << tablero[2][0] << " | " << tablero[2][1] << " | " << tablero[2][2] << " \n";
    cout << "\n";
}

// Valida y coloca la ficha en la matriz si la casilla está disponible
bool realizarMovimiento(char tablero[3][3], int fila, int columna, char jugador) {
    // Comprueba si la casilla aún muestra un número (no ha sido ocupada por 'X' u 'O')
    if (tablero[fila][columna] != 'X' && tablero[fila][columna] != 'O') {
        tablero[fila][columna] = jugador;
        return true;
    }
    return false;
}

// Comprueba todas las combinaciones posibles de victoria (filas, columnas y diagonales)
bool verificarGanador(char tablero[3][3], char jugador) {
    // Comprobar filas y columnas
    for (int i = 0; i < 3; i++) {
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
            return true;
        }
    }
    // Comprobar diagonales
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)) {
        return true;
    }
    return false;
}

// Verifica si ya no quedan casillas disponibles (empate)
bool verificarEmpate(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Si encuentra algún número del 1 al 9, el juego aún no se llena
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}