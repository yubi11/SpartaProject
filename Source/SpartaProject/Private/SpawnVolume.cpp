// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTable = nullptr; // 아이템 스폰 데이터 테이블 초기화
}



FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent(); //박스 스케일의 절반 크기를 반환 중심->끝 거리
	FVector BoxOrigin = SpawningBox->GetComponentLocation(); //박스의 중심 좌표

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z) //랜덤 방향으로 박스의 절반 크기만큼 이동한 위치를 반환
	);
}

AActor* ASpawnVolume::SpawnRandomItem()
{
	FItemSpawnRow* SelectedRow = GetRandomItem(); //랜덤한 아이템을 데이터 테이블에서 선택

	if (SelectedRow)
	{
		if(UClass* ActualClass = SelectedRow->ItemClass.Get()) //선택된 아이템의 클래스를 TSoftClassPtr 타입으로 가져와서 UClass 형태로 반환
		{
			return SpawnItem(ActualClass); //아이템 스폰
		}
	}

	return nullptr; //선택된 아이템이 없으면 nullptr 반환
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable) return nullptr; //아이템 데이터 테이블이 없으면 nullptr 반환

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext")); //데이터 테이블 컨텍스트 문자열
	ItemDataTable->GetAllRows(ContextString, AllRows); //데이터 테이블에서 모든 행을 가져옴

	if (AllRows.IsEmpty()) return nullptr; //행이 없으면 nullptr 반환

	float TotalChance = 0.0f;
	for(const FItemSpawnRow* Row : AllRows) //전체 확률의 합이 100이 아닐 경우를 대비
	{
		if(Row)
		{
			TotalChance += Row->SpawnChance; //각 행의 스폰 확률을 총합
		}
	}

	const float RandomValue = FMath::FRandRange(0.0f, TotalChance); //0부터 총 확률까지의 랜덤 값 생성

	float AccumulateChance = 0.0f; //스폰 누적 확률 변수

	for(FItemSpawnRow* Row : AllRows)
	{
		if(Row)
		{
			AccumulateChance += Row->SpawnChance; //각 행의 스폰 확률을 누적
			if(RandomValue <= AccumulateChance) //랜덤 값이 누적 확률 이하일 경우
			{
				return Row; //해당 행 반환
			}
		}
	}
	return nullptr; //모든 행을 확인했지만 조건에 맞는 행이 없으면 nullptr 반환
}


AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return nullptr;

	AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(
		ItemClass, 
		GetRandomPointInVolume(), 
		FRotator::ZeroRotator
	);
	return SpawnedItem;
}