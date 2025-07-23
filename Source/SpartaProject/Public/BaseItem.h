// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class SPARTAPROJECT_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType; // 아이템의 타입을 저장하는 변수

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Componenet")
	USceneComponent* Scene; // 씬 루트 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Componenet")
	USphereComponent* Collision; // 충돌 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Componenet")
	UStaticMeshComponent* StaticMesh; // 정적 메시 컴포넌트

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* PickupParticle; // 아이템 획득 시 재생할 파티클 효과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* PickupSound; // 아이템 획득 시 재생할 사운드

	FTimerHandle DestroyParticleTimerHandle;

	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComp, //자기 자신(스피어 콜리젼)
		AActor* OtherActor, //부딪힌 액터
		UPrimitiveComponent* OhterComp, //부딪힌 액터에 붙어있던 충돌을 일으킨 원인인 컴포넌트. 플레이어 기준으로 캡슐 컴포넌트
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OhterComp,
		int32 OtherBodyIndex) override;

	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;

	virtual void DestroyItem();


	UParticleSystemComponent* PickupParticleComponent = nullptr;

	UFUNCTION()
	void DestroyPickupParticle();



};
