#ifndef SIMPLEMODEL_HPP
#define SIMPLEMODEL_HPP

#include <boost/scoped_ptr.hpp>
#include <ymse/game.hpp>

namespace ymse {
class keyboard_handler;
}

class simplemodel : public ymse::game {
	struct impl;
	boost::scoped_ptr<impl> d;

	void set_ambient_incident();

	void calculate_incident();
	void calculate_excident();

	void record_display_list();

public:
	simplemodel();
	~simplemodel();

	void render();
	void tick();

	ymse::keyboard_handler* get_keyboard_handler();
};

#endif

