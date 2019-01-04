#pragma once

typedef struct  {
    short formatID;
    short channelSize;
    int samplingLate;
    int dataSpeed;
    short blockSize;
    short bps;
} FMT;

typedef struct {
    char RIFF_HEAD[4];
    int fileSize;
    char WAVE_HEAD[4];
    char defineFormat[4];
    char fmtSize;
    FMT fmt;
    char DATA_CHUNK[4];
    int waveSize;
} WAV_HEAD;


WAV_HEAD* initalize(WAV_HEAD* wav){
    //initialization RIFF header
    wav->RIFF_HEAD[0] = 'R';
    wav->RIFF_HEAD[1] = 'I';
    wav->RIFF_HEAD[2] = 'F';
    wav->RIFF_HEAD[3] = 'F';

    //initialization WAVE header
    wav->WAVE_HEAD[0] = 'W';
    wav->WAVE_HEAD[1] = 'A';
    wav->WAVE_HEAD[2] = 'V';
    wav->WAVE_HEAD[3] = 'E';

    //initialization fmt header
    wav->defineFormat[0] = 'f';
    wav->defineFormat[1] = 'm';
    wav->defineFormat[2] = 't';
    wav->defineFormat[3] = ' ';

    //initialization fmtSize 
    wav->fmtSize = 16;

    //initialization fmt 
    //initialization formatID
    wav->fmt.formatID = 1;

    //initialization channelSize
    wav->fmt.channelSize = 1;

    //initialization samplingLate
    wav->fmt.samplingLate = 8000;

    //initialization bit per sec
    wav->fmt.bps =  16;

    //initialization blockSize
    wav->fmt.blockSize = wav->fmt.channelSize * wav->fmt.bps / 2;

    //initialization dataSpeed
    wav->fmt.dataSpeed = wav->fmt.samplingLate * wav->fmt.blockSize;

    //initialization DataChunck
    wav->DATA_CHUNK[0] = 'd';
    wav->DATA_CHUNK[1] = 'a';
    wav->DATA_CHUNK[2] = 't';
    wav->DATA_CHUNK[3] = 'a';

    return wav;
}

WAV_HEAD* finalize(WAV_HEAD* wav){
    //finalize fileSize
    wav->fileSize = 
        (int)sizeof(WAV_HEAD) + wav->waveSize - 8;

    return wav;
}