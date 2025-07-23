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
	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComp, //�ڱ� �ڽ�(���Ǿ� �ݸ���)
		AActor* OtherActor, //�ε��� ����
		UPrimitiveComponent* OhterComp, //�ε��� ���Ϳ� �پ��ִ� �浹�� ����Ų ������ ������Ʈ. �÷��̾� �������� ĸ�� ������Ʈ
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0; // �����۰� ������ �� ȣ��Ǵ� �Լ�
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor,
		UPrimitiveComponent* OhterComp, 
		int32 OtherBodyIndex) = 0; // �����۰� ��ħ�� ������ �� ȣ��Ǵ� �Լ�
	virtual void ActivateItem(AActor* Activator) = 0; // �������� Ȱ��ȭ�� �� ȣ��Ǵ� �Լ�
	virtual FName GetItemType() const = 0; // �������� Ÿ���� ��ȯ�ϴ� �Լ�


	// ����, ����, ����
	// ����, ���� - ��� �ߵ��� - ������
	// ���� - ���� ���� ������ - �ߵ��� 5�� �� ���� - 5�� �ڿ��� �������̶��? - ������ ����

};
