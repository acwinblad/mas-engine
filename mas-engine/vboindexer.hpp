#ifndef VBOINDEXER_HPP
#define VBOINDEXER_HPP

void indexVBO(
	std::vector<vec3>& in_vertices,
	std::vector<vec2>& in_uvs,
	std::vector<vec3>& in_normals,
	std::vector<unsigned short>& out_indices,
	std::vector<vec3>& out_vertices,
	std::vector<vec2>& out_uvs,
	std::vector<vec3>& out_normals
	);

void indexVBO_TBN(
	std::vector<vec3>& in_vertices,
	std::vector<vec2>& in_uvs,
	std::vector<vec3>& in_normals,
	std::vector<vec3>& in_tangents,
	std::vector<vec3>& in_bitangents,
	std::vector<unsigned short>& out_indices,
	std::vector<vec3>& out_vertices,
	std::vector<vec2>& out_uvs,
	std::vector<vec3>& out_normals,
	std::vector<vec3>& out_tangents,
	std::vector<vec3>& out_bitangents
	);

#endif // !VBOINDEXER_HPP
