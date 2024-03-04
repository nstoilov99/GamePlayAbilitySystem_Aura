// Copyright ShutInGaming

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURAARPG_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UAuraAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
