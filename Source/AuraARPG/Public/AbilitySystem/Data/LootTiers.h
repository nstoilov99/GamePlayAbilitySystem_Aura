// Copyright ShutInGaming

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTiers.generated.h"

USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loottiers|Spawning")
	TSubclassOf<AActor> LootClass;

	UPROPERTY(EditAnywhere, Category = "Loottiers|Spawning")
	float ChanceToSpawn = 0.f;

	UPROPERTY(EditAnywhere, Category = "Loottiers|Spawning")
	float MaxNumberToSpawn = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loottiers|Spawning")
	bool bLootLevelOverride = true;
};
/**
 * 
 */
UCLASS()
class AURAARPG_API ULootTiers : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	TArray<FLootItem> GetLootItems();

	UPROPERTY(EditDefaultsOnly, Category = "Loottiers|Spawning")
	TArray<FLootItem> LootItems;
};
