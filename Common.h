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

struct Voxel
{
	Color boxColor;
	Vector3 Position;
};

class Common
{
public:
	Common();
	~Common();
};

