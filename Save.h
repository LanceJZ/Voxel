#pragma once
#include "Common.h"

namespace ptree = boost::property_tree; 

class Save
{
public:
	Save(void);
	~Save(void);

	void WriteEntity(std::vector<Voxel> VOXshape, std::string fileName);

private:
	Voxel shape;	
};

