#include "LoadSave.h"

LoadSave::LoadSave(void)
{
}

LoadSave::~LoadSave(void)
{
}

void LoadSave::SaveEntity(std::vector<Voxel> VOXshape, std::string fileName)
{
	ptree::ptree entityData;
	ptree::ptree voxColor;
	ptree::ptree voxPosition;
	
	for (int vox = 0; vox < VOXshape.size(); vox++)
	{
	
		Number carray[4] = { VOXshape[vox].boxColor.r, VOXshape[vox].boxColor.g, VOXshape[vox].boxColor.b,
			VOXshape[vox].boxColor.a };
		
		ptree::ptree crow;
	
		for (int c = 0; c < 4; c++)
		{
			ptree::ptree cell;
			cell.put_value(carray[c]);
			crow.push_back(std::make_pair("", cell));
		}
		
		voxColor.push_back(std::make_pair("", crow));
	
		Number parray[3] = { VOXshape[vox].Position.x, VOXshape[vox].Position.y, VOXshape[vox].Position.z };
	
		ptree::ptree prow;
	
		for (int p = 0; p < 3; p++)
		{
			ptree::ptree cell;
			cell.put_value(parray[p]);
			prow.push_back(std::make_pair("", cell));
		}
		voxPosition.push_back(std::make_pair("", prow));
	
	}
	
	entityData.add_child("Color", voxColor);
	entityData.add_child("Position", voxPosition);

	ptree::write_json(fileName + ".JSON", entityData);
}

std::vector<Voxel> LoadSave::LoadEntity(std::string fileName)
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
