#include "Load.h"

Load::Load(void)
{
}

Load::~Load(void)
{
}

std::vector<Voxel> Load::LoadEntity(std::string fileName)
{
	std::vector<Voxel> VOXshape;

	std::ifstream file(fileName);
	if (!file.good())
		return VOXshape;

	ptree::ptree entityDataRead;
	ptree::read_json(fileName, entityDataRead);

	for (ptree::ptree::value_type &row : entityDataRead.get_child("Color"))
	{
		int c = 0;

		Number carray[4];

		for (ptree::ptree::value_type &cell : row.second)
		{
			carray[c] = cell.second.get_value<Number>();
			c++;
		}

		shape.boxColor.r = carray[0];
		shape.boxColor.g = carray[1];
		shape.boxColor.b = carray[2];
		shape.boxColor.a = carray[3];

		VOXshape.push_back(shape);
	}

	int voxRead = 0;

	for (ptree::ptree::value_type &row : entityDataRead.get_child("Position"))
	{
		int p = 0;

		Number parray[3];

		for (ptree::ptree::value_type & cell : row.second)
		{
			parray[p] = cell.second.get_value<Number>();
			p++;
		}

		VOXshape[voxRead].Position.x = parray[0];
		VOXshape[voxRead].Position.y = parray[1];
		VOXshape[voxRead].Position.z = parray[2];

		voxRead++;
	}

	return VOXshape;
}

std::vector<ScenePrimitive*> Load::ReadBoxes(std::string fileName)
{
	std::vector<Voxel> shapeRead;
	std::vector<ScenePrimitive*> boxs;

	shapeRead.clear();
	shapeRead = LoadEntity(fileName + ".json");

	ScenePrimitive *box;

	for (int vox = 0; vox < shapeRead.size(); vox++)
	{
		box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 1, 1);
		box->setMaterialByName("Default");
		box->setPosition(shapeRead[vox].Position);
		box->setColor(shapeRead[vox].boxColor);
		box->id = std::to_string(vox);
		boxs.push_back(box);
	}

	return boxs;
}

void Load::ReadVoxelEntity(Entity *entity, std::vector<ScenePrimitive*> boxs)
{
	for (int box = 0; box < boxs.size(); box++)
	{
		entity->addChild(boxs[box]);
	}
}
