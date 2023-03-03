// Copyright shenkns Log System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "Modules/ModuleManager.h"

#pragma region Log

#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
: (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
: (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
: (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
: TEXT("[Standalone] "))

#if defined _MSC_VER && _MSC_VER
#define FUNC_NAME    *FString(__FUNCTION__)
#else 
#define FUNC_NAME    *FString(__func__)
#endif

#define LOG(LogCategory, Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN);\
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogCategory, Log, TEXT("%s%s : %s() : %s"), NETMODE_WORLD, *GetNameSafe(this), FUNC_NAME, *Msg);\
	CLEAR_WARN_COLOR();\
} \

#define LOG_STATIC(LogCategory, Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN);\
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogCategory, Log, TEXT("static::%s() : %s"), FUNC_NAME, *Msg);\
	CLEAR_WARN_COLOR(); \
} \

#define LOG_WARN(LogCategory, Format, ...) \
{ \
	SET_WARN_COLOR( COLOR_YELLOW );\
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogCategory, Log, TEXT("**WARNING** %s%s : %s() : %s"), NETMODE_WORLD, *GetNameSafe(this), FUNC_NAME, *Msg);\
	CLEAR_WARN_COLOR();\
} \

#define LOG_ERROR(LogCategory, Format, ...) \
{ \
	SET_WARN_COLOR( COLOR_RED );\
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogCategory, Log, TEXT("**ERROR** %s%s : %s() : %s"), NETMODE_WORLD, *GetNameSafe(this), FUNC_NAME, *Msg);\
	CLEAR_WARN_COLOR();\
} \

#define SCREEN_DEBUG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
	FCString::Sprintf(StdMsg, TEXT("%s%s : %s() : %s"), NETMODE_WORLD, *GetNameSafe(this), FUNC_NAME, *Msg); \
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Emerald, StdMsg); \
} \

#define DEBUG_MESSAGE(Screen, LogCategory, Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	if(Screen) \
	{ \
		TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
		FCString::Sprintf(StdMsg, TEXT("%s%s : %s() : %s"), NETMODE_WORLD,*GetNameSafe(this), FUNC_NAME, *Msg); \
		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Emerald, StdMsg); \
	} \
	SET_WARN_COLOR(COLOR_CYAN);\
	UE_LOG(LogCategory, Log, TEXT("%s%s : %s() : %s"), NETMODE_WORLD, *GetNameSafe(this), FUNC_NAME, *Msg);\
	CLEAR_WARN_COLOR(); \
} \

#pragma endregion Log

class FLogSystemModule : public IModuleInterface
{
};
