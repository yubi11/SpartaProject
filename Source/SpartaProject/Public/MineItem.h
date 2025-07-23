// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API AMineItem : public ABaseItem
{
	GENERATED_BODY()


public:
	AMineItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ExplosionCollision; // Collision component for explosion detection

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle; // 지뢰 폭파 시 재생할 파티클 효과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplosionSound; // 지뢰 폭파 시 재생할 사운드

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;
	UPROPERTY()
	UParticleSystemComponent* ExplosionParticleComponent; //파괴될 파티클 저장용
	
	bool bHasExploded; // 지뢰가 폭발했는지 여부

	FTimerHandle ExplosionTimerHandle;
	FTimerHandle DestroyParticleTimerHandle;
	
	virtual void ActivateItem(AActor* Activator) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void DestroyExplosionEffect();

	void Explode();
};

