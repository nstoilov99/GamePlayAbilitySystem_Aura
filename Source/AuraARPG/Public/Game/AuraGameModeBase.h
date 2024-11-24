// Copyright ShutInGaming

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class ULoadScreenSaveGame;
class UCharacterClassInfo;
class UAbilityInfo;
class UMVVM_LoadSlot;
class USaveGame;
/**
 * 
 */
UCLASS()
class AURAARPG_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;

	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

	void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);

	ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;

	ULoadScreenSaveGame* RetrieveInGameSaveData();

	void SaveInGameProgressData(ULoadScreenSaveGame* InSaveObject);
	
	void SaveWorldState(UWorld* World) const;
	void LoadWorldState(UWorld* World) const;

	static void DeleteSlot(const FString& SlotName, int32 SlotIndex);

	void TravelToMap(UMVVM_LoadSlot* Slot);

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

protected:
	virtual void BeginPlay() override;
};
