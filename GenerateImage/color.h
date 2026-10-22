// color.h
#ifndef COLOR_H
#define COLOR_H

#include <algorithm>

/*
 * RGBカラーを表すクラス.
 * 各成分は 0.0 ～ 1.0 の正規化値の範囲で保持する.
 */
class Color {
	public:
		double r, g, b;

// constructor and the member initializer list
		Color(double r = 0.0, double g = 0.0, double b = 0.0) : r(r), g(g), b(b) {}

// transform 0.0~1.0 into 0~255.
		int toInt(double v) const {
// 値を0.0から1.0の範囲内に収める.
			v = std::clamp(v, 0.0, 1.0);
// 0から255の整数に丸めて返す.
			return static_cast<int>(255.999 * v);
		}
};

#endif