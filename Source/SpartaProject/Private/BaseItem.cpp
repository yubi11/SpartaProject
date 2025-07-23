// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // 디폴트 콜리젼 설정
	Collision->SetupAttachment(Scene);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	//이벤트 바인딩 (오버랩 발생 시 호출되는 이벤트)
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);

}

void ABaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, //자기 자신(스피어 콜리젼)
	AActor* OtherActor, //부딪힌 액터
	UPrimitiveComponent* OhterComp, //부딪힌 액터에 붙어있던 충돌을 일으킨 원인인 컴포넌트. 플레이어 기준으로 캡슐 컴포넌트
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player")) // 자기 자신과 겹치지 않도록
	{
		ActivateItem(OtherActor); // 아이템 활성화 함수 호출
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Item Overlapped: %s"), *GetName()));
	}
}

void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, //자기 자신(스피어 콜리젼)
	AActor* OtherActor, //부딪힌 액터
	UPrimitiveComponent* OhterComp, //부딪힌 액터에 붙어있던 충돌을 일으킨 원인인 컴포넌트. 플레이어 기준으로 캡슐 컴포넌트
	int32 OtherBodyIndex)
{

}

void ABaseItem::ActivateItem(AActor* Activator)
{
	UParticleSystemComponent* Particle = nullptr;

	if(PickupParticle)
	{
		PickupParticleComponent = UGameplayStatics::SpawnEmitterAttached(
			PickupParticle,
			RootComponent,
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			true,
			EPSCPoolMethod::None,
			true); 
		/*
		PickupParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			PickupParticle,
			GetActorLocation(),
			GetActorRotation(),
			true
		);*/
		//Particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupParticle, GetActorLocation(), GetActorRotation(), true);
	}
	if(PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	}
	if (PickupParticleComponent)
	{

		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			this,
			&ABaseItem::DestroyPickupParticle,
			2.0f,
			false
		);
	}

	/*
	if ( Particle )
	{
		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			[Particle]() //람다 함수로 파티클 컴포넌트 제거
			{
				Particle->DestroyComponent();
			},
			2.0f,
			false
		);
	}*/
}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::DestroyItem()
{
	Destroy();
}

void ABaseItem::DestroyPickupParticle()
{
	if ( PickupParticleComponent && !PickupParticleComponent->IsBeingDestroyed() )
	{
		PickupParticleComponent->DestroyComponent();
		PickupParticleComponent = nullptr;
	}
}