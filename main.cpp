// g++ main.cpp commands.cpp timer.cpp
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

#include "commands.h"
#include "timer.h"
#include "color.h"

/*
 * PPM画像を管理するクラス
 */
class ImagePPM {
	private:
		int width;
		int height;
// 一次元配列で定義して高速化
		std::vector<Color> pixels;

	public:
// コンストラクタ：画像サイズ指定
		ImagePPM(int w, int h) : width(w), height(h), pixels(w * h) {}

// 指定座標に色を設定
		void setPixel(int x, int y, const Color& color) {
// 画面の外の座標には書き込まない
			if (x < 0 || x >= width || y < 0 || y >= height){
				return;
			}else{
				pixels[y * width + x] = color;
			}
		}

// PPM（P3形式）で保存
	void save(const std::string &filename) const {
		std::ofstream ofs(filename);
		ofs << "P3\n";
		ofs << width << " " << height << "\n";
		ofs << "255\n";

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				const Color &c = pixels[y * width + x];
				ofs << c.toInt(c.r) << " " << c.toInt(c.g) << " " << c.toInt(c.b) << " ";
			}
			ofs << "\n";
		}
	}
};

/* エントリポイント */
int main() {
// 処理時間測定開始
	Timer timer;

// 画像サイズ（解像度）
	const int WIDTH  = 4000;  // 横
	const int HEIGHT = 2000;  // 縦

    ImagePPM image(WIDTH, HEIGHT);

// フレーム設定
	const std::string baseName = "image";

	// 出力先ディレクトリのパス名（Downloads）
	const std::filesystem::path path outputDirectory = R"(C:\Users\take2\Downloads)";

	// ファイル名作成
    std::string ppmName = (outputDir / makeNumberedName(baseName, frame, ".ppm")).string();
    std::string pngName = makeNumberedName(baseName, frame, ".png");

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			double r = static_cast<double>(x) / (WIDTH - 1);
			double g = static_cast<double>(y) / (HEIGHT - 1);
			if((centerX-x)*(centerX-x) + (centerY-y)*(centerY-y) <= radius * radius){
				image.setPixel(x, y, Color(0.0, g, r));
			}else{
				image.setPixel(x, y, Color(0.0, g, r));
			}
		}
	}

    image.save(ppmName);
    convertPpmToPng(ppmName, pngName);
	
	exit(EXIT_SUCCESS); // 正常に終了
	// return 0;
}
