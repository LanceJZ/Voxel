#include "Game.h"

Game::Game(PolycodeView *view) : EventHandler()
{
	m_Exit = false;
	pCore = new POLYCODE_CORE(view, 1200, 800, false, true, 0, 0, 90, 0, true);
	pScene = new Scene(Scene::SCENE_3D);
	pCore->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);

	pBoxs = new Entity();
	pCurser = new SceneMesh(Mesh::LINE_MESH);
	pScene->addChild(pBoxs);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", true);

	pCurser->getMesh()->addVertex(0.51, -0.51, 0.51); //00 
	pCurser->getMesh()->addVertex(-0.51, -0.51, 0.51); //00

	pCurser->getMesh()->addVertex(0.51, 0.51, 0.51); //01
	pCurser->getMesh()->addVertex(0.51, -0.51, 0.51); //01

	pCurser->getMesh()->addVertex(0.51, 0.51, 0.51); //02
	pCurser->getMesh()->addVertex(-0.51, 0.51, 0.51); //02

	pCurser->getMesh()->addVertex(-0.51, 0.51, 0.51); //03
	pCurser->getMesh()->addVertex(-0.51, -0.51, 0.51); //03//

	pCurser->getMesh()->addVertex(-0.51, -0.51, -0.51); //04
	pCurser->getMesh()->addVertex(0.51, -0.51, -0.51); //04

	pCurser->getMesh()->addVertex(0.51, 0.51, -0.51); //05
	pCurser->getMesh()->addVertex(0.51, -0.51, -0.51); //05

	pCurser->getMesh()->addVertex(0.51, 0.51, -0.51); //06
	pCurser->getMesh()->addVertex(-0.51, 0.51, -0.51); //06

	pCurser->getMesh()->addVertex(-0.51, 0.51, -0.51); //07
	pCurser->getMesh()->addVertex(-0.51, -0.51, -0.51); //07//

	pCurser->getMesh()->addVertex(-0.51, -0.51, -0.51); //08
	pCurser->getMesh()->addVertex(-0.51, -0.51, 0.51); //08

	pCurser->getMesh()->addVertex(0.51, -0.51, -0.51); //09
	pCurser->getMesh()->addVertex(0.51, -0.51, 0.51); //09

	pCurser->getMesh()->addVertex(0.51, 0.51, -0.51); //10
	pCurser->getMesh()->addVertex(0.51, 0.51, 0.51); //10

	pCurser->getMesh()->addVertex(-0.51, 0.51, -0.51); //11
	pCurser->getMesh()->addVertex(-0.51, 0.51, 0.51); //11//

	pBoxs->addChild(pCurser);

	SceneLight *light = new SceneLight(SceneLight::POINT_LIGHT, pScene, 12250);
	light->setPosition(50, 70, 80);
	light->setLightColor(1, 1, 1);
	pScene->addLight(light);

	light = new SceneLight(SceneLight::POINT_LIGHT, pScene, 5800);
	light->setPosition(-50, 70, 80);
	light->setLightColor(1, 1, 1);
	pScene->addLight(light);

	light = new SceneLight(SceneLight::POINT_LIGHT, pScene, 3600);
	light->setPosition(-50, -70, 80);
	light->setLightColor(1, 1, 1);
	pScene->addLight(light);

	m_CameraRotation = 0.0;

	//UI ---------------------------------------------------------------------------------
	CoreServices::getInstance()->getResourceManager()->addArchive("UIThemes/UIThemes.pak");
	CoreServices::getInstance()->getConfig()->loadConfig("Polycode", "UIThemes/dark/theme.xml");

	Services()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
	Scene *scene2D = new Scene(Scene::SCENE_2D_TOPLEFT);
	scene2D->rootEntity.processInputEvents = true;

	SceneLabel::defaultAnchor = Vector3(-1.0, -1.0, 0.0);
	SceneLabel::defaultPositionAtBaseline = true;
	SceneLabel::defaultSnapToPixels = true;
	SceneLabel::createMipmapsForLabels = false;

	m_Window = new UIWindow("Voxel Edit", 350, 250);
	scene2D->addChild(m_Window);

	UILabel *name = new UILabel("Enter File Name:", 14, "sans", Label::ANTIALIAS_FULL);
	name->setPosition(m_Window->padding, m_Window->topPadding);
	m_Window->addChild(name);

	m_XYZCords = new UILabel("X-000, Y-000, Z-000", 14, "sans", Label::ANTIALIAS_FULL);
	m_XYZCords->setPosition(m_Window->padding + 10, m_Window->getHeight() - m_Window->topPadding - 5);
	m_Window->addChild(m_XYZCords);

	m_NameInput = new UITextInput(false, 200, 12);
	m_NameInput->setPosition(m_Window->padding, m_Window->topPadding + 20);
	m_Window->addChild(m_NameInput);

	m_LoadButton = new UIButton("Load", 60);
	m_LoadButton->setPosition(m_Window->padding + 225, m_Window->topPadding + 30);
	m_LoadButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_LoadButton);

	m_SaveButton = new UIButton("Save", 60);
	m_SaveButton->setPosition(m_Window->padding + 225, m_Window->topPadding);
	m_SaveButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_SaveButton);

	m_CloseButton = new UIButton("Close", 60);
	m_CloseButton->setPosition(m_Window->padding, m_Window->getHeight() - m_Window->topPadding - 35);
	m_CloseButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_CloseButton);

	m_SpinButton = new UIButton("Spin", 60);
	m_SpinButton->setPosition(m_Window->padding + 80, m_Window->getHeight() - m_Window->topPadding - 35);
	m_SpinButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_SpinButton);

	m_FlipButton = new UIButton("Flip", 60);
	m_FlipButton->setPosition(m_Window->padding + 150, m_Window->getHeight() - m_Window->topPadding - 35);
	m_FlipButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_FlipButton);

	m_ZoomIn = new UIButton("Zoom In", 70);
	m_ZoomIn->setPosition(m_Window->padding + 50, m_Window->getHeight() - m_Window->topPadding - 65);
	m_ZoomIn->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_ZoomIn);

	m_ZoomOut = new UIButton("Zoom Out", 70);
	m_ZoomOut->setPosition(m_Window->padding + 130, m_Window->getHeight() - m_Window->topPadding - 65);
	m_ZoomOut->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_ZoomOut);

	m_AddBox = new UIButton("Add", 50);
	m_AddBox->setPosition(m_Window->padding + 230, m_Window->topPadding + 90);
	m_AddBox->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_AddBox);

	m_RemoveBox = new UIButton("Remove", 70);
	m_RemoveBox->setPosition(m_Window->padding + 220, m_Window->topPadding + 60);
	m_RemoveBox->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_RemoveBox);

	m_ColorGrab = new UIButton("Grab Color", 80);
	m_ColorGrab->setPosition(m_Window->padding + 50, m_Window->topPadding + 100);
	m_ColorGrab->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_ColorGrab);

	m_ChangeColor = new UIButton("Change Color", 90);
	m_ChangeColor->setPosition(m_Window->padding + 45, m_Window->topPadding + 130);
	m_ChangeColor->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_ChangeColor);

	UIColorPicker *colorPicker;
	colorPicker = new UIColorPicker();
	colorPicker->setPosition(470, 0);
	colorPicker->setContinuous(false);
	scene2D->addChild(colorPicker);

	m_ColorBox = new UIColorBox(colorPicker, Color(1.0, 1.0, 1.0, 1.0), 50, 50);
	m_ColorBox->setBoxColor(Color(1.0, 1.0, 1.0, 1.0));
	m_ColorBox->setPosition(m_Window->padding + 140, m_Window->topPadding + 100);
	m_Window->addChild(m_ColorBox);

	Number moveButtonsX = 230;
	Number moveButtonsY = 125;

	m_PlusY = new UIButton("Y+", 23);
	m_PlusY->setPosition(m_Window->padding + moveButtonsX + 40, m_Window->topPadding + moveButtonsY + 10);
	m_PlusY->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_PlusY);

	m_PlusX = new UIButton("X+", 23);
	m_PlusX->setPosition(m_Window->padding + moveButtonsX + 70, m_Window->topPadding + moveButtonsY + 40);
	m_PlusX->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_PlusX);

	m_PlusZ = new UIButton("Z+", 23);
	m_PlusZ->setPosition(m_Window->padding + moveButtonsX + 80, m_Window->topPadding + moveButtonsY + 80);
	m_PlusZ->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_PlusZ);

	m_MinusY = new UIButton("Y-", 23);
	m_MinusY->setPosition(m_Window->padding + moveButtonsX + 40, m_Window->topPadding + moveButtonsY + 70);
	m_MinusY->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_MinusY);

	m_MinusX = new UIButton("X-", 23);
	m_MinusX->setPosition(m_Window->padding + moveButtonsX + 10, m_Window->topPadding + moveButtonsY + 40);
	m_MinusX->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_MinusX);

	m_MinusZ = new UIButton("Z-", 23);
	m_MinusZ->setPosition(m_Window->padding + moveButtonsX, m_Window->topPadding + moveButtonsY);
	m_MinusZ->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_MinusZ);

	m_RotateX = new UICheckBox("RotateX", false);
	m_RotateX->setPosition(m_Window->padding, m_Window->topPadding + 50);
	m_Window->addChild(m_RotateX);

	m_RotateY = new UICheckBox("RotateY", false);
	m_RotateY->setPosition(m_Window->padding + 100, m_Window->topPadding + 50);
	m_Window->addChild(m_RotateY);

	m_RotateZ = new UICheckBox("RotateZ", false);
	m_RotateZ->setPosition(m_Window->padding, m_Window->topPadding + 70);
	m_Window->addChild(m_RotateZ);

	m_ResetButton = new UIButton("Reset", 60);
	m_ResetButton->setPosition(m_Window->padding + 100, m_Window->topPadding + 70);
	m_ResetButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_ResetButton);

	m_TopButton = new UIButton("Top", 50);
	m_TopButton->setPosition(m_Window->padding + 300, m_Window->topPadding + 70);
	m_TopButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_TopButton);

	m_SideButton = new UIButton("Side", 50);
	m_SideButton->setPosition(m_Window->padding + 300, m_Window->topPadding + 95);
	m_SideButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_SideButton);

	m_FrontButton = new UIButton("Front", 50);
	m_FrontButton->setPosition(m_Window->padding + 300, m_Window->topPadding + 120);
	m_FrontButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_FrontButton);

	UpdateXYZ();
	Reset();

	//shape.boxColor = Color(0.8, 0.3, 0.5, 1.0);
	//shape.Position = Vector3(0.0, 0.0, 0.0);
	//m_Shape.push_back(shape);
	//shape.boxColor = Color(0.8, 0.5, 0.4, 1.0);
	//shape.Position = Vector3(1.01, 1.01, 0.0);
	//m_Shape.push_back(shape);
	//shape.boxColor = Color(0.8, 0.5, 0.4, 1.0);
	//shape.Position = Vector3(1.01, -1.01, 0.0);
	//m_Shape.push_back(shape);
	//shape.boxColor = Color(0.5, 0.3, 0.8, 1.0);
	//shape.Position = Vector3(1.01, 2.02, 0.0);
	//m_Shape.push_back(shape);
	//shape.boxColor = Color(0.3, 0.2, 0.6, 1.0);
	//shape.Position = Vector3(-1.01, 1.01, 0.0);
	//m_Shape.push_back(shape);
	//shape.boxColor = Color(0.4, 0.1, 0.7, 1.0);
	//shape.Position = Vector3(-1.01, -1.01, 0.0);
	//m_Shape.push_back(shape);
}

