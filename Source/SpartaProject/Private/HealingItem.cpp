// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "SpartaCharacter.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator); // 부모 클래스의 ActivateItem 호출

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
			GEngine->AddOnScreenDebugMessage(-1,
				2.0f,
				FColor::Green,
				FString::Printf(TEXT("체력 회복!: %.1f"), PlayerCharacter->GetHealth()));

		}
		DestroyItem();
	}
}