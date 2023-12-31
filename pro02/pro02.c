#include <stdio.h>


typedef struct {
    /* data */
    char pr_code[9];  // 開発コード
    int job_term;     // 開発作業日数
    int target_term;  // 目標作業期間
} JOB;


void job_scheduling (int, JOB [], int []);
void print_schedule (int num_s, JOB job[num_s], int job_sch[num_s]);

// num_s: サブシステム数
// job: サブシステム情報
// job_sch: 開発作業順序
void job_scheduling (int num_s, JOB job[num_s], int job_sch[num_s]) {
    int ft,          // i番目までの開発作業日数の合計
        ft_a, ft_b,  // (i - 1)番目までの開発作業日数の合計
        wt_a,        // 正順の2つの遅延日数の合計
        wt_b,        // 逆順の2つの遅延日数の合計
        job_no,      // 仕事の番号
        i, j;        // ループ用変数

    // jobの順番を保存
    for (i = 0; i < num_s; i++)
        job_sch[i] = i;

    ft = 0;  // 開発作業日数の合計値を初期化
    i = 0;   // ループ変数を初期化

    while (i < num_s - 1) {  // サブシステム数分ループ
        // (i - 1)番目までの開発作業日数を代入
        ft_a = ft;
        ft_b = ft;
        // 2つのJOBの遅延日数初期化
        wt_a = 0;
        wt_b = 0;

        for (j = 0; j < 2; j++) {  // 遅延日数の合計 wt_a, wt_bを求める
            // (i - 1)番目までの作業日数合計値に(i + j)番目の作業日数を加算
            ft_a += job[job_sch[i + j]].job_term;  // 正順
            // 目標作業期間を過ぎていたら
            if (ft_a > job[job_sch[i + j]].target_term)
                // 遅延日数を加算
                wt_a += ft_a - job[job_sch[i + j]].target_term;
            // (i - 1)番目までの作業日数合計値に(i + 1 - j)番目の作業日数を加算
            ft_b += job[job_sch[i + 1 - j]].job_term;  // 逆順
            // 目標作業期間を過ぎていたら
            if (ft_b > job[job_sch[i + 1 - j]].target_term)
                // 遅延日数を加算
                wt_b = ft_b - job[job_sch[i + 1 - j]].target_term;
        }
        // 遅延日数比較
        if (wt_a > wt_b) {  // 正順の方が遅延日数が多い場合
            // 順番の入れ替え ###############
            job_no = job_sch[i];
            job_sch[i] = job_sch[i + 1];
            job_sch[i + 1] = job_no;
            // ############################

            if (i > 0)
                // iを1減らし、開発作業日数の合計値からi-1番目の開発作業日数を減算
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
