#include "Game.h"

Game::Game(PolycodeView *view) : EventHandler()
{
	m_Exit = false;
	pCore = new POLYCODE_CORE(view, 800, 600, false, true, 0, 0, 90, 0, true);
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

	cameraRotation = 0.0;

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

	m_Window = new UIWindow("Voxel Edit", 300, 250);
	scene2D->addChild(m_Window);

	UILabel *name = new UILabel("Enter File Name:", 14, "sans", Label::ANTIALIAS_FULL);
	name->setPosition(m_Window->padding, m_Window->topPadding);
	m_Window->addChild(name);

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
	m_CloseButton->setPosition(m_Window->padding, m_Window->getHeight() - m_Window->topPadding - 20);
	m_CloseButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_CloseButton);

	m_SpinButton = new UIButton("Spin", 60);
	m_SpinButton->setPosition(m_Window->padding + 80, m_Window->getHeight() - m_Window->topPadding - 20);
	m_SpinButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_SpinButton);

	m_FlipButton = new UIButton("Flip", 60);
	m_FlipButton->setPosition(m_Window->padding + 150, m_Window->getHeight() - m_Window->topPadding - 20);
	m_FlipButton->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_FlipButton);

	m_AddBox = new UIButton("Add", 50);
	m_AddBox->setPosition(m_Window->padding + 170, m_Window->topPadding + 60);
	m_AddBox->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_AddBox);

	m_RemoveBox = new UIButton("Remove", 70);
	m_RemoveBox->setPosition(m_Window->padding + 230, m_Window->topPadding + 60);
	m_RemoveBox->addEventListener(this, UIEvent::CLICK_EVENT);
	m_Window->addChild(m_RemoveBox);

	m_ColorPicker = new UIColorPicker();
	m_ColorPicker->setPosition(450, 0);
	m_ColorPicker->setContinuous(false);
	scene2D->addChild(m_ColorPicker);

	m_ColorBox = new UIColorBox(m_ColorPicker, Color(1.0, 1.0, 1.0, 1.0), 50, 50);
	m_ColorBox->setBoxColor(Color(1.0, 1.0, 1.0, 1.0));
	m_ColorBox->setPosition(m_Window->padding + 140, m_Window->topPadding + 100);
	m_ColorBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	m_Window->addChild(m_ColorBox);

	Number moveButtonsY = 100;
	Number moveButtonsX = 200;

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
	if (events->getEventCode() == UIEvent::CHANGE_EVENT)
	{
		if (events->getDispatcher() == m_ColorBox)
		{
			
		}
	}

	if (events->getEventCode() == UIEvent::CLICK_EVENT)
	{

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
				SaveEntity(m_ShapeSave, m_FileName);
			}
		}

		if (events->getDispatcher() == m_AddBox)
		{
			bool clearToAdd = true;

			for (int vox = 0; vox < m_Boxs.size(); vox++)
			{
				if (m_Boxs[vox]->getPosition() == pCurser->getPosition())
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

		if (events->getDispatcher() == m_RemoveBox)
		{
			for (int vox = 0; vox < m_Boxs.size(); vox++)
			{
				if (m_Boxs[vox]->getPosition() == pCurser->getPosition())
				{
					pBoxs->removeChild(m_Boxs[vox]);
					m_Boxs.erase(m_Boxs.begin() + vox);
				}
			}
		}

		if (events->getDispatcher() == m_PlusX)
		{
			pCurser->setPositionX(pCurser->getPosition().x + 1.01);
		}

		if (events->getDispatcher() == m_PlusY)
		{
			pCurser->setPositionY(pCurser->getPosition().y + 1.01);
		}

		if (events->getDispatcher() == m_PlusZ)
		{
			pCurser->setPositionZ(pCurser->getPosition().z + 1.01);
		}

		if (events->getDispatcher() == m_MinusX)
		{
			pCurser->setPositionX(pCurser->getPosition().x - 1.01);
		}

		if (events->getDispatcher() == m_MinusY)
		{
			pCurser->setPositionY(pCurser->getPosition().y - 1.01);
		}

		if (events->getDispatcher() == m_MinusZ)
		{
			pCurser->setPositionZ(pCurser->getPosition().z - 1.01);
		}

		if (events->getDispatcher() == m_SpinButton)
		{
			pBoxs->Yaw(180);
		}

		if (events->getDispatcher() == m_FlipButton)
		{
			pBoxs->Roll(180);
		}
	}

	if (events->getDispatcher() == m_Window)
	{
		m_Window->showWindow();
	}

	if (events->getDispatcher() == pCore->getInput())
	{

		InputEvent *inputEvent = (InputEvent*)events;

		if (inputEvent->keyCode() == KEY_ESCAPE)
			m_Exit = true;
	}
}

bool Game::Update()
{
	//pBoxs->Yaw(pCore->getElapsed() * 25);
	//pBoxs->Pitch(pCore->getElapsed() * 10);
	//pBoxs->Roll(pCore->getElapsed() * 15);

	//cameraRotation += pCore->getElapsed() * 0.15;

	//pScene->getDefaultCamera()->setPosition(sin(cameraRotation) * 30.0 + 10, cos(cameraRotation) * 30.0 + 10, 10);
	pScene->getDefaultCamera()->setPosition(-5, 7, 10);
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

	m_ShapeRead.clear();
	m_ShapeRead = LoadSave::LoadEntity(m_FileName + ".json");

	m_Boxs.clear();
	ScenePrimitive *box;

	for (int vox = 0; vox < m_ShapeRead.size(); vox++)
	{
		box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 1, 1);
		box->setMaterialByName("Default");
		box->setPosition(m_ShapeRead[vox].Position);
		box->setColor(m_ShapeRead[vox].boxColor);
		box->id = std::to_string(vox);
		pBoxs->addChild(box);
		m_Boxs.push_back(box);
	}
}
