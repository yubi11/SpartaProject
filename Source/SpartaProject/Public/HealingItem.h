// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()

	AHealingItem();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
