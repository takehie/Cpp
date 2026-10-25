// g++ main.cpp
// ./a

// ヘッダの読み込み.
#include <iostream>
#include <fstream>
#include <vector> // 可変長配列を使用
#include <string> // 文字列操作
#include <algorithm>
#include <cstdlib> // コマンドを実行
#include <iomanip>
#include <cstdio>
#include <sstream>
#include <filesystem>
#include <chrono> // 時刻

/* エントリポイント */
int main() {
// 処理時間測定開始
// std::chrono::steady_clockを使用（システム時刻の変更に影響されない）
	const auto start = std::chrono::steady_clock::now();

// 画像サイズ（解像度）
	const int WIDTH  = 4000;  // 横
	const int HEIGHT = 2000;  // 縦

	const std::string baseName = "image.pmm";

	// 出力先ディレクトリのパス名（Downloads）
	const std::filesystem::path outputDirectory = R"(C:\Users\take2\Downloads)";

	// ファイル名作成
    std::string ppmName = (outputDirectory / baseName).string();

	// 終了時点の時刻を取得
	const auto end = std::chrono::steady_clock::now();
	// 開始時刻との時間差から経過時間を求める（ミリ秒で、整数値）
	const std::chrono::duration<double, std::milli> elapsed = end - start;

	// 経過時間を標準出力
	std::cout << "elapsed time: " << elapsed.count() << " ms\n";
	
	exit(EXIT_SUCCESS); // 正常に終了
	// return 0;
}
