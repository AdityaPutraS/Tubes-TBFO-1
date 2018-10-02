#ifndef DFA_H
#define DFA_H

#include <stdbool.h>
#include "papan.h"

#define banyakState 120 //Maksimal banyak state
#define banyakTipeInput 9

typedef struct
{
    int tabelTransisi[banyakState][banyakTipeInput];
    char daftarState[banyakState][23];
    int start;
    bool final[banyakState];
    int curState;
    char stateDilewati[7][23];
    int turn;
} DFA;

//Selektor
#define State(D, S, I) (D).tabelTransisi[(S)][(I)]
#define Daftar(D, I) (D).daftarState[(I)]
#define Final(D,I) (D).final[(I)]
#define Current(D) (D).curState
#define Start(D) (D).start
#define isFinal(D) (D).final[Current(D)]
#define StateDilewati(D, I) (D).stateDilewati[(I)]
#define Turn(D) (D).turn

//fungsi
int nomorState(char *namaState);
//mendapat nomor state dari nama state yang berformat (nomor)namaState

void initDFA(DFA *D, char *namaDaftarState, char *namaTabel, char *namaFinishState,int turn);
//Load DFA dengan daftar state dan tabel transisinya, serta mengisi pula finish statenya

void next(DFA *D, int X);
//DFA pindah ke state setelah diberi input X

int getMove(DFA D);
//Mendapat move dari current state
#endif
