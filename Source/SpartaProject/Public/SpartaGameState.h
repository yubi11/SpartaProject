// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPROJECT_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASpartaGameState();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration; // Level duration in seconds
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Wave")
	int32 CurrentWaveIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level|Wave")
	int32 MaxWaveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level|Wave")
	float WaveDuration;

	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdataTimerHandle;
	FTimerHandle WaveTimerHandle;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnCoinCollected();

	void StartLevel();
	void OnLevelTimeUp();
	void EndLevel();
	void UpdateHUD();

	void StartWave();
	void OnWaveTimeUp();
};