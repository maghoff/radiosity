#ifndef RADIOSITY_REDUCE_HPP
#define RADIOSITY_REDUCE_HPP

class gl_fbo;
class gl_texture;

void reduce(int w, int h, gl_fbo& f1, gl_fbo& f2, gl_texture& t1, gl_texture& t2);

#endif
