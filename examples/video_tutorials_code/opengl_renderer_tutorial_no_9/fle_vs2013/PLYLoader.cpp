/*********************************************************************************
created:	2017/06/09   03:22PM
filename: 	PLYLoader.cpp
file base:	PLYLoader
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class to load 3D PLY file format from the disk.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "PLYLoader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

// Description:
// Function that returns the total number of words in a given string.
static std::size_t countWordsInString(std::string const& _str)
{
	std::stringstream stream(_str);
	return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

bool PLYLoader::load(
	const std::string& _filename, 
	std::vector<Vector3D>& _vertices, 
	std::vector<Vector3D>& _normals, 
	std::vector<Vector2D>& _texcoord, 
	std::vector<Color4D>& _colors,
	std::vector<FaceIndices3>& _indices)
{
	std::ifstream file_op(_filename, std::ios::in);		//	open the file for reading
	if (!file_op)										//	if file not found display an error
	{
		std::cerr << "File not found." << std::endl;
		return false;
	}

	bool hascolors = false;								// flag for colors
	bool hasnormals = false;							// flag for normals
	bool hastexcoord = false;							// flag for texture coordinates

	int nb_V = 0;										// total number of vertices
	int nb_F = 0;										// total number of faces/triangles

	// read the header first.
	std::string line;									// text of each line
	while (!file_op.eof())								// start reading file data
	{
		std::getline(file_op, line);					// read the text of the line

		if (std::sscanf(line.c_str(), "element vertex %d", &nb_V) == 1) { std::cout << "No. of Vertices: " << nb_V << std::endl; }	// read total number of vertices

		if (line == "property uchar red") hascolors = true;		// set color flag true if file has colors information
		if (line == "property uchar green")	hascolors = true;
		if (line == "property uchar blue") hascolors = true;

		if (line == "property float s") hastexcoord = true;		// set normal flag true if file has normals information
		if (line == "property float t") hastexcoord = true;

		if (line == "property float nx") hasnormals = true;		// set normal flag true if file has normals information
		if (line == "property float ny") hasnormals = true;
		if (line == "property float nz") hasnormals = true;

		if (std::sscanf(line.c_str(), "element face %d", &nb_F) == 1) { std::cout << "No. of Faces: " << nb_F << std::endl; }	// read total number of faces/triangles

		std::cout << line << std::endl;

		if (line == "end_header") 
			break;
	}

	if (nb_V < 1 || nb_F < 1) return false;		// check if file has vertices and faces information.

	// reserve the memory for vertices, normals, texcoord, colors and _indices to speed-up the push_back process.
	_vertices.clear();
	_normals.clear();
	_texcoord.clear();
	_colors.clear();
	_indices.clear();
	_vertices.reserve(nb_V);
	_normals.reserve(nb_V);
	_texcoord.reserve(nb_V);
	_colors.reserve(nb_V);
	_indices.reserve(nb_F);

	float x = 0.0f, y = 0.0f, z = 0.0f,
		s = 0.0f, t = 0.0f,
		nx = 0.0f, ny = 0.0f, nz = 0.0f;
	unsigned int r = 0, g = 0, b = 0;
	unsigned int num = 0, v1 = 0, v2 = 0, v3 = 0;

	while (!file_op.eof())											// Start reading file data
	{
		std::getline(file_op, line);								// read the text of the line

		std::size_t nw = countWordsInString(line);

		if (nw == 3)
		{
			if (std::sscanf(line.c_str(), "%f %f %f", &x, &y, &z) == 3)
			{
				_vertices.push_back(Vector3D(x, y, z));						//	store vertex in [x, y, z] to the array
			}
		}
		else if (nw == 5)
		{
			if (std::sscanf(line.c_str(), "%f %f %f %f %f", &x, &y, &z, &s, &t) == 5)
			{
				_vertices.push_back(Vector3D(x, y, z));						//	store vertex in [x, y, z] to the array
				if (hastexcoord) _texcoord.push_back(Vector2D(s, t));		//	store texture coordinates in [s, t] to the array
			}
		}
		else if (nw == 6)
		{
			if (hasnormals)
			{
				if (std::sscanf(line.c_str(), "%f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz) == 6)
				{
					_vertices.push_back(Vector3D(x, y, z));						//	store vertex in [x, y, z] to the array
					_normals.push_back(Vector3D(nx, ny, nz));	//	store vertex normal in [x, y, z] to the array
				}
			}
			else if (hascolors)
			{
				if (std::sscanf(line.c_str(), "%f %f %f %d %d %d", &x, &y, &z, &r, &g, &b) == 6)
				{
					_vertices.push_back(Vector3D(x, y, z));						//	store vertex in [x, y, z] to the array
					_colors.push_back(Color4D(r / 255.f, g / 255.f, b / 255.f, 1.0f));	//	store vertex color in [r, g, b] to the array
				}
			}
		}
		else if (nw == 8)
		{
			if (std::sscanf(line.c_str(), "%f %f %f %f %f %f %f %f", &x, &y, &z, &s, &t, &nx, &ny, &nz) == 8)
			{
				_vertices.push_back(Vector3D(x, y, z));						//	store vertex in [x, y, z] to the array
				if (hastexcoord) _texcoord.push_back(Vector2D(s, t));		//	store texture coordinates in [s, t] to the array
				if (hasnormals) _normals.push_back(Vector3D(nx, ny, nz));	//	store vertex normal in [x, y, z] to the array
			}
		}
		else if (nw == 11)
		{
			if (std::sscanf(line.c_str(), "%f %f %f %f %f %f %f %f %d %d %d", &x, &y, &z, &s, &t, &nx, &ny, &nz, &r, &g, &b) == 11)
			{
				_vertices.push_back(Vector3D(x, y, z));						//	store vertex in [x, y, z] to the array
				if (hastexcoord) _texcoord.push_back(Vector2D(s, t));		//	store texture coordinates in [s, t] to the array
				if (hasnormals) _normals.push_back(Vector3D(nx, ny, nz));	//	store vertex normal in [x, y, z] to the array
				if (hascolors)_colors.push_back(Color4D(r / 255.f, g / 255.f, b / 255.f, 1.0f));	//	store vertex color in [r, g, b] to the array
			}
		}
		else if (nw == 4)
		{
			if (std::sscanf(line.c_str(), "%d %d %d %d", &num, &v1, &v2, &v3) == 4)
			{
				if (num == 3)
					_indices.push_back(FaceIndices3(v1, v2, v3));	//	store indices to the array
			}
		}
	}

	file_op.close();	// in the end, close the file.

	return true;
}
