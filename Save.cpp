#include "Save.h"

Save::Save()
{
}

Save::~Save()
{
}

void Save::WriteEntity(std::vector<Voxel> VOXshape, std::string fileName)
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

		int parray[3] = { int(VOXshape[vox].Position.x), int(VOXshape[vox].Position.y),
			int(VOXshape[vox].Position.z) };

		ptree::ptree prow;

		for (int p = 0; p < 3; p++)
		{
			ptree::ptree cell;

			if (parray[p] != 0)
				cell.put_value(parray[p] + (parray[p] * 0.01));
			else
				cell.put_value(0);

			prow.push_back(std::make_pair("", cell));
		}
		voxPosition.push_back(std::make_pair("", prow));

	}

	entityData.add_child("Color", voxColor);
	entityData.add_child("Position", voxPosition);

	ptree::write_json(fileName + ".JSON", entityData);
}