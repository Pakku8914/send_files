#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define recSize 1002 // 入力レコードの最大文字数 + 2(\n, \0)


// dataFile: 入力用ファイル名
// listFile: 出力用ファイル名
// keyPos:   keyカラムの開始桁位置
// keyLen:   keyカラムの開始桁数
// valuePos: valueカラムの開始桁位置
// valueLen: valueカラムの開始桁数
void outList (char *dataFile, char *listFile,
              int keyPos, int keyLen, int valuePos, int valueLen) {
    // ファイルポインタの定義
    FILE *inFile, *outFile;
    // inBuf: レコード全ての値
    // inKey: 読み込み中のkey名
    // key:   連続するkeyの保存
    // temp:  カラム一時保存用
    char inBuf[recSize], inKey[10], key[10], temp[10]; // (\n, \0)含めた配列
    // count: 同一カラム件数
    // inValue: 現在のvalueの保存
    // value: 同keyのvalueの保存
    long count, inValue, value;
    char format[] = " %9s %9ld %9ld\n"; // 出力フォーマット定義
    key[keyLen] = '\0';
    inKey[keyLen] = '\0';
    temp[keyLen] = '\0';
    outFile = fopen(listFile, "w"); // ファイルを書き込みモードで開く
    inFile = fopen(dataFile, "r");  // ファイルを読み込みモードで開く

    // レコードの読み出し
    if (fgets(inBuf,recSize, inFile) != NULL) { // レコードがある場合
        // keyにkey保存
        strncpy(key, inBuf + keyPos, keyLen);
        count = 1;
        // valueにvalue
        value = atol(strncpy(temp, inBuf + valuePos, valueLen));
        // レコードが取得できなくなるまでループ
        while (fgets(inBuf,recSize, inFile) != NULL) {
            // inKeyにkey保存
            strncpy(inKey, inBuf + keyPos, keyLen);
            // inValueにvalue保存
            inValue = atol(strncpy(temp, inBuf + valuePos, valueLen));
            if (strcmp(key, inKey) != 0) { // keyが違う場合
                // ファイルに，key，同一カラム件数，valueを出力
                fprintf(outFile, format, key, count, value);
                // カウント初期化
                count = 1;
                // keyの値を更新
                strcpy(key, inKey);
                // valueの値を更新
                value = inValue;
            }
            else { // keyが同じ場合
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

#define listLen 32 // 入力レコードの最大文字数+2 (\n, \0)

// listFile: DBファイル
void outListG (char *listFile) {
    // 入力ファイル
    FILE *inFile;
    // レコード
    char inBuf[listLen];
    // value: 現在の値
    // valueMax: valueの最大値
    long value, valueMax;
    // グラフ
    char graph[] = "*************************";

    inFile = fopen(listFile, "r"); // 読み込みモードでファイルを開く
    valueMax = 0;
    // 全てのレコードを読み込むループ
    while (fgets(inBuf,listLen, inFile) != NULL) {
        // 金額カラムをvalueに保存
        value = atol(inBuf + 21);
        // 最大値更新
        if (value > valueMax)
            valueMax = value;
    }
    // ファイル読み込み終了
    fclose(inFile);
    // ファイルを再読み込み
    inFile = fopen(listFile, "r");
    // 全てのレコードを読み込むループ
    while (fgets(inBuf, listLen, inFile) != NULL) {
        // 金額の読み込み
        value = atol(inBuf + 21);
        printf("%.30s, |%s\n", inBuf, &graph[25 - 25 * value / valueMax]);
    }
    fclose(inFile);
}
