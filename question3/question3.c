#include <stdio.h>
#include <string.h>

#define ARRAY_MAX 100
#define NUM_DIGIT 9
#define NUM_DIGIT_TH_POWER_OF_TEN 1000000000

// length: data配列の大きさ
// data[]: 下位から9桁ずつに切り分けて，要素番号の小さい順から値を格納
typedef struct {
    int length;
    long data[ARRAY_MAX];
} MP;

// 文字列から多倍長整数を扱う構造体に変換
void set (MP *, const char []);
// 多倍長整数を出力する
void print (const MP *);
// a + b = c をする
void add (const MP *, const MP *, MP *);

// num: MPで表現された多倍長整数
// str: 文字列で表現された他倍長整数
void set (MP *num, const char str[]) {
    // str_idx: 多倍長整数の桁数取得をindexにしたもの
    // num_idx: index数
    // i: ループ変数
    // mul: 文字列の桁数
    int str_idx = strlen(str) - 1;
    int num_idx = 0;
    int i;
    long mul;

    while (str_idx >= 0) { // 文字数分だけループ
        num->data[num_idx] = 0;
        // 1の位
        mul = 1;
        for (i = 0; i < NUM_DIGIT; i++) { // 9桁ループ
            // num_idx区画のmul桁目の値を加算
            num->data[num_idx] += mul * (str[str_idx--] - '0');
            // 次の位
            mul *= 10;
        }
        num_idx++;
    }
    num->length = num_idx;
}

// num: MPで表現された多倍長整数
void print (const MP *num) {
    int i;

    // 一番上の桁区切りまで出力
    printf("%ld", num->data[num->length - 1]);
    // 一番上の桁区切り以外の桁を出力
    for (i = num->length - 2; i >= 0; i--) {
        // ゼロ詰めして必ず9桁表示する
        printf("%09ld", num->data[i]);
    }
    printf("\n");
}

// a, b, c: MPで表現された多倍長整数
// c != a, b
void add (const MP *a, const MP *b, MP *c) {
}
