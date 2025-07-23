// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"

ASpartaGameMode::ASpartaGameMode()
{
	// Set default pawn class to our character class
	DefaultPawnClass = ASpartaCharacter::StaticClass(); //StaticClass() is a function that returns the UClass of the specified class type.
	// Set the game state class
	GameStateClass = ASpartaGameState::StaticClass();
	// Set the player controller class
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	// Set the HUD class
	//HUDClass = ASpartaHUD::StaticClass();
}