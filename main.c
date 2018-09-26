#include<stdio.h>
#include "dfa.h"
#include "game.h"

int main()
{
    int pilihan;
    printf("Selamat datang di permainan Tic-Tac-Toe\n");
    printf("Input 0 jika ingin cpu duluan, input 1 jika anda ingin mulai duluan\n");
    printf("Pilihanmu : ");
    scanf("%d",&pilihan);
    if(pilihan==0){
        DFA cpuFirst;
        initDFA(&cpuFirst,"State/daftarStates.txt","State/states.txt","State/finishState.txt",0);
        startGame(&cpuFirst,'O');
    }else{
        DFA playerFirst;
        initDFA(&playerFirst,"State/daftarStatesPlayer.txt","State/statesPlayer.txt","State/finishStatePlayer.txt",1);
        startGame(&playerFirst,'X');
    }
    return 0;
}