Game::~Game()
{
}

void Game::handleEvent(Event * events)
{
	if (events->getEventCode() == UIEvent::CLICK_EVENT)
	{
		if (events->getDispatcher() == m_TopButton)
		{
			Reset();
			m_CameraPosition.x = 0;
			m_CameraPosition.y = 0;
			pBoxs->Pitch(90);
			pBoxs->Roll(90);
		}

		if (events->getDispatcher() == m_SideButton)
		{
			Reset();
			m_CameraPosition.x = 0;
			m_CameraPosition.y = 0;			
		}

		if (events->getDispatcher() == m_FrontButton)
		{
			Reset();
			m_CameraPosition.x = 0;
			m_CameraPosition.y = 0;
			pBoxs->Yaw(-90);
		}

		if (events->getDispatcher() == m_CloseButton)
		{
			m_Exit = true;
		}

		if (events->getDispatcher() == m_LoadButton)
		{
			m_FileName = m_NameInput->getText().c_str();
			ReadVoxEntity();
		}

		if (events->getDispatcher() == m_SaveButton)
		{
			Save();
		}

		if (events->getDispatcher() == m_AddBox)
		{
			AddBox();
		}

		if (events->getDispatcher() == m_ColorGrab)
		{
			ColorGrab();
		}

		if (events->getDispatcher() == m_ChangeColor)
		{
			ChangeColor();
		}

		if (events->getDispatcher() == m_RemoveBox)
		{
			RemoveBox();
		}

		Number move = 1.01;

		if (events->getDispatcher() == m_PlusX)
		{
			pCurser->setPositionX(pCurser->getPosition().x + move);
			UpdateXYZ();
		}

		if (events->getDispatcher() == m_PlusY)
		{
			pCurser->setPositionY(pCurser->getPosition().y + move);
			UpdateXYZ();
		}

		if (events->getDispatcher() == m_PlusZ)
		{
			pCurser->setPositionZ(pCurser->getPosition().z + move);
			UpdateXYZ();
		}

		if (events->getDispatcher() == m_MinusX)
		{
			pCurser->setPositionX(pCurser->getPosition().x - move);
			UpdateXYZ();
		}

		if (events->getDispatcher() == m_MinusY)
		{
			pCurser->setPositionY(pCurser->getPosition().y - move);
			UpdateXYZ();
		}

		if (events->getDispatcher() == m_MinusZ)
		{
			pCurser->setPositionZ(pCurser->getPosition().z - move);
			UpdateXYZ();
		}

		if (events->getDispatcher() == m_SpinButton)
		{
			pBoxs->Yaw(180);
			UpdateXYZ();
		}

		if (events->getDispatcher() == m_FlipButton)
		{
			pBoxs->Roll(180);
			UpdateXYZ();
		}

		if (events->getDispatcher() == m_ResetButton)
		{
			Reset();
		}

		if (events->getDispatcher() == m_ZoomIn)
		{
			if (m_CameraPosition.z > 5)
				m_CameraPosition.z-=3;
		}

		if (events->getDispatcher() == m_ZoomOut)
		{
			if (m_CameraPosition.z < 100)
				m_CameraPosition.z+=3;
		}
	}

	if (events->getDispatcher() == pCore->getInput())
	{

		InputEvent *inputEvent = (InputEvent*)events;

		if (inputEvent->keyCode() == KEY_ESCAPE)
			m_Exit = true;

		if (inputEvent->keyCode() == KEY_INSERT)
			m_Window->showWindow();


		Number move = 1.01;

		if (inputEvent->keyCode() == KEY_RIGHT)
		{
			pCurser->setPositionX(pCurser->getPosition().x + move);
			UpdateXYZ();
		}

		if (inputEvent->keyCode() == KEY_UP)
		{
			pCurser->setPositionY(pCurser->getPosition().y + move);
			UpdateXYZ();
		}

		if (inputEvent->keyCode() == KEY_PAGEDOWN)
		{
			pCurser->setPositionZ(pCurser->getPosition().z + move);
			UpdateXYZ();
		}

		if (inputEvent->keyCode() == KEY_LEFT)
		{
			pCurser->setPositionX(pCurser->getPosition().x - move);
			UpdateXYZ();
		}

		if (inputEvent->keyCode() == KEY_DOWN)
		{
			pCurser->setPositionY(pCurser->getPosition().y - move);
			UpdateXYZ();
		}

		if (inputEvent->keyCode() == KEY_PAGEUP)
		{
			pCurser->setPositionZ(pCurser->getPosition().z - move);
			UpdateXYZ();
		}

		if (inputEvent->keyCode() == KEY_LCTRL)
		{
			AddBox();
		}

		if (inputEvent->keyCode() == KEY_RCTRL)
		{
			RemoveBox();
		}
	}
}

