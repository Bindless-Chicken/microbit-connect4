#include "MicroBit.h"
#include "Board.h"
#include "Event.h"

void app_main() {
	Board gameBoard;

	Event eventManager;
	eventManager.Init(&uBit);

	// Create the event for the A button
	eventManager.ButtonList[0].ReleasedLambda = ([&gameBoard]() {
		gameBoard.MovePaddle(EDirection::Right);
		gameBoard.Render(&uBit);
	});

	// Create the event for the B button
	eventManager.ButtonList[1].ReleasedLambda = ([&gameBoard]() {
		gameBoard.Drop();
		gameBoard.Render(&uBit);
	});

	// Set the display to grayscale
	uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);

	// First render of the game board
	gameBoard.Render(&uBit);

	// MainLoop
	while (true) {
		// Process the inputs
		eventManager.Process();

		uBit.sleep(100);
	}
}
