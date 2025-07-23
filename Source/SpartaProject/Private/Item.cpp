// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

DEFINE_LOG_CATEGORY(LogSparta);

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // 틱 함수를 키는 것. false는 끄는건데 Tick 안 쓰면 끄는게 좋음.

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
	//Rotator은 pitch, yaw, roll 순서임
	//           y축   z축   x축
	SetActorScale3D(FVector(2.0f));
	/*
	FVector NewLocation(300.0f, 200.0f, 100.0f);
	FRotator NewRotation(0.0f, 90.0f, 0.0f);
	FVector NewScale(2.0f);
	FTransform NewTransform(NewRotation, NewLocation, NewScale);
	SetActorTransform(NewTransform); //이렇게 한번에도 가능
	*/
	//UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	// 120 프레임 - 1초 120번 호출, 1초 / 120 = deltatime
	// 30 프레임 - 1초 30번 호출,  1초 / 30 - deltatime
	// 1초에 90도씩 회전
	// 90도 / 120 0.0005
	// 90도 / 30 0.01
	// 1초 = 90도 어느 컴퓨터에든 동일하게 하려면 DeltaTime 곱해줘야함.
	
	Super::Tick(DeltaTime);

	if(!FMath::IsNearlyZero(RotationSpeed)) // 스피드가 0이 아니면 실행. 부동소수점은 0.0이 되는 경우가 드물고 0.000001f 이런 식으로 될 수 있어서 방어장치.
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


//라이프 사이클
// 생성자 - 메모리에 생김. 딱 한번 호출.
// PostInitializeComponents() - 컴포넌트가 완성된 직후 호출, 컴포넌트 끼리 데이터 주고받기, 상호작용 할 때 이용.
// BeginPlay() - 배치 (Spawn) 직후
// 여기까지 탄생
// Tick(float DeltaTime) - 매 프레임마다 호출됨. 성능하락이 심하기에 사용주의
// 여기까지 활동
// Destroyed() - 삭제 되기 직전에 호출된다. (여러가지 리소스를 이 때 정리해주면 좋음), 강제 파기
// EndPlay() - 게임 종료, 파괴(Destroyed()), 레벨 전환 등에서 호출. 이때도 메모리 정리 가능
// 여기까지 죽음

// Destroyed를 호출하면 EndPlay도 호출됨 (ex. 아이템을 먹어서 아이템을 없애야할 때 등)
// 갑자기 게임을 종료하는 경우엔 EndPlay만 호출됨.