#pragma once

#include "MicroBit.h"
#include <string>
#include <bitset>
#include <cmath>

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 4
#define PLAYER_A_COLOUR 255
#define PLAYER_B_COLOUR 25

typedef std::bitset<25> Bitboard;

enum EPlayer {
	PlayerA = 0,
	PlayerB,
	NbOfPlayer = 2
};

enum EDirection {
	Right = 0,
	Left
};

class Board {
public:
	Board();

	void Render(MicroBit *uBit);
	void MovePaddle(const EDirection pDirection);
	void Drop();

	void ChangeTurn();

protected:
	void DrawBoard(const EPlayer pPlayer, MicroBit *uBit);
	void DrawPaddle(MicroBit *uBit);

	EPlayer PlayerTurn = EPlayer::PlayerA;

	int8_t PaddleLocation = 0;
	int8_t PreviousPaddleLocation = 4;

	/*
	Player board is stored in memory using bitboard. The bitboard
	is mapped using the following mapping:
	x x xx xx xx
	4 9 14 19 24
	3 8 13 18 23
	2 7 12 17 22
	1 6 11 16 21
	*/
	Bitboard PlayerBitboard[EPlayer::NbOfPlayer];
};