bool Game::Update()
{
	if (m_RotateX->isChecked())
		pBoxs->Pitch(pCore->getElapsed() * 25);

	if (m_RotateY->isChecked())
		pBoxs->Roll(pCore->getElapsed() * 25);

	if (m_RotateZ->isChecked())
		pBoxs->Yaw(pCore->getElapsed() * 25);

	//m_CameraRotation += pCore->getElapsed() * 0.15;

	//pScene->getDefaultCamera()->setPosition(sin(m_CameraRotation) * 30.0 + 10, cos(m_CameraRotation) * 30.0 + 10, 10);
	pScene->getDefaultCamera()->setPosition(m_CameraPosition);
	pScene->getDefaultCamera()->lookAt(Vector3(0, 0, 0));

	if (m_Exit)
	{
		return false;
	}

	return pCore->updateAndRender();
}

void Game::ReadVoxEntity(void)
{
	for (int vox = 0; vox < m_Boxs.size(); vox++)
	{
		pBoxs->removeChild(m_Boxs[vox]);
	}

	m_Boxs.clear();
	m_Boxs = Load::ReadBoxes(m_FileName);
	
	Load::ReadVoxelEntity(pBoxs, m_Boxs);

	pCurser->setPosition(0);
	UpdateXYZ();
}

void Game::UpdateXYZ(void)
{
	m_XYZCords->setText("X:" + to_string(pCurser->getPosition().x) + " Y:" + to_string(pCurser->getPosition().y)
		+ " Z:" + to_string(pCurser->getPosition().z));
}

