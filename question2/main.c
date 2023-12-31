#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define recSize 1002 // ���̓��R�[�h�̍ő啶���� + 2(\n, \0)


// dataFile: ���͗p�t�@�C����
// listFile: �o�͗p�t�@�C����
// keyPos:   key�J�����̊J�n���ʒu
// keyLen:   key�J�����̊J�n����
// valuePos: value�J�����̊J�n���ʒu
// valueLen: value�J�����̊J�n����
void outList (char *dataFile, char *listFile,
              int keyPos, int keyLen, int valuePos, int valueLen) {
    // �t�@�C���|�C���^�̒�`
    FILE *inFile, *outFile;
    // inBuf: ���R�[�h�S�Ă̒l
    // inKey: �ǂݍ��ݒ���key��
    // key:   �A������key�̕ۑ�
    // temp:  �J�����ꎞ�ۑ��p
    char inBuf[recSize], inKey[10], key[10], temp[10]; // (\n, \0)�܂߂��z��
    // count: ����J��������
    // inValue: ���݂�value�̕ۑ�
    // value: ��key��value�̕ۑ�
    long count, inValue, value;
    char format[] = " %9s %9ld %9ld\n"; // �o�̓t�H�[�}�b�g��`
    key[keyLen] = '\0';
    inKey[keyLen] = '\0';
    temp[keyLen] = '\0';
    outFile = fopen(listFile, "w"); // �t�@�C�����������݃��[�h�ŊJ��
    inFile = fopen(dataFile, "r");  // �t�@�C����ǂݍ��݃��[�h�ŊJ��

    // ���R�[�h�̓ǂݏo��
    if (fgets(inBuf,recSize, inFile) != NULL) { // ���R�[�h������ꍇ
        // key��key�ۑ�
        strncpy(key, inBuf + keyPos, keyLen);
        count = 1;
        // value��value
        value = atol(strncpy(temp, inBuf + valuePos, valueLen));
        // ���R�[�h���擾�ł��Ȃ��Ȃ�܂Ń��[�v
        while (fgets(inBuf,recSize, inFile) != NULL) {
            // inKey��key�ۑ�
            strncpy(inKey, inBuf + keyPos, keyLen);
            // inValue��value�ۑ�
            inValue = atol(strncpy(temp, inBuf + valuePos, valueLen));
            if (strcmp(key, inKey) != 0) { // key���Ⴄ�ꍇ
                // �t�@�C���ɁCkey�C����J���������Cvalue���o��
                fprintf(outFile, format, key, count, value);
                // �J�E���g������
                count = 1;
                // key�̒l���X�V
                strcpy(key, inKey);
                // value�̒l���X�V
                value = inValue;
            }
            else { // key�������ꍇ
                // b
                count++;
                value += inValue;
            }
        }
        // c
        fprintf(outFile, format, key, count, value);
    }
    fclose(inFile);
    fclose(outFile);
}

#define listLen 32 // ���̓��R�[�h�̍ő啶����+2 (\n, \0)

// listFile: DB�t�@�C��
void outListG (char *listFile) {
    // ���̓t�@�C��
    FILE *inFile;
    // ���R�[�h
    char inBuf[listLen];
    // value: ���݂̒l
    // valueMax: value�̍ő�l
    long value, valueMax;
    // �O���t
    char graph[] = "*************************";

    inFile = fopen(listFile, "r"); // �ǂݍ��݃��[�h�Ńt�@�C�����J��
    valueMax = 0;
    // �S�Ẵ��R�[�h��ǂݍ��ރ��[�v
    while (fgets(inBuf,listLen, inFile) != NULL) {
        // ���z�J������value�ɕۑ�
        value = atol(inBuf + 21);
        // �ő�l�X�V
        if (value > valueMax)
            valueMax = value;
    }
    // �t�@�C���ǂݍ��ݏI��
    fclose(inFile);
    // �t�@�C�����ēǂݍ���
    inFile = fopen(listFile, "r");
    // �S�Ẵ��R�[�h��ǂݍ��ރ��[�v
    while (fgets(inBuf, listLen, inFile) != NULL) {
        // ���z�̓ǂݍ���
        value = atol(inBuf + 21);
        printf("%.30s, |%s\n", inBuf, &graph[25 - 25 * value / valueMax]);
    }
    fclose(inFile);
}
