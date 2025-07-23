// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"


ASpartaCharacter::ASpartaCharacter()
{

	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")); // Create the spring arm component
	SpringArmComp->SetupAttachment(RootComponent); // Attach the spring arm to the root component
	SpringArmComp->TargetArmLength = 300.0f; // Set the length of the spring arm
	SpringArmComp->bUsePawnControlRotation = true; // Use the pawn's control rotation

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); // Create the camera component
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName); // Set the camera to the end of the spring arm
	CameraComp->bUsePawnControlRotation = false; // Disable camera rotation based on pawn control 카메라까지 컨트롤러가 움직일때마다 회전하면 정신없음.(스프링암만 움직임)

	OverHeadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidget")); // 캐릭터 머리 위 위젯
	OverHeadWidget->SetupAttachment(GetMesh()); // 메시에 부착
	OverHeadWidget->SetWidgetSpace(EWidgetSpace::Screen); // 스크린과 월드 중 스크린으로

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
	JumpHeight = 600.0f; // Set the jump height
	Health = MaxHealth = 100.0f; // Initialize health and max health

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed; // Set the normal walking speed
}


void ASpartaCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdateOverHeadHP(); // Initialize the overhead health widget
	
}


void ASpartaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::Move);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StartJump);
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &ASpartaCharacter::StopJump);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::Look);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StartSprint);
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &ASpartaCharacter::StopSprint);
			}
		}
	}

}

void ASpartaCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;
	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ASpartaCharacter::StartJump(const FInputActionValue& value) 
{
	if (value.Get<bool>())
	{
		if (GetCharacterMovement())
		{
			GetCharacterMovement()->JumpZVelocity = JumpHeight; // 점프 높이 설정
		}
		Jump(); // 점프 시작
	}
}

void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping(); // 점프 중지
	}
}

void ASpartaCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X); // LookInput.X 값에 특정 값 곱해주면 그게 마우스 민감도
	AddControllerPitchInput(LookInput.Y);
}

void ASpartaCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; // 스프린트 속도 증가
	}

}

void ASpartaCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed; // 스프린트 해제시 원래 속도로 복귀
	}
}

float ASpartaCharacter::GetHealth() const
{
	return Health; // 현재 체력 반환
}

void ASpartaCharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth); // 체력 증가, 최소 0, 최대 MaxHealth로 제한
	UE_LOG(LogTemp, Warning, TEXT("Get Health: %.1f"), Health);
	UpdateOverHeadHP();
}

float ASpartaCharacter::TakeDamage(
	float DamageAmount,
	struct FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); // 실제로 나한테 들어온 데미지(방어력 적용해서 감소 등)

	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth); // 체력 감소, 최소 0, 최대 MaxHealth로 제한
	UE_LOG(LogTemp, Warning, TEXT("Get Damage: %.1f"), Health);
	UpdateOverHeadHP();

	if (Health <= 0.0f)
	{
		OnDeath();
	}

	return DamageAmount; // Return the amount of damage taken
}

void ASpartaCharacter::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Character has died!"));
	
	ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (SpartaGameState)
	{
		SpartaGameState->OnGameOver(); // 게임 오버 처리
	}
}

void ASpartaCharacter::UpdateOverHeadHP()
{
	if ( !OverHeadWidget ) return;
	
	UUserWidget* OverHeadWidgetInstance = OverHeadWidget->GetUserWidgetObject();
	if ( !OverHeadWidgetInstance ) return;

	if ( UTextBlock* HPText = Cast<UTextBlock>(OverHeadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHP"))))
	{
		HPText->SetText(FText::FromString(FString::Printf(TEXT("HP : %.0f / %.0f"), Health, MaxHealth)));
	}

}