#pragma once
#include <Polycode.h>
#include <PolycodeView.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <vector>
#include <fstream>
#include <iostream>

namespace ptree = boost::property_tree;

struct Voxel
{
	Color boxColor;
	Vector3 Position;
};

class LoadSave
{
public:
	LoadSave(void);
	~LoadSave(void);

	void SaveEntity(std::vector<Voxel> entity, std::string fileName);
	std::vector<Voxel> LoadEntity(std::string fileName);

private:
	Voxel shape;
};

