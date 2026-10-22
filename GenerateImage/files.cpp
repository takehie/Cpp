#include <iostream> // 標準出力
#include <string> // 文字列操作
#include <cstdlib> // コマンドを実行、C標準ライブラリ
#include <cstdio> // ファイル操作、C標準ライブラリ

void convertPpmToPng(const std::string& ppm, const std::string& png) {
	// ppmをpngに変換するコマンドを作成
	std::string cmd = "magick " + ppm + " " + png;
	// コマンドを実行して、変換
	std::system(cmd.c_str());
}

void deletePpm(const std::string& filename) {
	if (std::remove(filename.c_str()) == 0) {
		std::cout << "Deleted: " << filename << std::endl;
	} else {
		std::cerr << "Failed to delete: " << filename << std::endl;
	}
}