// Copyright ShutInGaming


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Kismet/KismetSystemLibrary.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>FIRE BOLT</>\n\n"

			//Level
			"<Small>Level: </><Level>%d</>\n"
			//ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			//Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Launeches a bolt of fire, "
			"exploding on impact and dealing: </>"
			//Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>FIRE BOLT</>\n\n"

			//Level
			"<Small>Level: </><Level>%d</>\n"
			//ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			//Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Number Of FireBolts
			"<Default>Launeches %d bolts of fire, "
			"exploding on impact and dealing: </>"
			//Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumOfProjectiles),
			ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		//Title
		"<Title>NEXT LEVEL</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		//Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Number Of FireBolts
		"<Default>Launeches %d bolts of fire, "
		"exploding on impact and dealing: </>"
		//Damage
		"<Damage>%d</><Default> fire damage with"
		" a chance to burn</>"),

		//Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumOfProjectiles),
		ScaledDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);

	//NumOfProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	if (NumOfProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (NumOfProjectiles - 1);
		for (int32 i = 0; i < NumOfProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			UKismetSystemLibrary::DrawDebugArrow(
				GetAvatarActorFromActorInfo(),
				SocketLocation + FVector(0, 0, 10),
				SocketLocation + FVector(0, 0, 10)+ Direction * 75.f,
				1,
				FLinearColor::Red,
				120.f,
				1.f);
		}
	}
	else 
	{
		//Single Projectile
		UKismetSystemLibrary::DrawDebugArrow(
			GetAvatarActorFromActorInfo(),
			SocketLocation + FVector(0, 0, 10),
			SocketLocation + FVector(0, 0, 10) + Forward * 75.f,
			1,
			FLinearColor::Red,
			120.f,
			1.f);
	}
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + Forward * 100.f, 1, FLinearColor::White, 120.f, 1.f);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + LeftOfSpread * 100.f, 1, FLinearColor::Gray, 120.f, 1.f);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + RightOfSpread * 100.f, 1, FLinearColor::Gray, 120.f, 1.f);
}
