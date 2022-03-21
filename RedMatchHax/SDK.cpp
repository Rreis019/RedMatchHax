#include "GameSDK.h"
#include "SDK.h"
#include <libloaderapi.h>
#include <stdio.h>
#include "Logger.h"


//OFFSETS
uint64_t offsetGameObjectManager = 0x17CF988;

//MODULES
MODULEINFO modUnityPlayerDll;
MODULEINFO modGameAssemblyDll;

//ADDR
GameObjectManager* gameObjectManager = 0x0;

//FUNCTIONS
struct Il2CppString;
typedef Il2CppString* tpIl2cpp_string_new(const char*);
typedef void* tpIl2cpp_resolve_icall(const char*);


tpIl2cpp_thread_attach* fnIl2cpp_thread_attach;
tpIl2cpp_domain_get* fnIl2cpp_domain_get;

tpIl2cpp_string_new* fnIl2cpp_string_new;
tpIl2cpp_resolve_icall* fnIl2cpp_resolve_icall;
tpFindGameObjectByTag* fnFindGameObjectByTag;
tpComponentGetGameobject* fnComponentGetGameobject;
tpGetWindowWitdh* fnGetWindowWitdh;
tpGetWindowHeight* fnGetWindowHeight;
tpTransformGetPos* fnGameObjectGetTransform;
tpTransformSetPos* fnTransformSetPosition;
tp_WorldToScreenPoint* fnWorldToScreenPoint;
tpGetMainCamera* fnGetMainCamera;
tpSetTargetFrameRate* fnSetTargetFrameRate;
//Name of DLL
#define UNITYPLAYER_DLL "UnityPlayer.dll"
#define GAMEASSEMBLY_DLL "GameAssembly.dll"

//export from gameAssembly.dll
#define EXPORT_IL2CPP_STRING_NEW  "il2cpp_string_new"
#define EXPORT_IL2CPP_RESOLVE_ICALL "il2cpp_resolve_icall"

#define EXPORT_FIND_GAMEOBJECT_BY_TAG "UnityEngine.GameObject::FindGameObjectsWithTag(System.String)"
#define EXPORT_COMPONENT_GET_GAMEOBJECT "UnityEngine.Component::get_gameObject()"
#define EXPORT_GET_MAIN_CAMERA "UnityEngine.Camera::get_main()"
#define EXPORT_GET_WIDTH "UnityEngine.Screen::get_width()"
#define EXPORT_GET_HEIGHT "UnityEngine.Screen::get_height()"
#define EXPORT_GAMEOBJECT_GET_TRANSFORM "UnityEngine.GameObject::get_transform()"
#define EXPORT_GAMEOBJECT_SET_TRANSFORM_POSITION "UnityEngine.Transform::set_position_Injected(UnityEngine.Vector3&)"
#define EXPORT_WORLDTOSCREEN "UnityEngine.Camera::WorldToScreenPoint_Injected"
#define EXPORT_LIMITFRAMERATE "UnityEngine.Application::set_targetFrameRate(System.Int32)"

void getFunctions()
{
	fnWorldToScreenPoint = (tp_WorldToScreenPoint*)fnIl2cpp_resolve_icall(EXPORT_WORLDTOSCREEN);
	fnGameObjectGetTransform = (tpTransformGetPos*)fnIl2cpp_resolve_icall(EXPORT_GAMEOBJECT_GET_TRANSFORM);
	fnTransformSetPosition = (tpTransformSetPos*)fnIl2cpp_resolve_icall(EXPORT_GAMEOBJECT_SET_TRANSFORM_POSITION);
	fnGetWindowWitdh = (tpGetWindowWitdh*)fnIl2cpp_resolve_icall(EXPORT_GET_WIDTH);
	fnGetWindowHeight = (tpGetWindowHeight*)fnIl2cpp_resolve_icall(EXPORT_GET_HEIGHT);
	fnComponentGetGameobject = (tpComponentGetGameobject*)fnIl2cpp_resolve_icall(EXPORT_COMPONENT_GET_GAMEOBJECT);
	fnFindGameObjectByTag = (tpFindGameObjectByTag*)fnIl2cpp_resolve_icall(EXPORT_FIND_GAMEOBJECT_BY_TAG);
	fnGetMainCamera = (tpGetMainCamera*)fnIl2cpp_resolve_icall(EXPORT_GET_MAIN_CAMERA);
	fnSetTargetFrameRate = (tpSetTargetFrameRate*)fnIl2cpp_resolve_icall(EXPORT_LIMITFRAMERATE);
	fnIl2cpp_thread_attach = (tpIl2cpp_thread_attach*)GetProcAddress((HMODULE)modGameAssemblyDll.lpBaseOfDll, "il2cpp_thread_attach");
	fnIl2cpp_domain_get = (tpIl2cpp_domain_get*)GetProcAddress((HMODULE)modGameAssemblyDll.lpBaseOfDll, "il2cpp_domain_get");

	PRINT_POINTER(fnWorldToScreenPoint);
	PRINT_POINTER(fnGameObjectGetTransform);
	PRINT_POINTER(fnTransformSetPosition);
	PRINT_POINTER(fnGetWindowWitdh);
	PRINT_POINTER(fnGetWindowHeight);
	PRINT_POINTER(fnComponentGetGameobject);
	PRINT_POINTER(fnFindGameObjectByTag);
	PRINT_POINTER(fnIl2cpp_thread_attach);
	PRINT_POINTER(fnIl2cpp_domain_get);
	PRINT_POINTER(fnSetTargetFrameRate);
}

