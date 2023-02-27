#pragma once

template <typename T>
T* GetInterface(const char* dllname, const char* name)
{
	auto handle = GetModuleHandle(dllname);

	if (!handle)
		return nullptr;

	auto functionAddress = GetProcAddress(handle, "CreateInterface");
	
	if (!functionAddress)
		return nullptr;

	using Fn = T * (*)(const char*, int*);

	auto CreateInterface = reinterpret_cast<Fn>(functionAddress);

	return CreateInterface(name, nullptr);
}

class CEntity
{
public:
	const int& GetHealth()
	{
		return *reinterpret_cast<int*>(this + 0x100);
	}
};

class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual void* GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(int hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(int hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual CEntity* GetClientEntity(int entnum) = 0;
	virtual void* GetClientEntityFromHandle(int hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};
