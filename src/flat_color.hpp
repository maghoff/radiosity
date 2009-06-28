#ifndef SIMPLEMODEL_FLAT_COLOR_HPP
#define SIMPLEMODEL_FLAT_COLOR_HPP

/// Generates a flat texture of the given size. All the pixels are given the
/// value of (r, g, b, a).
void flat_color(
	unsigned width, unsigned height,
	float r, float g, float b, float a
);

#endif
