#include "Timer.h"

// コンストラクタ インスタンス生成時に自動で計測を開始する
Timer::Timer() {
    start();
}

// 計測開始（時刻を記録）
void Timer::start() {
    // 現在時刻を開始時刻として保存
    m_startTime = std::chrono::steady_clock::now();
}

// 経過時間をミリ秒で取得
double Timer::elapsedMilliseconds() const {
    // 現在時刻を取得、型推論で初期化
    auto now = std::chrono::steady_clock::now();

    // 開始時刻との差分をミリ秒で計算
    std::chrono::duration<double, std::milli> elapsed = now - m_startTime;
    return elapsed.count();
}

// 経過時間を秒で取得
double Timer::elapsedSeconds() const {
    // 現在時刻を取得、型推論で初期化
    auto now = std::chrono::steady_clock::now();

    // 開始時刻との差分を秒で計算
    std::chrono::duration<double> elapsed = now - m_startTime;
    return elapsed.count();
}
