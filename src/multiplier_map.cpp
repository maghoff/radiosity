#include <GL/gl.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include "debug_gl.hpp"
#include "multiplier_map.hpp"

void generate_multiplier_map(int fbo_width, int fbo_height) {
	GLfloat map[fbo_width * fbo_height * 4];

	int qw = fbo_width / 4, qh = fbo_height / 4;
	assert(qw*4 == fbo_width);
	assert(qh*4 == fbo_height);

	assert(qw == qh); //< A cube should be like-sided...
	const double b = qw;

	double sum = 0.; //< For normalization

	for (int y=0; y<fbo_height; ++y) {
		for (int x=0; x<fbo_width; ++x) {
			for (int c=0; c<4; ++c) {
				map[(fbo_width * y + x) * 4 + c] = 0.f;
			}
		}
	}

	for (int y=0; y<2*qh; ++y) {
		for (int x=0; x<2*qw; ++x) {

			double dx = (x - qw), dy = (y - qh);
			double h = sqrt(b*b + dx*dx + dy*dy);
			double val =
				(b / h) * //< Compensation for hemicube-shape
				(b / h) //< Lambert's Cosine Law
			;

			sum += val;

			for (int c=0; c<4; ++c) {
				map[((y + qh) * fbo_width + (x + qw)) * 4 + c] = val;
			}
		}
	}

	for (int y=0; y<2*qh; ++y) {
		for (int x=0; x<qw; ++x) {

			double dx = x, dy = (y - qh);
			double h = sqrt(b*b + dx*dx + dy*dy);
			double val =
				(b / h) * //< Compensation for hemicube-shape
				(dx / h) //< Lambert's Cosine Law
			;

			sum += 2. * val;

			for (int c=0; c<4; ++c) {
				map[((y + qh) * fbo_width + x) * 4 + c] = val;
				map[((y + qh) * fbo_width + (fbo_width-1 - x)) * 4 + c] = val;
			}
		}
	}

	for (int y=0; y<qh; ++y) {
		for (int x=0; x<2*qw; ++x) {

			double dx = (x - qw), dy = y;
			double h = sqrt(b*b + dx*dx + dy*dy);
			double val =
				(b / h) * //< Compensation for hemicube-shape
				(dy / h) //< Lambert's Cosine Law
			;

			sum += 2. * val;

			for (int c=0; c<4; ++c) {
				map[(y * fbo_width + x + qw) * 4 + c] = val;
				map[((fbo_height-1 - y) * fbo_width + x + qw) * 4 + c] = val;
			}
		}
	}

	// Normalize
	double r_sum = 1. / sum;
	for (int y=0; y<fbo_height; ++y) {
		for (int x=0; x<fbo_width; ++x) {
			for (int c=0; c<4; ++c) {
//				map[(fbo_width * y + x) * 4 + c] *= r_sum;
			}
		}
	}

	std::cout <<
		"sum: " << sum << "\n"
		"r_sum: " << r_sum << std::endl <<
		"sum ^ (1/16): " << pow(sum, 1./16.) << std::endl <<
		"1 / sum ^ (1/16): " << (1. / pow(sum, 1./16.)) << std::endl;

	glTexImage2D(
		GL_TEXTURE_2D, 0,
		GL_RGBA16F,
		fbo_width, fbo_height, 0, GL_RGBA,
		GL_FLOAT,
		map
	);
}
