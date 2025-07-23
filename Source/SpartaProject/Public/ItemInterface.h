// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPARTAPROJECT_API IItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComp, //자기 자신(스피어 콜리젼)
		AActor* OtherActor, //부딪힌 액터
		UPrimitiveComponent* OhterComp, //부딪힌 액터에 붙어있던 충돌을 일으킨 원인인 컴포넌트. 플레이어 기준으로 캡슐 컴포넌트
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0; // 아이템과 겹쳤을 때 호출되는 함수
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor,
		UPrimitiveComponent* OhterComp, 
		int32 OtherBodyIndex) = 0; // 아이템과 겹침이 끝났을 때 호출되는 함수
	virtual void ActivateItem(AActor* Activator) = 0; // 아이템을 활성화할 때 호출되는 함수
	virtual FName GetItemType() const = 0; // 아이템의 타입을 반환하는 함수


	// 지뢰, 힐링, 코인
	// 힐링, 코인 - 즉시 발동형 - 오버랩
	// 지뢰 - 범위 내에 오버랩 - 발동이 5초 뒤 폭발 - 5초 뒤에서 오버랩이라면? - 데미지 입음

};
