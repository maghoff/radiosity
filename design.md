Random notes on the design
==========================


The multiplier map
------------------

After rendering a hemicube, the image has to be adjusted for:

 * the shape of the hemicube (we kind of want a hemisphere instead)
 * the angle of incident light (Lambert's cosine law)

These two adjustments come in the form of a number each pixel is supposed to be
multiplied by, which means that we can multiply these two together to get one
map (maps from coordinate to multiplication factor) which adjust for both
things.

Applying the map is as simple as doing alpha blending with

    glBlendFunc(GL_ZERO, GL_SRC_ALPHA);

See the documentation for `glBlendFunc` to see the mathematical truth of this.


Normalization
-------------

To calculate the total amount of incident light to a given pixel, we should add
the value of all pixels in the hemicube rendering (after applying the
multiplier map). However, with no further adjustment, this would give us a
number in a range going from 0 to well over the desired 1.

There are several ways to attack this:

 1. Normalize the multiplier map, such that the sum of all pixels in it is 1.
 2. Divide the sum of the total from a hemicube by the total of the multiplier
    map.

These two are both theoretically sound, but do not work in practice because
pixels in OpenGL do not have the required dynamic range. With method 1., we
would end up having a multiplier map completely filled with zeroes, and with
method 2., we would end up dividing by such a large number that it would always
result in zero.

The solution I have found to this is to incorporate the division into the
calculation of the sum of all the pixels. See the chapter on summation.


Summation
---------

A central operation in radiosity rendering is to caculate the sum of all pixels
in a rendered scene (with partial or no lighting).

The way we do this is to first render the scene to a texture by way of an FBO
(frame buffer object). When we have all the pixels in a texture, we can draw
the top half of the texture to another FBO and then, thanks to `glBlendFunc`,
we can add the other half of the texture on top. Rinse and repeat until all we
have exactly one pixel of data. This pixel is the sum of the entire texture.

For a hemicube that has been multiplied by the multiplier map, this sum is too
large. We lose precision and indeed the entire data point. We need to divide
this by the sum of all the pixels in the multiplier map, call this value S.
However, S is also too large for OpenGL to handle properly. We need to devise a
way to achieve this division without doing it all in one go.

By using `glColor`, we can multiply the texture by some factor each time we
draw it on the next frame buffer. Since we do this everytime we add, we keep
within an acceptable dynamic range. If we choose a constant factor for this, it
will be multiplied in once for each halving of the texture. For a texture
size of 2^d x 2^d pixels, we do d halvings in the x-direction, then d
additional halvings in the y-direction for a total of 2d halvings.

To achieve the desired division in the end we need to choose the factor f such
that f^(2d) = 1 / S. It follows that f = 1 / S^(1/2d).

This approach works well in practice.
