#pragma once
#include <list>


class Material;
class Mesh;
class Component;
class Transform;


/**
* @brief Basic class for all objects in a scene.
*/
class Object
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] name The object's name.
	*/
	Object(const char * name = NULL);
	
	/**
	* @brief Releases resources.
	*/
	~Object();

	/**
	* @brief Initializes all members including components.
	*/
	void Init();
	
	/**
	* @brief Adds custom components to the object.
	* @param [in] pComponent Component to add.
	*/
	void AddComponent(Component * pComponent);

	/**
	* @brief Is the object active ?
	* If true then the object is rendered and Update() is called at each frame.
	*/
	bool IsActive() const;

	/**
	* @brief Set the object active/inactive.
	* If true then the object is rendered and Update() is called at each frame.
	* @param [in] isActive Active/inactive.
	*/
	void SetActive(bool isActive);
	
	/**
	* @brief Is called at each frame.
	* Executes all component's Update() at each frame.
	*/
	void Update() const;

	/**
	* @brief Contains World matrix (position, rotation, scale).
	*/
	Transform * m_pTransform;

	/**
	* @brief Contains mesh (vertex & index buffers).
	*/
	Mesh *		m_pMesh;

	/**
	* @brief Contains Vertex & Pixel Shaders.
	*/
	Material *	m_pMaterial;

	/**
	* @brief Contains custom scripts.
	*/
	std::list<Component *> m_components;

	/**
	* @brief The object's name.
	*/
	std::string m_name;

	/**
	* @brief The object is active/inactive.
	* If true then the object is rendered and Update() is called at each frame.
	*/
	bool m_isActive;
};
