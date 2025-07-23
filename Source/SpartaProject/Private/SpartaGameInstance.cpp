// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameInstance.h"

USpartaGameInstance::USpartaGameInstance()
{
	// Initialize default values
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void USpartaGameInstance::AddToScore(int32 Amount)
{
	// Increment the score by 1
	TotalScore += Amount;
	// Optionally, you can log the score or trigger any other game logic here
	UE_LOG(LogTemp, Warning, TEXT("총합 점수 갱신: %d"), TotalScore);
}