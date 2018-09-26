#ifndef GAME_H
#define GAME_H

#include "dfa.h"
#include "papan.h"

void startGame(DFA* D, char start);
//Memulai game dengan dfa D dan karakter awal start (X atau O)

bool inputValid(int input,PAPAN P);
//Mengecek apakah input valid

#endif