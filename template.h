#pragma once
template<typename T>
T temptest(T v, T min, T max) {
	if (v < min) {
		return min;
	}
	else if (v > max) {
		return max;
	}
	else {
		return v;
	}
}