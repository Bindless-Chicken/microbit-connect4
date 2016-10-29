#include "Event.h"

Event::Event() {

}

void Event::Init(MicroBit *uBit) {
	if (uBit != nullptr) {
		// A button binding
		Button buttonA;
		buttonA.Button = &uBit->buttonA;
		ButtonList.push_back(buttonA);

		// B binding
		Button buttonB;
		buttonB.Button = &uBit->buttonB;
		ButtonList.push_back(buttonB);
	}
}

void Event::Process() {
	for (auto &button : ButtonList) {
		if (button.Button->isPressed()) {
			if (button.Status == EButtonStatus::Pressed)
				button.PressedFor++;
			else {
				button.Status = EButtonStatus::Pressed;
				if (button.PressedLambda)
					button.PressedLambda();
			}
		}
		else {
			if (button.Status == EButtonStatus::Pressed) {
				button.Status = EButtonStatus::Released;
				button.PressedFor = 0;
				if (button.ReleasedLambda)
					button.ReleasedLambda();
			}
		}
	}
}