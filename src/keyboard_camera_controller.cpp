#include <ymse/vec.hpp>
#include <ymse/bindable_keyboard_handler.hpp>
#include <ymse/opposite_keys.hpp>
#include <ymse/keycodes.hpp>
#include "keyboard_camera_controller.hpp"

using ymse::vec3f;

struct keyboard_camera_controller::impl {
	boost::scoped_ptr<ymse::opposite_keys>
		forward,
		right,
		yaw,
		pitch,
		roll
	;
};

keyboard_camera_controller::keyboard_camera_controller(
	ymse::bindable_keyboard_handler& handler
) :
	d(new impl)
{
	using namespace ymse;
	d->forward.reset(new ymse::opposite_keys(handler, KEY_S, KEY_W));
	d->right.reset(new ymse::opposite_keys(handler, KEY_A, KEY_D));
	d->yaw.reset(new ymse::opposite_keys(handler, KEY_RIGHT, KEY_LEFT));
	d->pitch.reset(new ymse::opposite_keys(handler, KEY_UP, KEY_DOWN));
	d->roll.reset(new ymse::opposite_keys(handler, KEY_Q, KEY_E));
}

keyboard_camera_controller::~keyboard_camera_controller() {
}

double keyboard_camera_controller::forward() {
	return 0.08 * d->forward->val();
}

double keyboard_camera_controller::right() {
	return 0.08 * d->right->val();
}

double keyboard_camera_controller::yaw() {
	return 0.2 * d->yaw->val();
}

double keyboard_camera_controller::pitch() {
	return 0.2 * d->pitch->val();
}

double keyboard_camera_controller::roll() {
	return 0.2 * d->roll->val();
}
