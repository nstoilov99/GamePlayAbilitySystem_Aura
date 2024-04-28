// Copyright ShutInGaming

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AttributePointReward = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SpellPointReward = 1;
};
/**
 * 
 */
UCLASS()
class AURAARPG_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelUpInfo> LevelUpInformation;

	int32 FindLevelForXP(int32 XP);
};