void Game::ChangeColor(void)
{
	for (int vox = 0; vox < m_Boxs.size(); vox++)
	{
		if (CheckBoxMatch(m_Boxs[vox]->getPosition(), pCurser->getPosition()))
		{			
			m_Boxs[vox]->setColor(m_ColorBox->getSelectedColor());
		}
	}
}

void Game::AddBox(void)
{
	bool clearToAdd = true;

	for (int vox = 0; vox < m_Boxs.size(); vox++)
	{
		if (CheckBoxMatch(m_Boxs[vox]->getPosition(), pCurser->getPosition()))
		{
			clearToAdd = false;
		}
	}

	if (clearToAdd)
	{
		ScenePrimitive *box;

		box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 1, 1);
		box->setMaterialByName("Default");
		box->setPosition(pCurser->getPosition());
		box->setColor(m_ColorBox->getSelectedColor());
		box->id = std::to_string(m_Boxs.size());
		pBoxs->addChild(box);
		m_Boxs.push_back(box);
	}
}

void Game::RemoveBox(void)
{
	for (int vox = 0; vox < m_Boxs.size(); vox++)
	{
		if (CheckBoxMatch(m_Boxs[vox]->getPosition(), pCurser->getPosition()))
		{
			pBoxs->removeChild(m_Boxs[vox]);
			m_Boxs.erase(m_Boxs.begin() + vox);
		}
	}
}

