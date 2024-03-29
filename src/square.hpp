#ifndef SIMPLEMODEL_SQUARE_HPP
#define SIMPLEMODEL_SQUARE_HPP

#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

class gl_double_buffer;

class square : public boost::noncopyable {
	struct impl;
	boost::scoped_ptr<impl> d;

	double dx, dy;
	double nx, ny, nz;
	void get_hemicube(
		unsigned dim,
		int x, int y,
		gl_double_buffer& buf,
		unsigned scene_display_list,
		unsigned multiplier_map,
		unsigned multiplier_map_sum
	);

public:
	square();
	~square();

	void set_origin(float, float, float);
	void set_t_direction(float, float, float);
	void set_u_direction(float, float, float);

	void calculate_incident(
		unsigned dim,
		gl_double_buffer bufs[],
		//gl_double_buffer& buf,
		unsigned scene_display_list,
		unsigned multiplier_map,
		unsigned multiplier_map_sum
	);
	void calculate_excident();

	void render();

	unsigned emission();
	unsigned reflectance();
	unsigned incident();
	unsigned excident();
};

#endif
