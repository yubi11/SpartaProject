// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

UCLASS()
class SPARTAPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;

public:
	ASpartaCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverHeadWidget; //캐릭터 머리 위에 UI 표시용

	UFUNCTION(BlueprintPure, Category = "Health") //Get 함수는 BlueprintPure로 선언하여 블루프린트에서 읽기 전용으로 사용 가능
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Health") //Set 함수는 BlueprintCallable로 선언하여 블루프린트에서 호출 가능
	void AddHealth(float Amount);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(
		float DamageAmount, //데미지 양
		struct FDamageEvent const& DamageEvent, // 데미지 유형(물속성, 불속성 스킬 등)
		AController* EventInstigator, // 데미지를 입힌 객체(상대 캐릭터, 몬스터, 지뢰를 심은 사람 등)
		AActor* DamageCauser) override; // 데미지를 입힌 원인(총알, 폭발물, 지뢰,  스킬 등)


	UFUNCTION() //블프에서 안 쓰더라도 엔진에 함수의 존재를 알리도록 리플렉션 등록
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value); //on off가 있는 것들은 나눠주는게 좋음. 점프 같은 것
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	void OnDeath();
	void UpdateOverHeadHP(); // 머리 위 위젯 업데이트용 함수
};
