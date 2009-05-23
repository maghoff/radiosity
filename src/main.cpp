#include <iostream>
#include <typeinfo>
#include <ymse/gl_box_reshaper.hpp>
#include <ymse/glut_core.hpp>
#include <ymse/gl_box_reshaper.hpp>
#include "simplemodel.hpp"

int main(int argc, const char *argv[])
try {
	ymse::glut_core c;
	c.init(argc, argv);

	ymse::gl_box_reshaper r;
	r.set_box(-220, -70, 220, 70);
	c.set_reshaper_object(&r);

	simplemodel g;
	c.set_game_object(&g);

	c.set_keyboard_handler(g.get_keyboard_handler());

	return c.run();
}
catch (const std::exception& e) {
	std::cerr <<
		"Fatal error: " << e.what() << "\n"
		"Typeid: " << typeid(e).name() << std::endl;
	return -1;
}
catch (...) {
	std::cerr << "Unknown fatal error" << std::endl;
	return -1;
}; //< ; is a workaround for MSVC

