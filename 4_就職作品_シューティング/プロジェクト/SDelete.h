#pragma once

template <class T>
inline void SDelete(T*& p) {
	delete p;
	p = nullptr;
}