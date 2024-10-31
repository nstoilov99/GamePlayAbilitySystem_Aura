// Copyright ShutInGaming

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraFireBlast.generated.h"

class AAuraFireBall;
/**
 * 
 */
UCLASS()
class AURAARPG_API UAuraFireBlast : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

	UFUNCTION(BlueprintCallable)
	TArray<AAuraFireBall*> SpawnFireballs();
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire Blast")
	int32 NumFireBalls = 12;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf <AAuraFireBall> FireBallClass;
};
