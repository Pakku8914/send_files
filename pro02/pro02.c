#include <stdio.h>


typedef struct {
    /* data */
    char pr_code[9];  // �J���R�[�h
    int job_term;     // �J����Ɠ���
    int target_term;  // �ڕW��Ɗ���
} JOB;


void job_scheduling (int, JOB [], int []);
void print_schedule (int num_s, JOB job[num_s], int job_sch[num_s]);

// num_s: �T�u�V�X�e����
// job: �T�u�V�X�e�����
// job_sch: �J����Ə���
void job_scheduling (int num_s, JOB job[num_s], int job_sch[num_s]) {
    int ft,          // i�Ԗڂ܂ł̊J����Ɠ����̍��v
        ft_a, ft_b,  // (i - 1)�Ԗڂ܂ł̊J����Ɠ����̍��v
        wt_a,        // ������2�̒x�������̍��v
        wt_b,        // �t����2�̒x�������̍��v
        job_no,      // �d���̔ԍ�
        i, j;        // ���[�v�p�ϐ�

    // job�̏��Ԃ�ۑ�
    for (i = 0; i < num_s; i++)
        job_sch[i] = i;

    ft = 0;  // �J����Ɠ����̍��v�l��������
    i = 0;   // ���[�v�ϐ���������

    while (i < num_s - 1) {  // �T�u�V�X�e���������[�v
        // (i - 1)�Ԗڂ܂ł̊J����Ɠ�������
        ft_a = ft;
        ft_b = ft;
        // 2��JOB�̒x������������
        wt_a = 0;
        wt_b = 0;

        for (j = 0; j < 2; j++) {  // �x�������̍��v wt_a, wt_b�����߂�
            // (i - 1)�Ԗڂ܂ł̍�Ɠ������v�l��(i + j)�Ԗڂ̍�Ɠ��������Z
            ft_a += job[job_sch[i + j]].job_term;  // ����
            // �ڕW��Ɗ��Ԃ��߂��Ă�����
            if (ft_a > job[job_sch[i + j]].target_term)
                // �x�����������Z
                wt_a += ft_a - job[job_sch[i + j]].target_term;
            // (i - 1)�Ԗڂ܂ł̍�Ɠ������v�l��(i + 1 - j)�Ԗڂ̍�Ɠ��������Z
            ft_b += job[job_sch[i + 1 - j]].job_term;  // �t��
            // �ڕW��Ɗ��Ԃ��߂��Ă�����
            if (ft_b > job[job_sch[i + 1 - j]].target_term)
                // �x�����������Z
                wt_b = ft_b - job[job_sch[i + 1 - j]].target_term;
        }
        // �x��������r
        if (wt_a > wt_b) {  // �����̕����x�������������ꍇ
            // ���Ԃ̓���ւ� ###############
            job_no = job_sch[i];
            job_sch[i] = job_sch[i + 1];
            job_sch[i + 1] = job_no;
            // ############################

            if (i > 0)
                // i��1���炵�A�J����Ɠ����̍��v�l����i-1�Ԗڂ̊J����Ɠ��������Z
                ft -= job[job_sch[--i]].job_term;
        }
        else
            ft += job[job_sch[i++]].job_term;
    }
}

void print_schedule (int num_s, JOB job[num_s], int job_sch[num_s]) {
    int ft, wt, wt_sum, i;

    ft = 0;
    wt_sum = 0;

    for (i = 0; i < num_s; i++) {
        ft += job[job_sch[i]].job_term;
        if (ft > job[job_sch[i]].target_term) {
            wt = ft - job[job_sch[i]].target_term;
            wt_sum += wt;
        }
        else
            wt = 0;
        printf("%3d %10s %10d %10d\n", i + 1, job[job_sch[i]].pr_code, wt,
               wt_sum);
    }
}
