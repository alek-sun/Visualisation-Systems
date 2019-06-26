#pragma once
#include <list>
#include <vector>

class Camera;
class Light;
class Object;


class Scene
{
public:

	void Init();
	void Deinit();

	void AddObject	(Object * pObject);
	void AddLight	(Light * pLight);

	void SetSelectedObject(Object * pObject);
	Object * GetSelectedObject();
	
	void SetCamera	(Camera * pCamera);
	//Camera &		GetCamera() const;
	Camera *		GetCamera();
	
	const std::list<const Light *> & GetLights() const;

	const std::vector<const Object *> & GetObjects() const;
	
	void Update();
	void Render();

private:
	std::vector<const Object *>	m_objects;
	std::list<const Light *>	m_lights;
	Camera *					m_pCamera;
	Object *					m_pSelectedObject;
};
