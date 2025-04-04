#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

bool loadOBJ(
	const char* path,
	std::vector<vec3>& out_vertices,
	std::vector<vec2>& out_uvs,
	std::vector<vec3>& out_normals
);


/*
bool loadAssImp(
	const char* path,
	std::vector<unsigned short>& indices,
	std::vector<vec3>& vertices,
	std::vector<vec2>& uvs,
	std::vector<vec3>& normals
);
*/

#endif