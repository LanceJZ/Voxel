#pragma once
#include "LoadSave.h"
#include <Polycode.h>
#include <PolycodeView.h>
#include <PolycodeUI.h>
#include <vector>

namespace ptree = boost::property_tree;
using namespace Polycode;

class Game : public LoadSave, public EventHandler
{
public:
	Game(PolycodeView *view);
	~Game();

	void handleEvent(Event *events);
	bool Update(void);

private:
	Core *pCore;
	Scene *pScene;
	Entity *pBoxs;
	SceneMesh * pCurser;
	Number cameraRotation;
	
	std::vector<ScenePrimitive*> m_Boxs;
	std::vector<Voxel> m_ShapeSave;
	std::vector<Voxel> m_ShapeRead;

	bool m_Exit;
	std::string m_FileName;

	UITextInput *m_NameInput;
	UITextInput *m_ColorRInput;
	UITextInput *m_ColorGInput;
	UITextInput *m_ColorBInput;
	UITextInput *m_ColorAInput;
	UIButton *m_CloseButton;
	UIButton *m_SpinButton;
	UIButton *m_FlipButton;
	UIButton *m_LoadButton;
	UIButton *m_SaveButton;
	UIButton *m_AddBox;
	UIButton *m_RemoveBox;
	UIButton *m_PlusX;
	UIButton *m_PlusY;
	UIButton *m_PlusZ;
	UIButton *m_MinusX;
	UIButton *m_MinusY;
	UIButton *m_MinusZ;

	void ReadVoxEntity(void);
};

