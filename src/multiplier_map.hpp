#ifndef RADIOSITY_MULTIPLIER_MAP_HPP
#define RADIOSITY_MULTIPLIER_MAP_HPP

// Generates a texture with which to multiply a hemicube rendering to
// compensate for the cube shape as well as the angle of incident light
// (Lambert's cosine law)
//
// The texture is put into the currently bound texture by way of glTexImage2D.
double generate_multiplier_map(int fbo_width, int fbo_height);

#endif
