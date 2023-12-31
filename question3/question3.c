#include <stdio.h>
#include <string.h>

#define ARRAY_MAX 100
#define NUM_DIGIT 9
#define NUM_DIGIT_TH_POWER_OF_TEN 1000000000

// length: data�z��̑傫��
// data[]: ���ʂ���9�����ɐ؂蕪���āC�v�f�ԍ��̏�����������l���i�[
typedef struct {
    int length;
    long data[ARRAY_MAX];
} MP;

// �����񂩂瑽�{�������������\���̂ɕϊ�
void set (MP *, const char []);
// ���{���������o�͂���
void print (const MP *);
// a + b = c ������
void add (const MP *, const MP *, MP *);

// num: MP�ŕ\�����ꂽ���{������
// str: ������ŕ\�����ꂽ���{������
void set (MP *num, const char str[]) {
    // str_idx: ���{�������̌����擾��index�ɂ�������
    // num_idx: index��
    // i: ���[�v�ϐ�
    // mul: ������̌���
    int str_idx = strlen(str) - 1;
    int num_idx = 0;
    int i;
    long mul;

    while (str_idx >= 0) { // ���������������[�v
        num->data[num_idx] = 0;
        // 1�̈�
        mul = 1;
        for (i = 0; i < NUM_DIGIT; i++) { // 9�����[�v
            // num_idx����mul���ڂ̒l�����Z
            num->data[num_idx] += mul * (str[str_idx--] - '0');
            // ���̈�
            mul *= 10;
        }
        num_idx++;
    }
    num->length = num_idx;
}

// num: MP�ŕ\�����ꂽ���{������
void print (const MP *num) {
    int i;

    // ��ԏ�̌���؂�܂ŏo��
    printf("%ld", num->data[num->length - 1]);
    // ��ԏ�̌���؂�ȊO�̌����o��
    for (i = num->length - 2; i >= 0; i--) {
        // �[���l�߂��ĕK��9���\������
        printf("%09ld", num->data[i]);
    }
    printf("\n");
}

// a, b, c: MP�ŕ\�����ꂽ���{������
// c != a, b
void add (const MP *a, const MP *b, MP *c) {
}
