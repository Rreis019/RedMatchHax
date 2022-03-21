#pragma once
#include <windows.h>
#include <cstdint>
#include "vec3.h"
#include "Utils.h"

class LastObjectBase
{
public:
	char pad_0000[16]; //0x0000
	class GameObject *gameObject; //0x0010
}; //Size: 0x0018


class BaseObject
{
public:
	char pad_0000[8]; //0x0000
	class BaseObject *nextObject; //0x0008
	class GameObject *gameObject; //0x0010
}; //Size: 0x0018


class GameObject
{
public:
	char pad_0000[48]; //0x0000
	class CompList* ComponentList; //0x0030
	char pad_0038[8]; //0x0038
	uint32_t ComponentSize; //0x0040
	char pad_0044[12]; //0x0044
	uint32_t layer; //0x0050
	uint16_t tag; //0x0054
	char pad_0056[10]; //0x0056
	char* name; //0x0060
}; //Size: 0x0068

class GameObjectManager
{
public:
	class LastObjectBase* LastTaggedObject; //0x0000
	class BaseObject* TaggedObjects; //0x0008
	class LastObjectBase* LastActiveObject; //0x0010
	class BaseObject* ActiveObjects; //0x0018
	class LastObjectBase* LastTaggedObject2; //0x0020
	class BaseObject* TaggedObject2; //0x0028
}; //Size: 0x0030


class ComponentBase
{
public:
	char pad_0000[40]; //0x0000
	class Ilcpp2Object* fields; //0x0028
}; //Size: 0x0030

class Ilcpp2Object
{
public:
	class Il2CppClass* klass; //0x0000
}; //Size: 0x0008

class Il2CppClass
{
public:
	char pad_0000[16]; //0x0000
	char* compname; //0x0010
}; //Size: 0x0018


//OFFSETS
extern uint64_t offsetGameObjectManager;


//ADDR
extern MODULEINFO modUnityPlayerDll;
extern MODULEINFO modGameAssemblyDll;
extern GameObjectManager* gameObjectManager;


struct Il2CppString;
typedef Il2CppString* tpIl2cpp_string_new(const char*);
typedef void* tpIl2cpp_resolve_icall(const char*);
typedef void* tpFindGameObjectByTag(Il2CppString*);
typedef void* tpComponentGetGameobject(void* component);
typedef	void* tpGetCurrentCamera();
typedef void* tpTransformSetPos(void* transform, vec3 pos);
typedef vec3 tpTransformGetPos(void* transform);
typedef void* tpGameObjectGetTransform(void* gameObject);
typedef int tpGetWindowWitdh();
typedef int tpGetWindowHeight();
typedef void(__fastcall tp_WorldToScreenPoint)(uint64_t camera, vec3* m_vWorld, int m_iEye, vec3* m_vScreen);
typedef void* tpGetMainCamera();
typedef void tpIl2cpp_thread_attach(uint64_t domain);
typedef void* tpIl2cpp_domain_get();
typedef void* tpSetTargetFrameRate(int fps);

extern tpFindGameObjectByTag* fnFindGameObjectByTag;
extern tpComponentGetGameobject* fnComponentGetGameobject;
extern tpGetWindowWitdh* fnGetWindowWitdh;
extern tpGetWindowHeight* fnGetWindowHeight;
extern tpTransformGetPos* fnGameObjectGetTransform;
extern tpTransformSetPos* fnTransformSetPosition;
extern tp_WorldToScreenPoint* fnWorldToScreenPoint;
extern tpGetMainCamera* fnGetMainCamera;
extern tpIl2cpp_thread_attach* fnIl2cpp_thread_attach;
extern tpIl2cpp_domain_get* fnIl2cpp_domain_get;
extern tpSetTargetFrameRate* fnSetTargetFrameRate;



void initSDK();
void dumpObjects();

bool w2s(uint64_t camFields, vec3 pos, vec3& out);
uint64_t getComponentById(uint64_t ComponentList, int id);
char* getComponentName(uintptr_t complist, int index);
uint64_t getComponentByName(GameObject* gameObject, char* compName);
vec3 getGameObjectPos(GameObject* gameObject);