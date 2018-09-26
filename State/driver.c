#include <stdio.h>
#include <stdbool.h>

int main()
{
    FILE *fileTabel = fopen("statesPlayer.txt", "r");
    bool baca = true;
    int bar = 0;
    printf("OTW baca");
    while (baca)
    {
        char temp[9][22];
        if (fscanf(fileTabel, "%s %s %s %s %s %s %s %s %s",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8]) != EOF)
        {
            //0 jika tidak pindah state
            for(int i = 0;i<9;i++){
                printf("\n%s",temp[i]);
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
}