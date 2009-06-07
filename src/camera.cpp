#include <ymse/vec.hpp>
#include "camera.hpp"

using ymse::vec3f;

struct camera::impl {
	vec3f p, v;
};

camera::camera() :
	d(new impl)
{
}

camera::~camera() {
}

void camera::apply() {
}
