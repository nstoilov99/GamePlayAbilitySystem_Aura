// Copyright ShutInGaming


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/*
	* Primary Attributes
	*/
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage")
	);

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magical damage")
	);

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("Increases Armor and Armor penetration")
	);

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Increases Health")
	);

	/*
	* Secondary Attributes
	*/

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance")
	);

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignored Percentage of enemy Armor, increases Critical Hit Chance")
	);

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance to cut incoming damage in half")
	);

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Chance to double damage plus critical hit bonus")
	);

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Bonus damage added when a critical hit is scored")
	);

	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Reduces Critical Hit Chance of attacking enemies")
	);

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of Health regeneratied every 1 second")
	);

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of Mana regeneratied every 1 second")
	);

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Max amount of Health obtainable")
	);

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Max amount of Mana obtainable")
	);

	/*
	* Input Tags
	*/

	GameplayTags.InputTag_ActionPrimary = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ActionPrimary"),
		FString("Input Tag for Primary Action (Left Mouse Button)")
	);

	GameplayTags.InputTag_ActionSecondary = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ActionSecondary"),
		FString("Input Tag for Secondary Action (Right Mouse Button)")
	);
	GameplayTags.InputTag_ActionSlot1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ActionSlot1"),
		FString("Input Tag for 1st Action Slot (Key 1)")
	);
	GameplayTags.InputTag_ActionSlot2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ActionSlot2"),
		FString("Input Tag for 2nd Action Slot (Key 2)")
	);
	GameplayTags.InputTag_ActionSlot3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ActionSlot3"),
		FString("Input Tag for 3rd Action Slot (Key 3)")
	);
	GameplayTags.InputTag_ActionSlot4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ActionSlot4"),
		FString("Input Tag for 4th Action Slot (Key 4)")
	);
}