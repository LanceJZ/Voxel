#pragma once
#include "Load.h"
#include "Save.h"
#include <Polycode.h>
#include <PolycodeView.h>
#include <PolycodeUI.h>
#include <vector>

namespace ptree = boost::property_tree;
using namespace Polycode;

class Game : public Load, public Save, public EventHandler
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
	Number m_CameraRotation;
	
	std::vector<ScenePrimitive*> m_Boxs;
	std::vector<Voxel> m_ShapeSave;
	std::vector<Voxel> m_ShapeRead;

	bool m_Exit;

	std::string m_FileName;
	Vector3 m_CameraPosition;

	UIWindow *m_Window;
	UITextInput *m_NameInput;
	UITextInput *m_ColorRInput;
	UITextInput *m_ColorGInput;
	UITextInput *m_ColorBInput;
	UITextInput *m_ColorAInput;
	UILabel *m_XYZCords;
	UIColorBox *m_ColorBox;
	UIButton *m_CloseButton;
	UIButton *m_SpinButton;
	UIButton *m_FlipButton;
	UIButton *m_ResetButton;
	UIButton *m_ColorGrab;
	UIButton *m_ZoomIn;
	UIButton *m_ZoomOut;
	UIButton *m_ChangeColor;
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
	UIButton *m_TopButton;
	UIButton *m_SideButton;
	UIButton *m_FrontButton;
	UICheckBox *m_RotateX;
	UICheckBox *m_RotateY;
	UICheckBox *m_RotateZ;

	void ReadVoxEntity(void);
	void UpdateXYZ(void);
	void ChangeColor(void);
	void AddBox(void);
	void RemoveBox(void);
	void Save(void);
	void ColorGrab(void);
	void Reset(void);

	bool CheckBoxMatch(Vector3 positionBox, Vector3 positionCursor);
};

