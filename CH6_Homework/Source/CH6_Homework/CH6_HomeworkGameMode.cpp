// Copyright Epic Games, Inc. All Rights Reserved.

#include "CH6_HomeworkGameMode.h"
#include "CH6_HomeworkCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACH6_HomeworkGameMode::ACH6_HomeworkGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
