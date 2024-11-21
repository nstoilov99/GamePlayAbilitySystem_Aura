// Copyright ShutInGaming

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AuraGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AURAARPG_API UAuraGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FName PlayerStartTag = FName();
	
	UPROPERTY()
	FString LoadSlotName = FString();

	UPROPERTY()
	int32 LoadSlotIndex = 0;
};