void Game::Save(void)
{
	if (m_NameInput->getText().size() > 2 && m_Boxs.size() > 0)
	{
		m_ShapeSave.clear();

		for (int vox = 0; vox < m_Boxs.size(); vox++)
		{
			Voxel shape;
			shape.boxColor = m_Boxs[vox]->color;
			shape.Position = m_Boxs[vox]->getPosition();
			m_ShapeSave.push_back(shape);
		}

		m_FileName = m_NameInput->getText().c_str();
		Save::WriteEntity(m_ShapeSave, m_FileName);
	}
}

void Game::ColorGrab(void)
{
	for (int vox = 0; vox < m_Boxs.size(); vox++)
	{
		if (CheckBoxMatch(m_Boxs[vox]->getPosition(), pCurser->getPosition()))
		{
			m_ColorBox->setBoxColor(m_Boxs[vox]->color);
		}
	}
}

void Game::Reset(void)
{
	m_CameraPosition = Vector3(-6, 8, 20);
	pBoxs->setRotationEuler(0);
	m_RotateX->setChecked(false);
	m_RotateY->setChecked(false);
	m_RotateZ->setChecked(false);
}

bool Game::CheckBoxMatch(Vector3 positionBox, Vector3 positionCursor)
{
	int xCur = positionCursor.x;
	int yCur = positionCursor.y;
	int zCur = positionCursor.z;
	int xBox = positionBox.x;
	int yBox = positionBox.y;
	int zBox = positionBox.z;

	if (xCur == xBox && yCur == yBox && zCur == zBox)
		return true;

	return false;
}
