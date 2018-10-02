#include<stdio.h>
#include "dfa.h"
#include "game.h"

int main()
{
    int pilihan;
    printf("Selamat datang di permainan \n");
    printf("'########:'####::'######:::::'########::::'###:::::'######:::::'########::'#######::'########:\n");
    printf("... ##..::. ##::'##... ##::::... ##..::::'## ##:::'##... ##::::... ##..::'##.... ##: ##.....::\n");
    printf("::: ##::::: ##:: ##:::..:::::::: ##:::::'##:. ##:: ##:::..:::::::: ##:::: ##:::: ##: ##:::::::\n");
    printf("::: ##::::: ##:: ##::::::::::::: ##::::'##:::. ##: ##::::::::::::: ##:::: ##:::: ##: ######:::\n");
    printf("::: ##::::: ##:: ##::::::::::::: ##:::: #########: ##::::::::::::: ##:::: ##:::: ##: ##...::::\n");
    printf("::: ##::::: ##:: ##::: ##::::::: ##:::: ##.... ##: ##::: ##::::::: ##:::: ##:::: ##: ##:::::::\n");
    printf("::: ##::::'####:. ######:::::::: ##:::: ##:::: ##:. ######:::::::: ##::::. #######:: ########:\n");
    printf(":::..:::::....:::......:::::::::..:::::..:::::..:::......:::::::::..::::::.......:::........::\n");
    printf("Input 0 jika ingin cpu duluan, input 1 jika anda ingin mulai duluan\n");
    printf("Pilihanmu : ");
    scanf("%d",&pilihan);
    if(pilihan==0){
        DFA cpuFirst;
        initDFA(&cpuFirst,"State/daftarSimbol.txt","State/daftarStates.txt","State/stateAwal.txt","State/states.txt","State/finishState.txt",0);
        startGame(&cpuFirst,'O');
    }else{
        DFA playerFirst;
        initDFA(&playerFirst,"State/daftarSimbol.txt","State/daftarStatesPlayer.txt","State/stateAwalPlayer.txt","State/statesPlayer.txt","State/finishStatePlayer.txt",1);
        startGame(&playerFirst,'X');
    }
    return 0;
}
