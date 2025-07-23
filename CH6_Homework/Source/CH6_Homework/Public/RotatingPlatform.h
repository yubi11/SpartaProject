// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class CH6_HOMEWORK_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ȸ�� ���� �޽� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	UStaticMeshComponent* MeshComponent;

	// �ʴ� ȸ�� ���� (deg/sec)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FRotator RotationSpeed;

};
