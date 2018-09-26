#ifndef BOARD_H
#define BOARD_H

#include<stdbool.h>

typedef struct{
    char data[3][3];
}PAPAN;

#define isi(P,R,C) (P).data[(R)][(C)]
#define giliran(P) (P).giliran

void initPapan(PAPAN* P,char start);
//Init papan dengan 0 semua, giliran = true
void printBoard(PAPAN P);
//Print papan ke layar
int cekMenang(PAPAN P);
//return 0 jika belum ada yang menang,1 jika O menang, 2 jika X menang, 3 jika draw
#endif