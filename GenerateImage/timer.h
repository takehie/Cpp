#ifndef TIMER_H
#define TIMER_H

#include <chrono>

/*
 * 処理時間を測定するためのタイマークラス
 * 実装は Timer.cpp
 */
class Timer {
    public:
        // コンストラクタ
        Timer();

        // 計測開始（リセット）
        void start();

        // 経過時間をミリ秒で取得、メンバ変数を変更しない
        double elapsedMilliseconds() const;

        // 経過時間を秒で取得、メンバ変数を変更しない
        double elapsedSeconds() const;

    private:
        // 計測開始時刻を保存するメンバ変数
        std::chrono::steady_clock::time_point m_startTime;
};

#endif