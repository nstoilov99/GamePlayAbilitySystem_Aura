// Copyright ShutInGaming

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURAARPG_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Player Interface */
	void AddToXP_Implementation(int32 InXP);
	/**end Player Interface */

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/**end Combat Interface */
	
private:
	virtual void InitAbilityActorInfo() override;
};
