#ifndef ESSENTIAL_H
#define ESSENTIAL_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <ctype.h>
#include <set>
#include <time.h>
#include <random>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

using namespace std;


#define MAGIC_KEY 224 // 상하좌우 화살표가 들어올 때 선행되어 들어오는 숫자
#define SPACE 32 // 스페이스 키 값
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4
#define ENTER 13

#define ACES 20
#define Deuce5s 21
#define Threes 22
#define Fours 23
#define Fives 24
#define Sixes 25
#define Subtotal 26
#define Choice 27
#define FourofaKind 28
#define FullHouse 29
#define SStraight 30
#define LStraight 31
#define Yatch 32
#define Total 33

/*
enum KEYBOARD {
    1p_UP = 72, 1p_LEFT = 75, 1p_RIGHT = 77, 1p_DOWN = 80
};
*/


/*
int RandRange(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}
*/


#endif
