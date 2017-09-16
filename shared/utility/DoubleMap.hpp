#pragma once

#include <map>

template <typename T, typename S>
class DoubleMap {
	std::map<T, S> tFirst;
	std::map<S, T> sFirst;
public:
	void add(T key, S value) {
		tFirst[key] = value;
		sFirst[value] = key;
	}

	void remove(T key) {
		if (tFirst.count(key) == 0) return;
		sFirst.erase(tFirst[key]);
		tFirst.erase(key);
	}

	void remove(S key) {
		if (sFirst.count(key) == 0) return;
		tFirst.erase(sFirst[key]);
		sFirst.erase(key);
	}

	bool exists(T key) {
		return tFirst.count(key) != 0;
	}

	bool exists(S key) {
		return sFirst.count(key) != 0;
	}

	S get(T key) {
		return tFirst[key];
	}

	T get(S key) {
		return sFirst[key];
	}
};
