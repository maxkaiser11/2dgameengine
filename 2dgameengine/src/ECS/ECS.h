#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <cerrno>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

//////////////////////////////////////////////////////////////////////
// Signature
// //////////////////////////////////////////////////////////////////
// We use a bitset (1s and 0s) to keep track of which components an entity has,
// and also helps keep track of entities a system is interested in.
// /////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> Signature;

struct BaseComponent
{
protected:
	static int nextId;
};

// Used to assigna unique id to a component type
template <typename T>
class Component: public BaseComponent 
{
	// retuirns the unique id of component<T>
	static int GetId()
	{
		static auto id = nextId++;
		return id;
	}
};

class Entity {
private:
  int id;

public:
  Entity(int id) : id(id){};
  int GetId() const;
};

//////////////////////////////////////////////////////////////////////
// System
// /////////////////////////////////////////////////////////////////
// The system processes entities that contain a specific signature
// ////////////////////////////////////////////////////////////////
class System {
private:
  Signature componentSignature;
  std::vector<Entity> entities;

public:
  System() = default;
  ~System() = default;

  void AddEntityToSystem(Entity entity);
  void RemoveEntityFromSystem(Entity entity);
  std::vector<Entity> GetSystemEntities() const;
  const Signature& GetComponentSignature() const;

  // defines the component type that entities must have to be considered by the system
  template <typename TComponent> void RequireComponent();
};

class Registry {
  // TODO:...
};

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

#endif
