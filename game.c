#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "game.h"
#include "papan.h"

void startGame(DFA *D, char start)
//Memulai game dengan dfa D dan karakter awal start (X atau O)
{
    PAPAN game;
    int pilihan;
    if (start == 'X')
    {
        printf("Game dimulai, player harus menaruh di tengah\n");
    }
    else
    {
        printf("Game dimulai, cpu harus menaruh di tengah\n");
    }

    initPapan(&game, start);
    printBoard(game);
    Turn(*D) += 1; //Ganti turn
    while (!isFinal(*D) || !(Turn(*D)%2)) //Berhenti saat mencapai state final, menambah kondisi !Turn(*D)%2 agar cpu bisa mengeprint kondisi terakhir game
    {
        if (Turn(*D) % 2)
        {
            //jika 1, maka if akan true, menandakan giliran player skrng
            printf("Sekarang giliranmu, input angka 1-9 yang menandakan tempat di papan : ");
            scanf("%d", &pilihan);
            //Validasi input
            while (!inputValid(pilihan, game))
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
        //strcpy(StateDilewati(*D, Turn(*D)), Daftar(*D, Current(*D)));
        Turn(*D) += 1; //Ganti turn
    }
    //Catat state terakhir
    //strcpy(StateDilewati(*D, Turn(*D)), Daftar(*D, Current(*D)));
    //Game selesai, output hasil permainan
    int kondisiAkhir = cekMenang(game);
    if(kondisiAkhir==1){
        printf("CPU MENANG\n");
    }else if(kondisiAkhir==2){
        printf("PLAYER MENANG\n");
    }else if(kondisiAkhir==3){
        printf("DRAW\n");
    }
}
bool inputValid(int input, PAPAN P)
//Mengecek apakah input valid
{
    //cek apakah berada di range 1-9
    if (input >= 1 && input <= 9)
    {
        //cek apakah diletakan di tempat yang kosong
        int bar = (input - 1) / 3, kol = (input - 1) % 3;
        if (isi(P, bar, kol) == '_')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}