#pragma once

#include "Microbit.h"
#include <functional>
#include <vector>

enum EButtonStatus {
	Released = 0,
	Pressed = 1
};

struct Button {
	// Number of cycle the button was pressed for
	uint32_t PressedFor = 0;

	// Ref to the button
	MicroBitButton *Button;

	// Current Status of the button
	EButtonStatus Status;

	// Release lambda
	std::function<void()> ReleasedLambda;

	// Pressed Lambda
	std::function<void()> PressedLambda;
};

class Event {
public:
	Event();

	// param pDefault: should we load the default A/B buttons
	void Init(MicroBit *uBit = nullptr);

	// Process the inputs
	void Process();

	std::vector<Button> ButtonList;
};