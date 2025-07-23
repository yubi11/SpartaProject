// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CH6_Homework/CH6_HomeworkGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCH6_HomeworkGameMode() {}

// Begin Cross Module References
CH6_HOMEWORK_API UClass* Z_Construct_UClass_ACH6_HomeworkGameMode();
CH6_HOMEWORK_API UClass* Z_Construct_UClass_ACH6_HomeworkGameMode_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_CH6_Homework();
// End Cross Module References

// Begin Class ACH6_HomeworkGameMode
void ACH6_HomeworkGameMode::StaticRegisterNativesACH6_HomeworkGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACH6_HomeworkGameMode);
UClass* Z_Construct_UClass_ACH6_HomeworkGameMode_NoRegister()
{
	return ACH6_HomeworkGameMode::StaticClass();
}
struct Z_Construct_UClass_ACH6_HomeworkGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "CH6_HomeworkGameMode.h" },
		{ "ModuleRelativePath", "CH6_HomeworkGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACH6_HomeworkGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ACH6_HomeworkGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_CH6_Homework,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACH6_HomeworkGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACH6_HomeworkGameMode_Statics::ClassParams = {
	&ACH6_HomeworkGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACH6_HomeworkGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ACH6_HomeworkGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACH6_HomeworkGameMode()
{
	if (!Z_Registration_Info_UClass_ACH6_HomeworkGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACH6_HomeworkGameMode.OuterSingleton, Z_Construct_UClass_ACH6_HomeworkGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACH6_HomeworkGameMode.OuterSingleton;
}
template<> CH6_HOMEWORK_API UClass* StaticClass<ACH6_HomeworkGameMode>()
{
	return ACH6_HomeworkGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACH6_HomeworkGameMode);
ACH6_HomeworkGameMode::~ACH6_HomeworkGameMode() {}
// End Class ACH6_HomeworkGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_CH6_Homework_Source_CH6_Homework_CH6_HomeworkGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACH6_HomeworkGameMode, ACH6_HomeworkGameMode::StaticClass, TEXT("ACH6_HomeworkGameMode"), &Z_Registration_Info_UClass_ACH6_HomeworkGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACH6_HomeworkGameMode), 3908592527U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CH6_Homework_Source_CH6_Homework_CH6_HomeworkGameMode_h_2635011797(TEXT("/Script/CH6_Homework"),
	Z_CompiledInDeferFile_FID_CH6_Homework_Source_CH6_Homework_CH6_HomeworkGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_CH6_Homework_Source_CH6_Homework_CH6_HomeworkGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
