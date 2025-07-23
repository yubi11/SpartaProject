// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "SpartaPlayerController.h"
#include "SpartaCharacter.h"
#include "SpartaGameInstance.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

ASpartaGameState::ASpartaGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevel = 3;

	CurrentWaveIndex = 0;
	MaxWaveIndex = 3;       // 💡 웨이브 3개
	WaveDuration = 10.0f;   // 💡 각 웨이브 10초
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdataTimerHandle, 
		this, 
		&ASpartaGameState::UpdateHUD, 
		0.1f, 
		true // true means it will repeat every second
	);
}

int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	if(UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if(SpartaGameInstance)
		{
			SpartaGameInstance->AddToScore(Amount);
		}
	}
}

void ASpartaGameState::StartLevel()
{
	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) //게임 스타트 시 메뉴 UI 종료 후 HUD 표시
	{
		if(ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->ShowGameHUD(); //게임 HUD 표시
		}
	}


	if ( UGameInstance* GameInstance = GetGameInstance() )
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if ( SpartaGameInstance )
		{
			CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
		}
	}

	CurrentWaveIndex = 0; // 웨이브 초기화
	StartWave(); // 첫 번째 웨이브 시작

	/*
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40; // 아이템 40개 스폰

	for(int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			int32 RandomIndex = FMath::RandRange(0, FoundVolumes.Num() - 1);
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[RandomIndex]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if(SpawnedActor &&  SpawnedActor->IsA(ACoinItem::StaticClass()) )

				SpawnedCoinCount++;
			}
		}
	}

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle, 
		this, 
		&ASpartaGameState::OnLevelTimeUp, 
		LevelDuration, 
		false // false means it will not repeat
	);
	UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d coins"), CurrentLevelIndex + 1, SpawnedCoinCount);
	GEngine->AddOnScreenDebugMessage(-1,
		2.0f,
		FColor::Orange,
		FString::Printf(TEXT("레벨 %d Start!, %d 개 코인 생성!"), CurrentLevelIndex + 1, SpawnedCoinCount));
		*/
	
}

void ASpartaGameState::OnLevelTimeUp()
{
	EndLevel();
}

void ASpartaGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	/*UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);
	GEngine->AddOnScreenDebugMessage(-1,
		2.0f,
		FColor::Orange,
		FString::Printf(TEXT("남은 코인: %d / %d"), CollectedCoinCount, SpawnedCoinCount));*/

	if(SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		//EndLevel();
		GetWorldTimerManager().ClearTimer(LevelTimerHandle);
		OnWaveTimeUp();
	}
}

void ASpartaGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if ( UGameInstance* GameInstance = GetGameInstance() )
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if ( SpartaGameInstance )
		{
			AddScore(Score);
			CurrentLevelIndex++;
			SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if ( CurrentLevelIndex >= MaxLevel )
	{
		OnGameOver();
		return;
	}
	
	if(LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		//FName NextLevelName = LevelMapNames[CurrentLevelIndex];
		//UGameplayStatics::OpenLevel(this, NextLevelName);
		GetWorldTimerManager().ClearTimer(LevelTimerHandle);
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void ASpartaGameState::OnGameOver()
{
	if ( APlayerController* PlayerController = GetWorld()->GetFirstPlayerController() ) //게임 스타트 시 메뉴 UI 종료 후 HUD 표시
	{
		if ( ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController) )
		{
			SpartaPlayerController->SetPause(true); //게임 일시정지
			SpartaPlayerController->bIsRestart = true; //게임 재시작 여부 설정
			SpartaPlayerController->ShowMainMenu(SpartaPlayerController->bIsRestart); //게임 HUD 표시
		}
	}

	if ( UGameInstance* GameInstance = GetGameInstance() )
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if ( SpartaGameInstance )
		{
			int32 TotalScore = SpartaGameInstance->TotalScore;
			/*UE_LOG(LogTemp, Warning, TEXT("Game Over! Final Score: %d"), TotalScore);
			GEngine->AddOnScreenDebugMessage(-1,
				2.0f,
				FColor::Orange,
				FString::Printf(TEXT("게임 종료! 총합 점수: %d"), TotalScore));*/
		}
	}
	
}

void ASpartaGameState::UpdateHUD()
{
	if ( APlayerController* PlayerController = GetWorld()->GetFirstPlayerController() )
	{
		if ( ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController) )
		{
			if ( UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget() )
			{
				if ( UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))) )
				{
					float RemainTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainTime)));
				}
				if ( UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))) )
				{
					if(UGameInstance* GameInstance = GetGameInstance())
					{
						USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
						if(SpartaGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
						}
					}
				}
				if ( UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))) )
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d (Wave: %d)"), CurrentLevelIndex + 1, CurrentWaveIndex + 1)));
				}
				if ( UTextBlock* HealthText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("HP"))) )
				{
					if ( APlayerController* PC = GetWorld()->GetFirstPlayerController() )
					{
						if ( ASpartaCharacter* Player = Cast<ASpartaCharacter>(PC->GetPawn()) )
						{
							HealthText->SetText(FText::FromString(FString::Printf(TEXT("HP : %.0f"), Player->GetHealth())));
						}
					}
				}

			}
		}
	}
}

void ASpartaGameState::StartWave()
{
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> ExistingItem;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseItem::StaticClass(), ExistingItem);

	for ( AActor* Item : ExistingItem )
	{
		if (Item)
		{
			Item->Destroy();
		}
	}

	int32 ItemToSpawn = 30 + CurrentWaveIndex * 10; //웨이브 당 아이템 수 증가

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for ( int32 i = 0; i < ItemToSpawn; i++ )
	{
		if ( FoundVolumes.Num() > 0 )
		{
			int32 RandomIndex = FMath::RandRange(0, FoundVolumes.Num() - 1);
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[RandomIndex]);
			if ( SpawnVolume )
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if ( SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()) )
				{
					SpawnedCoinCount++;
				}
			}
		}
	}
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnWaveTimeUp,
		WaveDuration,
		false // false means it will not repeat
	);


	UE_LOG(LogTemp, Warning, TEXT("Wave %d 시작!"), CurrentWaveIndex + 1);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange,
		FString::Printf(TEXT("Wave %d 시작! 총 %d 개 아이템 생성!"), CurrentWaveIndex + 1, SpawnedCoinCount));
}

void ASpartaGameState::OnWaveTimeUp()
{
	CurrentWaveIndex++;

	if ( CurrentWaveIndex >= MaxWaveIndex )
	{
		EndLevel(); // 마지막 웨이브 완료 시 레벨 종료
	}
	else
	{
		StartWave(); // 다음 웨이브 시작
	}
}