#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dfa.h"
//fungsi

int nomorState(char* namaState)
//mendapat nomor state dari nama state yang berformat (nomor)namaState
{
    //"001" = 0*100 + 0 * 10 + 1
    //"012" = 0*100 + 1 * 10 + 2
    int ratusan = (int)namaState[1] - 48;
    int puluhan = (int)namaState[2] - 48;
    int satuan = (int)namaState[3] - 48;
    return 100*ratusan+10*puluhan+satuan;
}
void initDFA(DFA *D,char *namaDaftarSimbol, char *namaDaftarState,char *namaStateAwal, char *namaTabel, char *namaFinishState,int turn)
//Load DFA dengan daftar state dan tabel transisinya, serta mengisi pula finish statenya
{
    bool baca;
    //baca daftar state
    FILE *fileDaftar = fopen(namaDaftarState, "r");
    baca = true;
    int nomor = 0;
    while (baca)
    {
        char dummy[23] = "";
        if (fscanf(fileDaftar, "%s", dummy) != EOF)
        {
            //Belum eof
            strcpy(Daftar(*D, nomor), dummy);
            nomor++;
        }
        else
        {
            //EOF
            baca = false;
        }
    }
    fclose(fileDaftar);
    //baca tabel transisi
    FILE *fileTabel = fopen(namaTabel, "r");
    baca = true;
    int bar = 0;
    while (baca)
    {
        char temp[9][23];
        if (fscanf(fileTabel, "%s %s %s %s %s %s %s %s %s", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]) != EOF)
        {
            //0 jika tidak pindah state
            for (int i = 0; i < 9; i++)
            {
                //cek apakah yang dibaca merupakan - atau nama state
                if (temp[i][0] == '-')
                {
                    //jika - maka tabel transisinya mengacu balik ke stateawal nya
                    State(*D, bar, i) = bar;
                }
                else
                {
                    State(*D, bar, i) = nomorState(temp[i]);
                }
            }
            bar += 1;
        }
        else
        {
            //EOF
            baca = false;
        }
    }
    fclose(fileTabel);
    //baca finish state
    FILE *fileFinish = fopen(namaFinishState, "r");
    baca = true;
    //assign semua false
    for (int i = 0; i < banyakState; i++)
    {
        Final(*D, i) = false;
    }
    while (baca)
    {
        char dummy[23];
        if (fscanf(fileDaftar, "%s", dummy) != EOF)
        {
            //Belum eof
            //Dapatkan nomor state
            int nomor = nomorState(dummy);
            Final(*D, nomor) = true;
        }
        else
        {
            //EOF
            baca = false;
        }
    }
    fclose(fileFinish);
    //Baca start State dari file external
    FILE *fileStart = fopen(namaStateAwal, "r");
    fscanf(fileStart, "%d",&Start(*D));
    fclose(fileStart);
    Current(*D) = Start(*D);
    //Baca daftar simbol
    FILE *fileSimbol = fopen(namaDaftarSimbol, "r");
    for(int i = 0;i< banyakTipeInput;i++)
    {
        fscanf(fileSimbol,"%d",&Simbol(*D,i));
    }
    fclose(fileSimbol);

    Turn(*D) = turn;
    for(int i = 0;i<7;i++){
        strcpy(StateDilewati(*D,i),"");
    }
}

void next(DFA *D, int X)
//DFA pindah ke state setelah diberi input X
{
    //Prekondisi : Input valid
    //Final : DFA pindah ke state yang sesuai setelah diberi input X
    Current(*D) = State(*D, Current(*D)-1, X-1); //-1 karena array dari 0
}

int getMove(DFA D)
//Mendapat move dari current state
{
    char state[23];
    strcpy(state, Daftar(D, Current(D)-1));  //-1 karena array dari 0
    return (int)state[strlen(state) - 1] - 48; //minus 48 karena '1' = 49
}

bool inputValid(DFA D,int input,PAPAN P)
//Mengecek apakah input valid
{
    //cek apakah berada di range 1-9
    bool valid = false;
    for(int i = 0;i<banyakTipeInput;i++)
    {
        if(Simbol(D,i) == input){
            valid = true;
            break;
        }
    }
    if (valid)
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