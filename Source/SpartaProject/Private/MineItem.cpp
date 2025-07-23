// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpartaCharacter.h"
#include "Particles/ParticleSystemComponent.h"

AMineItem::AMineItem()
{
	ExplosionDelay = 3.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30.0f;
	bHasExploded = false;
	ExplosionParticleComponent = nullptr;
	ItemType = "Mine";

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);

}

void AMineItem::ActivateItem(AActor* Activator)
{
	if(bHasExploded) // 이미 폭발한 경우
	{
		return; // 아무 동작도 하지 않음
	}
	// 게임 월드 -> 타이머 매니저가
	// 타이머 핸들러를 관리
	Super::ActivateItem(Activator); // 부모 클래스의 ActivateItem 호출

	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle, 
		this, 
		&AMineItem::Explode, 
		ExplosionDelay, 
		false // false means it will not repeat
	);
	bHasExploded = true; // 폭발 상태로 변경
}

void AMineItem::Explode()
{
	UParticleSystemComponent* Particle = nullptr;
	if(ExplosionParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), 
			ExplosionParticle, 
			GetActorLocation(), 
			GetActorRotation(),
			false
		);
	}
	if(ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound, 
			GetActorLocation()
		);
	}

	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Actor);
			UGameplayStatics::ApplyDamage(
				Actor, 
				ExplosionDamage, 
				nullptr, 
				this, 
				UDamageType::StaticClass()
			);
			/*
			GEngine->AddOnScreenDebugMessage(-1,
				2.0f,
				FColor::Green,
				FString::Printf(TEXT("데미지 입음! Health: %.1f"), PlayerCharacter->GetHealth()));*/
		}
	}

	DestroyItem();

	if ( Particle )
	{
		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			this,
			&AMineItem::DestroyExplosionEffect,
			2.0f, 
			false
		);
	}
}

void AMineItem::DestroyExplosionEffect()
{
	if ( ExplosionParticleComponent && !ExplosionParticleComponent->IsBeingDestroyed() )
	{
		ExplosionParticleComponent->DestroyComponent();
		ExplosionParticleComponent = nullptr;
	}
}

void AMineItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 💡 레벨 이동 시 안전하게 타이머 제거
	if ( GetWorld() )
	{
		GetWorld()->GetTimerManager().ClearTimer(ExplosionTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(DestroyParticleTimerHandle);
	}

	Super::EndPlay(EndPlayReason);
}