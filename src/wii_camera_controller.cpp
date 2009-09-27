#include <iostream>
#include <cwiid.h>
#include "wii_camera_controller.hpp"

wii_camera_controller::wii_camera_controller() :
	wiimote(0)
{
	std::cout << "Connecting Wii Remote. Please press 1+2 on the handset" << std::endl;

	bdaddr_t addr = *BDADDR_ANY;
	wiimote = cwiid_connect(&addr, CWIID_FLAG_REPEAT_BTN);

	cwiid_command(wiimote, CWIID_CMD_LED, CWIID_LED1_ON | CWIID_LED4_ON);
	cwiid_command(wiimote, CWIID_CMD_RPT_MODE,
		CWIID_RPT_STATUS |
		CWIID_RPT_BTN |
		CWIID_RPT_NUNCHUK
	);
}

wii_camera_controller::~wii_camera_controller() {
	if (wiimote) cwiid_disconnect(wiimote);
}

void wii_camera_controller::pump() {
/*
	int n;
	cwiid_mesg* msgs;
	timespec ts;
	cwiid_get_mesg(wiimote, &n, &msgs, &ts);
*/

	/*int ok =*/ cwiid_get_state(wiimote, &st);
}

double wii_camera_controller::forward() {
	return
		((st.buttons & CWIID_BTN_A) ? 0.07 : 0) -
		((st.buttons & CWIID_BTN_B) ? 0.07 : 0)
	;
}

double wii_camera_controller::right() {
	return
		((st.buttons & CWIID_BTN_RIGHT) ? 0.07 : 0) -
		((st.buttons & CWIID_BTN_LEFT) ? 0.07 : 0)
	;
}

double wii_camera_controller::up() {
	return
		((st.buttons & CWIID_BTN_UP) ? 0.07 : 0) -
		((st.buttons & CWIID_BTN_DOWN) ? 0.07 : 0)
	;
}

double stickval(uint8_t ival) {
	const double magnitude = 128.0;
	const double cap_top = 32.0;
	const double cap_bottom = 8.0;

	double v = ival - 128.0;
	bool neg = v < 0;

	if (neg) v = -v;

	if (v > magnitude - cap_top) v = magnitude - cap_top;
	if (v < cap_bottom) v = 0;
	else v -= cap_bottom;

	if (neg) v = -v;

	v /= magnitude - cap_top - cap_bottom;

	return v;
}

double wii_camera_controller::yaw() {
	return -0.7 * stickval(st.ext.nunchuk.stick[0]);
}

double wii_camera_controller::pitch() {
	return -0.7 * stickval(st.ext.nunchuk.stick[1]);
}

double wii_camera_controller::roll() {
	return
		((st.buttons & CWIID_BTN_PLUS) ? 0.7 : 0) -
		((st.buttons & CWIID_BTN_MINUS) ? 0.7 : 0)
	;
}
