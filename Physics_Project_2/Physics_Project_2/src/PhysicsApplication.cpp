#include "PhysicsApplication.h"
#include "SpaceShip/SpaceShip.h"
#include "City/City.h"

void PhysicsApplication::SetUp()
{
	physicsEngine.fixedStepTime = 0.01f;
	physicsEngine.gravity.y = 0;
	stopKeyCallback = true;
	
	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 1000.0f,65.0f);

	//camera->SetCameraPosition(glm::vec3(7.0f, 20.0f, 25.0f));
	//camera->SetCameraRotation(glm::vec3(-15.0f, -135.0f,0));

	EntityManager::GetInstance().AddToRendererAndPhysics(&renderer, &defShader, &physicsEngine);
	
#pragma region Light
	Model* lightModel = new Model("res/Models/DefaultSphere.fbx", false);
	lightModel->transform.SetScale(glm::vec3(0.01));
	renderer.AddModel(lightModel, &solidColorShader);
	Light* light = new Light();
	light->InitializeLight(lightModel, Directional);
	light->intensity = 2;
	lightManager.AddLight(light);
#pragma endregion

	SpaceShip* spaceShip = new SpaceShip(&alphaBlendShader);
	spaceShip->SetCamera(camera);
	City* city = new City();

	EntityManager::GetInstance().Start();
}

void PhysicsApplication::PreRender()
{

}

void PhysicsApplication::PostRender()
{
	physicsEngine.Update(deltaTime);
	EntityManager::GetInstance().Update(deltaTime);

	//DrawAABBRecursive(buildingPhy->hierarchialAABB->rootNode);
}

void PhysicsApplication::ProcessInput(GLFWwindow* window)
{
	std::stringstream ssTitle;
	ssTitle << "Camera Pos : "
		<< camera->cameraPos.x << " , "
		<< camera->cameraPos.y << " , "
		<< camera->cameraPos.z
		<< "  Camera Pitch : "
		<< camera->cameraPitch
		<< "  Camera Yaw : "
		<< camera->cameraYaw;

	std::string theTitle = ssTitle.str();

	glfwSetWindowTitle(window, theTitle.c_str());
}

void PhysicsApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
	if (action == GLFW_PRESS)
	{
		InputManager::GetInstance().OnKeyPressed(key);
	}
	else if (action == GLFW_RELEASE)
	{
		InputManager::GetInstance().OnKeyReleased(key);
	}
	else if (action == GLFW_REPEAT)
	{
		InputManager::GetInstance().OnKeyHeld(key);
	}
}

void PhysicsApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}


void PhysicsApplication::DrawAABBRecursive(HierarchicalAABBNode* node)
{
	if (node == nullptr) return;

	/*if (node->nodeIndex == aabbDrawDepthIndex)
	{
		renderer.DrawAABB(GetGraphicsAabb(node->GetModelAABB()), aabbColor[2]);
		return;
	}*/

	if (node->triangleIndices.size() != 0)
	{
		renderer.DrawAABB(GetGraphicsAabb(node->GetModelAABB()), aabbColor[2]);
	}

	if (node->leftNode == nullptr) return;

	DrawAABBRecursive(node->leftNode);
	DrawAABBRecursive(node->rightNode);

}