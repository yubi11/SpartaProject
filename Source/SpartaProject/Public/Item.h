// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h" // 이 파일은 항상 헤더파일 중 마지막에 배치해야 됨. 아님 오류남. 리플렉션 시스템 내용 포함.

DECLARE_LOG_CATEGORY_EXTERN(LogSparta, Warning, All);

UCLASS() //지금 해당 클래스를 리플렉션 시스템에 등록하는 매크로(키워드). 이래야 블루프린트에서 접근 가능.
class SPARTAPROJECT_API AItem : public AActor
{
	GENERATED_BODY() //UCLASS()와 항상 쌍으로 다님. 리플렉션 데이터 자동 생성.
	
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