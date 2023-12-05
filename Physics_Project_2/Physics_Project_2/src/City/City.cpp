#include "City.h"

City::City()
{
	model = new Model();
	phyObj = new PhysicsObject();
	InitializeEntity(this);
}

void City::Start()
{
}

void City::Update(float deltaTime)
{
}

void City::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/FullCity/FullCity.fbx");
	model->transform.SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	model->transform.SetScale(glm::vec3(.5f));
	renderer->AddModel(model, shader);

	phyObj = new PhysicsObject();
	phyObj->maxDepth = 20;
	phyObj->Initialize(model, MESH_OF_TRIANGLES, STATIC);
	physicsEngine->AddPhysicsObject(phyObj);
}

void City::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void City::OnKeyPressed(const int& key)
{
}

void City::OnKeyReleased(const int& key)
{
}

void City::OnKeyHeld(const int& key)
{
}
