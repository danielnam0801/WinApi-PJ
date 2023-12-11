#pragma once
//#include<iostream>
#include <Windows.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include "define.h"
#include "Vec2.h"
#include "enums.h"
#include <functional>
//using namespace std; ��� ����
using std::vector;
using std::map;
using std::wstring;

template<typename T>
std::function<void(T*)> array_deleter() {
	return [](T* ptr) { delete[] ptr; };
}

// transparent �� blt �� �� �ʿ�
#pragma comment(lib, "Msimg32.lib")