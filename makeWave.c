#include "makeWave.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979

int main(){
    WAV_HEAD wav;
    FILE* fp;
    long time;
    double hz = 0, s = 0, x = 0;
    char* filename;
    char filestring[19] = "%.1lfhz_%.1lfs.wav";
    short* wave;
    int strsize;
    char continueflug = 'Y';
    int needsize = 0;
    
    do{
        initalize(&wav);

        printf("hz:");
        scanf("%lf", &hz);
        printf("s:");
        scanf("%lf", &s);

        printf("ファイル名:");
        strsize = printf(filestring, hz, s);
        printf("\n");

        needsize = (int)(s * 8000);

        if ((filename = (char*)calloc(strsize + 1, sizeof(char))) == NULL) exit(1);
        sprintf(filename, filestring, hz, s);
        if ((fp = fopen(filename, "w")) == NULL) exit(1);

        if ((wave = (short*)calloc(needsize, sizeof(short))) == NULL) exit(1);

        for (time = 0; time < needsize; time++) {
            wave[time] = (short)(15000 * sin(2.0 * PI*time / (8000 / hz)));
        }

        wav.waveSize = needsize * 2;
        finalize(&wav);

        if(fwrite(&wav,sizeof(WAV_HEAD),1,fp) < 1){
            printf("ヘッダーの書き出しに失敗しました");
            exit(1);
        }
        if(fwrite(wave,sizeof(short),needsize,fp) < needsize){
            printf("波形情報の書き出しに失敗しました");
            exit(1);
        }

        printf("正常に書き出しが終了しました。");
        printf("続けますか？(Y/n)\n");
        getchar();
        continueflug = getchar();
    } while (toupper(continueflug) == 'Y');

    return 0;
}
