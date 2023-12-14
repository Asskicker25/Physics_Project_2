#include "ImpactSpheres.h"

ImpactSpheres::ImpactSpheres()
{
	model = new Model("res/Models/DefaultSphere.fbx");
	model->transform.SetScale(glm::vec3(1.0f));
	model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.8f, 0.0, 0.6f, 1.0f));

	InitializeEntity(this);
}

ImpactSpheres& ImpactSpheres::GetInstance()
{
	static ImpactSpheres instance;
	return instance;
}

void ImpactSpheres::AddCollisionPoint(const glm::vec3& point)
{
	if (!canAddPoint) return;

	Model* sphere = new Model();
	sphere->CopyFromModel(*model);
	sphere->transform.SetPosition(point);

	renderer->AddModel(sphere, shader);

	canAddPoint = false;
	timeStep = 0;
}

void ImpactSpheres::CalcualteTime(float deltaTime)
{
	if (canAddPoint) return;

	timeStep += deltaTime;

	if (timeStep >= addInterval)
	{
		canAddPoint = true;
		timeStep = 0;
	}

}

void ImpactSpheres::Start()
{
}

void ImpactSpheres::Update(float deltaTime)
{
	CalcualteTime(deltaTime);
}

void ImpactSpheres::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
}

void ImpactSpheres::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
