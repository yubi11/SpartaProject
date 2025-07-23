// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

DEFINE_LOG_CATEGORY(LogSparta);

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // ƽ �Լ��� Ű�� ��. false�� ���°ǵ� Tick �� ���� ���°� ����.

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	if (MeshAsset.Succeeded()) {
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded()) {
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	UE_LOG(LogSparta, Warning, TEXT("%s Constructor"), *GetName());

	RotationSpeed = 90.0f;

}


// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	OnItemPickedUP();

	SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	//Rotator�� pitch, yaw, roll ������
	//           y��   z��   x��
	SetActorScale3D(FVector(2.0f));
	/*
	FVector NewLocation(300.0f, 200.0f, 100.0f);
	FRotator NewRotation(0.0f, 90.0f, 0.0f);
	FVector NewScale(2.0f);
	FTransform NewTransform(NewRotation, NewLocation, NewScale);
	SetActorTransform(NewTransform); //�̷��� �ѹ����� ����
	*/
	//UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	// 120 ������ - 1�� 120�� ȣ��, 1�� / 120 = deltatime
	// 30 ������ - 1�� 30�� ȣ��,  1�� / 30 - deltatime
	// 1�ʿ� 90���� ȸ��
	// 90�� / 120 0.0005
	// 90�� / 30 0.01
	// 1�� = 90�� ��� ��ǻ�Ϳ��� �����ϰ� �Ϸ��� DeltaTime ���������.
	
	Super::Tick(DeltaTime);

	if(!FMath::IsNearlyZero(RotationSpeed)) // ���ǵ尡 0�� �ƴϸ� ����. �ε��Ҽ����� 0.0�� �Ǵ� ��찡 �幰�� 0.000001f �̷� ������ �� �� �־ �����ġ.
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}

void AItem::ResetActorPosition() 
{
	SetActorLocation(FVector::ZeroVector);
}

float AItem::GetRotationSpeed() const 
{
	return RotationSpeed;
}



void AItem::PostInitializeComponents() 
{
	Super::PostInitializeComponents();
	UE_LOG(LogSparta, Warning, TEXT("%s PostInitaialize"), *GetName());
}

void AItem::Destroyed() 
{
	UE_LOG(LogSparta, Warning, TEXT("%s Destroyed"), *GetName());
	Super::Destroyed();
}

void AItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogSparta, Warning, TEXT("%s EndPlay"), *GetName());
	Super::EndPlay(EndPlayReason);
}


//������ ����Ŭ
// ������ - �޸𸮿� ����. �� �ѹ� ȣ��.
// PostInitializeComponents() - ������Ʈ�� �ϼ��� ���� ȣ��, ������Ʈ ���� ������ �ְ�ޱ�, ��ȣ�ۿ� �� �� �̿�.
// BeginPlay() - ��ġ (Spawn) ����
// ������� ź��
// Tick(float DeltaTime) - �� �����Ӹ��� ȣ���. �����϶��� ���ϱ⿡ �������
// ������� Ȱ��
// Destroyed() - ���� �Ǳ� ������ ȣ��ȴ�. (�������� ���ҽ��� �� �� �������ָ� ����), ���� �ı�
// EndPlay() - ���� ����, �ı�(Destroyed()), ���� ��ȯ ��� ȣ��. �̶��� �޸� ���� ����
// ������� ����

// Destroyed�� ȣ���ϸ� EndPlay�� ȣ��� (ex. �������� �Ծ �������� ���־��� �� ��)
// ���ڱ� ������ �����ϴ� ��쿣 EndPlay�� ȣ���.