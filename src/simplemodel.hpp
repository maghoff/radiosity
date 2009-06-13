#ifndef SIMPLEMODEL_HPP
#define SIMPLEMODEL_HPP

#include <ymse/game.hpp>

#include <ymse/bindable_keyboard_handler.hpp>
#include "camera.hpp"
#include "keyboard_camera_controller.hpp"

namespace ymse {
class keyboard_handler;
}

class simplemodel : public ymse::game {

	unsigned display_list;

	float angx, angy, angz;

	camera c;
	ymse::bindable_keyboard_handler kbd;
	keyboard_camera_controller contr;

	void record_display_list();

public:
	simplemodel();
	~simplemodel();

	void render();
	void tick();

	ymse::keyboard_handler* get_keyboard_handler();
};

#endif

