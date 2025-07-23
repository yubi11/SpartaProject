
#include "CoinItem.h"
#include "Engine/World.h"
#include "SpartaGameState.h"
#include "SpartaGameInstance.h"

ACoinItem::ACoinItem()
{
	PointValue = 0;
	ItemType = "DefaultCoin"; // Set a default item type
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator); // 부모 클래스의 ActivateItem 호출

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if(UWorld* World = GetWorld())
		{
			if (ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>() ) 
			{
				GameState->AddScore(PointValue); // Add points to the game state
				GameState->OnCoinCollected(); // Notify the game state that a coin was collected
				if ( UGameInstance* GameInstance = GetGameInstance() )
				{
					USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
					if ( SpartaGameInstance )
					{
						GEngine->AddOnScreenDebugMessage(-1,
							2.0f,
							FColor::Green,
							FString::Printf(TEXT("%s : %d점 획득! 현재 점수: %d"), *ItemType.ToString(), PointValue, SpartaGameInstance->TotalScore));
					}
				}
			}
			
		}
		DestroyItem();
	}
}