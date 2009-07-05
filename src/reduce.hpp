#ifndef RADIOSITY_REDUCE_HPP
#define RADIOSITY_REDUCE_HPP

class gl_double_buffer;

// Calculate the sum of the current front buffer in the given double buffer,
// divided by the divisor. The division is carried out so as to maintain
// numerical stability.
void reduce(int w, int h, gl_double_buffer&, double divisor);

#endif
