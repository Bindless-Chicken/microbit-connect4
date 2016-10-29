#include "Board.h"

Board::Board() {
}

void Board::Render(MicroBit *uBit) {
	// Draw the board for both players
	DrawBoard(EPlayer::PlayerA, uBit);
	DrawBoard(EPlayer::PlayerB, uBit);

	// Draw the paddle
	DrawPaddle(uBit);
}

void Board::DrawBoard(const EPlayer pPlayer, MicroBit *uBit) {
	uint8_t brightness = pPlayer == EPlayer::PlayerA ? PLAYER_A_COLOUR : PLAYER_B_COLOUR;

	for (uint8_t i = 0; i < 25; ++i) {
		if (PlayerBitboard[pPlayer][i])
			uBit->display.image.setPixelValue(std::floor(i / 5), 4-(i % 5), brightness);
	}
}

void Board::DrawPaddle(MicroBit *uBit) {
	uint8_t brightness = PlayerTurn == EPlayer::PlayerA ? PLAYER_A_COLOUR : PLAYER_B_COLOUR;

	uBit->display.image.setPixelValue(PaddleLocation, 0, brightness);
	uBit->display.image.setPixelValue(PreviousPaddleLocation, 0, 0);
}

void Board::MovePaddle(const EDirection pDirection) {
	PreviousPaddleLocation = PaddleLocation;
	PaddleLocation += pDirection == EDirection::Left ? -1 : 1;

	// Detect overflow
	if (PaddleLocation < 0)
		PaddleLocation = 4;
	else if (PaddleLocation > 4)
		PaddleLocation = 0;
}

void Board::Drop() {
	for (uint8_t i = 0; i <= 4; ++i) {
		// Test if the space is available on both players
		if (PlayerBitboard[EPlayer::PlayerA][(PaddleLocation * 5)+i] == false && PlayerBitboard[EPlayer::PlayerB][(PaddleLocation * 5) + i] == false) {
			PlayerBitboard[PlayerTurn][(PaddleLocation * 5) + i] = true;

			// Switch player turn
			ChangeTurn();

			// and quit
			return;
		}
	}
}

void Board::ChangeTurn() {
	PlayerTurn = PlayerTurn == EPlayer::PlayerA ? EPlayer::PlayerB : EPlayer::PlayerA;
}