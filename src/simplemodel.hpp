#ifndef SIMPLEMODEL_HPP
#define SIMPLEMODEL_HPP

#include <ymse/game.hpp>

namespace ymse {
class keyboard_handler;
}

class simplemodel : public ymse::game {

	float angx, angy, angz;

public:
	simplemodel();

	void render();
	void tick();

	ymse::keyboard_handler* get_keyboard_handler();
};

#endif

