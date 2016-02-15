#pragma once
#include "Common.h"

namespace ptree = boost::property_tree;

class Load
{
public:
	Load(void);
	~Load(void);

	std::vector<ScenePrimitive*> ReadBoxes(std::string fileName);
	void ReadVoxelEntity(Entity *entity, std::vector<ScenePrimitive*> boxs);

private:
	Voxel shape;

	std::vector<Voxel> LoadEntity(std::string fileName);
};

