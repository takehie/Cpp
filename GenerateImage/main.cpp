// g++ main.cpp files.cpp timer.cpp
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

#include "files.h"
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

// 指定した中心・半径・色で「球（円）」を描画する
	void drawSphere(int centerX, int centerY, int radius, const Color& color) {
// 球が収まる最小矩形だけを走査する（無駄な計算を避ける）
		for (int y = centerY - radius; y <= centerY + radius; ++y) {
			for (int x = centerX - radius; x <= centerX + radius; ++x) {

				int dx = x - centerX;
				int dy = y - centerY;

// 円の内部かどうかを判定
				if (dx * dx + dy * dy <= radius * radius) {
					setPixel(x, y, color);
				}
 			}
		}
	}

// PPM（P3形式）で保存
	void save(const std::string& filename) const {
		std::ofstream ofs(filename);
		ofs << "P3\n";
		ofs << width << " " << height << "\n";
		ofs << "255\n";

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				const Color& c = pixels[y * width + x];
				ofs << c.toInt(c.r) << " " << c.toInt(c.g) << " " << c.toInt(c.b) << " ";
			}
			ofs << "\n";
		}
	}
};

/* 連番付きファイル名を生成（例: image_00001.ppm）*/
std::string makeNumberedName(const std::string& base, int frame, const std::string& ext){
// osuringstreamで文字列操作を容易にする
	std::ostringstream oss;
// <<を使って文字列を組み立て
// frameをsetw()とsetfillが適用される。
	oss << base << "_" << std::setw(5) << std::setfill('0') << frame << ext;

	return oss.str();
}

/* エントリポイント */
int main() {
// 処理時間測定開始
	Timer timer;

// FullHD解像度
	const int WIDTH  = 1920;  // 横
	const int HEIGHT = 1080;  // 縦

// 球の情報
	int centerX = WIDTH / 2;
	int centerY = HEIGHT / 2;
	int radius = 200;

        ImagePPM image(WIDTH, HEIGHT);

// フレーム設定
	const int totalFrames = 1;
	const std::string baseName = "20260118_image";
	int frame = 1;

	// パス名
	std::string pathName;

	// ファイル名作成
    std::string ppmName = makeNumberedName(baseName, frame, ".ppm");
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

/*
	for (int frame = 1; frame <= totalFrames; ++frame) {

		ImagePPM image(WIDTH, HEIGHT);

		// ===== 背景グラデーション =====
		for (int y = 0; y < HEIGHT; ++y) {
			for (int x = 0; x < WIDTH; ++x) {
				double r = static_cast<double>(x) / (WIDTH - 1);
				double g = static_cast<double>(y) / (HEIGHT - 1);
				image.setPixel(x, y, Color(r, g, 0.0));
			}
		}

		// ===== フレームに応じて球を移動 =====
		int radius = 200;

		// 横方向に移動（左 → 右）
		int centerX = static_cast<int>((WIDTH - 2 * radius) * (static_cast<double>(frame - 1) / (totalFrames - 1))) + radius;

		int centerY = HEIGHT / 2;

		image.drawSphere(centerX, centerY, radius, Color(0.0, 0.0, 1.0));

		// ===== 保存 & 変換 =====
		std::string ppmName = makeNumberedName(baseName, frame, ".ppm");
		std::string pngName = makeNumberedName(baseName, frame, ".png");

 		image.save(ppmName);
		convertPpmToPng(ppmName, pngName);

		// std::cout << "Frame " << frame << " generated\n";
	}
*/

	// std::cout << "Finished!" << std::endl;

	// std::system("rm 20260101_*.png");
	// std::system("rm 20260101_*.ppm");

	deletePpm("20260118_image_00001.ppm");

	std::cout << "処理時間：" << timer.elapsedSeconds() << "[s]" << std::endl;

	exit(EXIT_SUCCESS); // 正常に終了
	// return 0;
}
