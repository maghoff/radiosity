#include <ymse/vec.hpp>
#include <ymse/bindable_keyboard_handler.hpp>
#include <ymse/opposite_keys.hpp>
#include <ymse/keycodes.hpp>
#include <ymse/key.hpp>
#include "keyboard_camera_controller.hpp"

using ymse::vec3f;

struct keyboard_camera_controller::impl {
	boost::scoped_ptr<ymse::opposite_keys>
		forward,
		yaw,
		pitch,
		roll
	;

	boost::scoped_ptr<ymse::key>
		strafe
	;
};

keyboard_camera_controller::keyboard_camera_controller(
	ymse::bindable_keyboard_handler& handler
) :
	d(new impl)
{
	using namespace ymse;
	d->forward.reset(new ymse::opposite_keys(handler, KEY_Z, KEY_A));
	d->yaw.reset(new ymse::opposite_keys(handler, KEY_RIGHT, KEY_LEFT));
	d->pitch.reset(new ymse::opposite_keys(handler, KEY_UP, KEY_DOWN));
	d->roll.reset(new ymse::opposite_keys(handler, KEY_Q, KEY_W));
	d->strafe.reset(new ymse::key(handler, KEY_LALT));
}

keyboard_camera_controller::~keyboard_camera_controller() {
}

double keyboard_camera_controller::forward() {
	return 0.07 * d->forward->val();
}

double keyboard_camera_controller::right() {
	return d->strafe->val() ? 0.07 * d->yaw->val() : 0;
}

double keyboard_camera_controller::up() {
	return d->strafe->val() ? 0.07 * d->pitch->val() : 0;
}

double keyboard_camera_controller::yaw() {
	return d->strafe->val() ? 0 : 0.7 * d->yaw->val();
}

double keyboard_camera_controller::pitch() {
	return d->strafe->val() ? 0 : 0.7 * d->pitch->val();
}

double keyboard_camera_controller::roll() {
	return 0.7 * d->roll->val();
}
