#include <stdbool.h>
#include <stdio.h>
#include "papan.h"

void initPapan(PAPAN *P, char start)
//Init papan dengan 0 semua, giliran = true
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            isi(*P, i, j) = '_';
        }
    }
    isi(*P, 1, 1) = start;
}
void printBoard(PAPAN P)
//Print papan ke layar
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c ", isi(P, i, j));
        }
        printf("\n");
    }
}
int cekMenang(PAPAN P)
//return 0 jika belum ada yang menang,1 jika O menang, 2 jika X menang, 3 jika draw
{
    //Cek baris
    for (int i = 0; i < 3; i++)
    {
        if ((isi(P, i, 0) == isi(P, i, 1)) && (isi(P, i, 0) == isi(P, i, 2)))
        {
            char cek = isi(P, i, 0);
            if (cek == 'O')
            {
                return 1;
            }
            else if (cek == 'X')
            {
                return 2;
            }
        }
    }
    //Cek kolom
    for (int i = 0; i < 3; i++)
    {
        if ((isi(P, 0, i) == isi(P, 1, i)) && (isi(P, 0, i) == isi(P, 2, i)))
        {
            char cek = isi(P, 0, i);
            if (cek == 'O')
            {
                return 1;
            }
            else if (cek == 'X')
            {
                return 2;
            }
        }
    }
    //Cek diagonal
    if ((isi(P, 0, 0) == isi(P, 1, 1)) && (isi(P, 0, 0) == isi(P, 2, 2)))
    {
        char cek = isi(P, 0, 0);
        if (cek == 'O')
        {
            return 1;
        }
        else if (cek == 'X')
        {
            return 2;
        }
    }
    //Cari apakah ada yang kosong
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isi(P, i, j) == '_')
            {
                return 0;
            }
        }
    }
    //Jika sampai sini, berarti draw
    return 3;
}