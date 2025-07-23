// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CH6_Homework/Public/RotatingPlatform.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRotatingPlatform() {}

// Begin Cross Module References
CH6_HOMEWORK_API UClass* Z_Construct_UClass_ARotatingPlatform();
CH6_HOMEWORK_API UClass* Z_Construct_UClass_ARotatingPlatform_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_CH6_Homework();
// End Cross Module References

// Begin Class ARotatingPlatform
void ARotatingPlatform::StaticRegisterNativesARotatingPlatform()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARotatingPlatform);
UClass* Z_Construct_UClass_ARotatingPlatform_NoRegister()
{
	return ARotatingPlatform::StaticClass();
}
struct Z_Construct_UClass_ARotatingPlatform_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "RotatingPlatform.h" },
		{ "ModuleRelativePath", "Public/RotatingPlatform.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshComponent_MetaData[] = {
		{ "Category", "Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xde\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/RotatingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xde\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotationSpeed_MetaData[] = {
		{ "Category", "Platform Settings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xca\xb4\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (deg/sec)\n" },
#endif
		{ "ModuleRelativePath", "Public/RotatingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xca\xb4\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (deg/sec)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeshComponent;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RotationSpeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARotatingPlatform>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARotatingPlatform_Statics::NewProp_MeshComponent = { "MeshComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARotatingPlatform, MeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshComponent_MetaData), NewProp_MeshComponent_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARotatingPlatform_Statics::NewProp_RotationSpeed = { "RotationSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARotatingPlatform, RotationSpeed), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotationSpeed_MetaData), NewProp_RotationSpeed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARotatingPlatform_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARotatingPlatform_Statics::NewProp_MeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARotatingPlatform_Statics::NewProp_RotationSpeed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARotatingPlatform_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ARotatingPlatform_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_CH6_Homework,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARotatingPlatform_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ARotatingPlatform_Statics::ClassParams = {
	&ARotatingPlatform::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ARotatingPlatform_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ARotatingPlatform_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARotatingPlatform_Statics::Class_MetaDataParams), Z_Construct_UClass_ARotatingPlatform_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ARotatingPlatform()
{
	if (!Z_Registration_Info_UClass_ARotatingPlatform.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARotatingPlatform.OuterSingleton, Z_Construct_UClass_ARotatingPlatform_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ARotatingPlatform.OuterSingleton;
}
template<> CH6_HOMEWORK_API UClass* StaticClass<ARotatingPlatform>()
{
	return ARotatingPlatform::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ARotatingPlatform);
ARotatingPlatform::~ARotatingPlatform() {}
// End Class ARotatingPlatform

// Begin Registration
struct Z_CompiledInDeferFile_FID_CH6_Homework_Source_CH6_Homework_Public_RotatingPlatform_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ARotatingPlatform, ARotatingPlatform::StaticClass, TEXT("ARotatingPlatform"), &Z_Registration_Info_UClass_ARotatingPlatform, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARotatingPlatform), 913373310U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CH6_Homework_Source_CH6_Homework_Public_RotatingPlatform_h_3375379312(TEXT("/Script/CH6_Homework"),
	Z_CompiledInDeferFile_FID_CH6_Homework_Source_CH6_Homework_Public_RotatingPlatform_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_CH6_Homework_Source_CH6_Homework_Public_RotatingPlatform_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
