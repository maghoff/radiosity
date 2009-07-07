#ifndef SIMPLEMODEL_GET_INCIDENT_LIGHT_HPP
#define SIMPLEMODEL_GET_INCIDENT_LIGHT_HPP

class gl_double_buffer;

void get_incident_light(
	unsigned dim,
	gl_double_buffer& buf,
	unsigned display_list,
	unsigned multiplier_map,
	unsigned multiplier_map_sum
);

#endif
