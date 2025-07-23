// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h" // �� ������ �׻� ������� �� �������� ��ġ�ؾ� ��. �ƴ� ������. ���÷��� �ý��� ���� ����.

DECLARE_LOG_CATEGORY_EXTERN(LogSparta, Warning, All);

UCLASS() //���� �ش� Ŭ������ ���÷��� �ý��ۿ� ����ϴ� ��ũ��(Ű����). �̷��� �������Ʈ���� ���� ����.
class SPARTAPROJECT_API AItem : public AActor
{
	GENERATED_BODY() //UCLASS()�� �׻� ������ �ٴ�. ���÷��� ������ �ڵ� ����.
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components");
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components");
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Properties");
	float RotationSpeed;

	UFUNCTION(BlueprintCallable, Category = "Item|Actions")
	void ResetActorPosition();

	UFUNCTION(BlueprintPure, Category="Item|Properties")
	float GetRotationSpeed() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Item|Event")
	void OnItemPickedUP();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};