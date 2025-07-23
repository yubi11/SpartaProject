// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPlayerController.h"
#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

ASpartaPlayerController::ASpartaPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	JumpAction(nullptr),
	SprintAction(nullptr), 
	HUDWidgetClass(nullptr), 
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
	bIsRestart = false; //게임 시작 시 기본값은 false
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0); //IMC 활성화
			}
		}
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if(CurrentMapName.Contains(TEXT("MenuLevel")))
	{
		bIsRestart = false; //메뉴 레벨에서는 게임 재시작이 아니므로 false로 설정
		ShowMainMenu(bIsRestart); //게임 시작 시 메뉴 UI 표시
	}

}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ASpartaPlayerController::ShowGameHUD()
{
	if ( HUDWidgetInstance ) //이미 HUD 위젯이 있다면
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr; //HUD 위젯 인스턴스 제거
	}
	if ( MainMenuWidgetInstance ) //이미 HUD 위젯이 있다면
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr; //HUD 위젯 인스턴스 제거
	}

	if ( HUDWidgetClass )
	{
		if ( !HUDWidgetInstance )
		{
			HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		}
		if ( HUDWidgetInstance )
		{
			HUDWidgetInstance->AddToViewport();
			bShowMouseCursor = false; //게임 시작했으니 마우스 커서 표시
			SetInputMode(FInputModeGameOnly()); //게임 모드로 전환
		}

		ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
		if(SpartaGameState)
		{
			SpartaGameState->UpdateHUD(); //게임 상태 초기화
		}
	}
}

void ASpartaPlayerController::ShowMainMenu(bool IsRestart)
{
	if ( HUDWidgetInstance ) //이미 HUD 위젯이 있다면
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr; //HUD 위젯 인스턴스 제거
	}
	if ( MainMenuWidgetInstance ) //이미 HUD 위젯이 있다면
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr; //HUD 위젯 인스턴스 제거
	}

	if (MainMenuWidgetClass)
	{
		if (!MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		}
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			bShowMouseCursor = true; //마우스 커서 표시
			SetInputMode(FInputModeUIOnly()); //UI 모드로 전환
		}

		if(UTextBlock* ButtonText = Cast<UTextBlock>(
			MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			UTextBlock* QuitText = Cast<UTextBlock>(
				MainMenuWidgetInstance->GetWidgetFromName(TEXT("QuitButtonText")));
			if ( IsRestart )
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
				QuitText->SetText(FText::FromString(TEXT("MainMenu")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
				QuitText->SetText(FText::FromString(TEXT("Quit")));
			}
		}
		if ( IsRestart )
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(TEXT("PlayGameOverAnim"));
			if ( PlayAnimFunc )
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr); //게임 오버 애니메이션 재생
			}

			if(UTextBlock* TotalScoreText = Cast<UTextBlock>(
				MainMenuWidgetInstance->GetWidgetFromName(TEXT("TotalScoreText"))))
			{
				if(USpartaGameInstance* SpartaGameInstance = 
					Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					TotalScoreText->SetText(FText::FromString(
						FString::Printf(TEXT("Total Score: %d"), SpartaGameInstance->TotalScore)));
				}
			}
		}
	}
}

void ASpartaPlayerController::StartGame()
{
	if(USpartaGameInstance* SpartaGameInstance = 
		Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		SpartaGameInstance->CurrentLevelIndex = 0;
		SpartaGameInstance->TotalScore = 0; //게임 시작시 점수 초기화
	}

	SetPause(false); //게임 일시정지 해제
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("BasicLevel"))); //레벨1로 이동
}

void ASpartaPlayerController::QuitToMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("QuitToMainMenu Called"));
	SetPause(false);
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MenuLevel")));
}

void ASpartaPlayerController::QuitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("QuitGame Called"));
	SetPause(false);
	UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, false);
}