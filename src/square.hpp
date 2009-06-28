#ifndef SIMPLEMODEL_SQUARE_HPP
#define SIMPLEMODEL_SQUARE_HPP

#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

class gl_double_texture;

class square : public boost::noncopyable {
	struct impl;
	boost::scoped_ptr<impl> d;

public:
	square();
	~square();

	void set_origin(float, float, float);
	void set_t_direction(float, float, float);
	void set_u_direction(float, float, float);

	void calculate_incident();
	void calculate_excident();

	void render();

	unsigned emission();
	unsigned reflectance();
	unsigned incident();
	unsigned excident();
};

#endif