#define PATTERN_GAMEOBJECTMANAGER (char*)"\x48\x8B\x15\x00\x00\x00\x00\x48\x83\xC2\x20\x48\x3B"
#define MASK_GAMEOBJECTMANAGER (char*)"xxx????xxxxxx"

void initSDK()
{
	modUnityPlayerDll = getModuleInfo((char*)UNITYPLAYER_DLL);
	modGameAssemblyDll = getModuleInfo((char*)GAMEASSEMBLY_DLL);
	gameObjectManager =  (GameObjectManager*)(*(uint64_t*)absoluteAddress(findPattern(PATTERN_GAMEOBJECTMANAGER, MASK_GAMEOBJECTMANAGER, modUnityPlayerDll), 3));
	PRINT_POINTER(gameObjectManager);
	fnIl2cpp_string_new = (tpIl2cpp_string_new*)GetProcAddress((HMODULE)modGameAssemblyDll.lpBaseOfDll, EXPORT_IL2CPP_STRING_NEW);
	fnIl2cpp_resolve_icall = (tpIl2cpp_resolve_icall*)GetProcAddress((HMODULE)modGameAssemblyDll.lpBaseOfDll, EXPORT_IL2CPP_RESOLVE_ICALL);
	getFunctions();
	initGameSDK();
	uint64_t domain = (uint64_t)fnIl2cpp_domain_get();
	fnIl2cpp_thread_attach(domain);
}

uint64_t getComponentById(uint64_t ComponentList, int id)
{
	return *(uint64_t*)(ComponentList + (0x8 + (id * 0x10)));
}

vec3 getGameObjectPos(GameObject* gameObject)
{
	uint64_t compList = (uint64_t)gameObject->ComponentList;
	uint64_t tranform = getComponentById(compList, 0);
	uint64_t tranform_internal = *(uint64_t*)(tranform + 0x38);
	return *(vec3*)(tranform_internal + 0x90);
}

char* getComponentName(uintptr_t complist, int index)
{
	if (index == 0)
		return (char*)"Transform";

	__try
	{
		ComponentBase* comp = (ComponentBase*)getComponentById(complist, index);
		return comp->fields->klass->compname;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return (char*)""; }
}


uint64_t getComponentByName(GameObject* gameObject,char* compName) 
{
	uint64_t compList = (uint64_t)gameObject->ComponentList;

	for(int i = 1 ; i < gameObject->ComponentSize;i++)
	{
		char* tempName = getComponentName(compList, i);

		if (strcmp(tempName, compName) == 0) {
			return getComponentById(compList,i);
		}

	}

	return NULL;
}

//PlayerAvatar(Clone) -> <000001C1B036D210>  Tag:0 Layer:9  CompSize:51
void dumpObjects()
{
	FILE* txtDump = fopen("C:\\Dump\\Dump.txt", "w");

	if (!txtDump)
	{
		printf("Failed to create Dump.txt");
		return;
	}

	if (gameObjectManager == NULL) { return; }

	GameObject* lastTaggedGameObject = gameObjectManager->LastTaggedObject->gameObject;
	BaseObject* nextNode = gameObjectManager->TaggedObjects;


	while (true)
	{
		GameObject* gameObject = nextNode->gameObject;

		if (!gameObject || gameObject == NULL) {
			break;
		}

		//printf("GameObj: %p\n", GameObject);
		fprintf(txtDump, "%s -> <%p>  Tag:%d Layer:%d  CompSize:%d\n", gameObject->name, gameObject, gameObject->tag, gameObject->layer, gameObject->ComponentSize);
		fprintf(txtDump, "[Components]\n");
		for (int i = 0; i < gameObject->ComponentSize; i++){
			char* compname = getComponentName((uint64_t)gameObject->ComponentList, i);
			fprintf(txtDump, "%s\n", compname);
		}
		fprintf(txtDump, "\n\n");
		nextNode = nextNode->nextObject;


		if (gameObject == lastTaggedGameObject) {
			break;
		}

	}

	printf("Dumped!");
	fclose(txtDump);
}

bool w2s(uint64_t camFields,vec3 pos,vec3& out)
{
	vec3 result = vec3();
	fnWorldToScreenPoint(camFields, &pos, 2, &result);
	out.X = result.X;
	out.Y = result.Y;
	out.Z = result.Z;
	out.Y = fnGetWindowHeight() - out.Y;
	if (out.Z < 1.0f) { return false;}
	return true;
}