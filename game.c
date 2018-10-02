#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "game.h"
#include "papan.h"

void startGame(DFA *D, char start)
//Memulai game dengan dfa D dan karakter awal start (X atau O)
{
    PAPAN game;
    int pilihan, noStateDilewati = 0;
    if (start == 'X')
    {
        printf("Game dimulai, player harus menaruh di tengah\n");
    }
    else
    {
        printf("Game dimulai, cpu harus menaruh di tengah\n");
    }
    //Catat state awal
    strcpy(StateDilewati(*D,noStateDilewati),Daftar(*D,Start(*D)-1));  //Isi -1 karena nomor State dimulai dari 1 dan indeksnya 0
    noStateDilewati += 1;
    initPapan(&game, start);
    printBoard(game);
    Turn(*D) += 1;               //Ganti turn
    while (cekMenang(game) == 0) //Berhenti saat game telah selesai
    {
        if (Turn(*D) % 2)
        {
            //jika 1, maka if akan true, menandakan giliran player skrng
            printf("Sekarang giliranmu, input angka 1-9 yang menandakan tempat di papan : ");
            scanf("%d", &pilihan);
            //Validasi input
            while (!inputValid(*D, pilihan, game))
            {
                printf("Input tidak valid, masukkan 1-9 dan di tempat yang kosong : ");
                scanf("%d", &pilihan);
            }
            //Sudah valid
            //pasang gerakan disana
            int bar = (pilihan - 1) / 3, kol = (pilihan - 1) % 3;
            isi(game, bar, kol) = 'X';
            //next state dfa
            next(D, pilihan);
            //Catat perubahan state
            strcpy(StateDilewati(*D,noStateDilewati),Daftar(*D,Current(*D)-1)); 
            //Current(*D)-1 karena nomor state dimulai dari 1, dan di indeks dimulai dari 0
            noStateDilewati += 1;
            //print papan ke layar
            printBoard(game);
        }
        else
        {
            //jika 0, maka if akan false, menandakan giliran komp skrng
            printf("Sekarang giliran cpu\n");
            //Dapatkan move paling optimal
            int optimal = getMove(*D);
            int bar = (optimal - 1) / 3, kol = (optimal - 1) % 3;
            isi(game, bar, kol) = 'O';
            //print papan ke layar
            printBoard(game);
        }
        Turn(*D) += 1; //Ganti turn
    }
    //Game selesai, output hasil permainan
    int kondisiAkhir = cekMenang(game);
    if (kondisiAkhir == 1)
    {
        printf("CPU MENANG\n");
    }
    else if (kondisiAkhir == 2)
    {
        printf("PLAYER MENANG\n");
    }
    else if (kondisiAkhir == 3)
    {
        printf("DRAW\n");
    }
    //Print semua state yang dilewati
    printf("State yang telah dilewati : \n");
    for (int i = 0; i < noStateDilewati; i++)    //Loop dari 0 sampai Turn(*D)-1 karena nilai Turn saat selesai adalah banyak state yang dilewati+1
    {  
        printf("%s\n",StateDilewati(*D,i));
    }
}