// Copyright ShutInGaming


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	const float SinePeriod = 2 * PI / SinePeriodConstant;
	if (RunningTime > SinePeriod)
	{
		RunningTime = 0;
	}
	ItemMovement(DeltaTime);
}

void AAuraEffectActor::ItemMovement(float DeltaTime)
{
	if (bRotates)
	{
		const FRotator DeltaRotation(0.f, DeltaTime * RotationRate, 0.f);
		CalculatedRotation = UKismetMathLibrary::ComposeRotators(CalculatedRotation, DeltaRotation);
	}
	if (bSinusoudalMovement)
	{
		const float Sine = SineAmplitude * FMath::Sin(RunningTime * SinePeriodConstant);

		CalculatedLocation = InitialLocation + FVector(0.f, 0.f, Sine);
	}
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	CalculatedLocation = InitialLocation;
	CalculatedRotation = GetActorRotation();
}

void AAuraEffectActor::StartSinusoidalMovement()
{
	bSinusoudalMovement = true;
	InitialLocation = GetActorLocation();
	CalculatedLocation = InitialLocation;
}

void AAuraEffectActor::StartRotation()
{
	bRotates = true;
	CalculatedRotation = GetActorRotation();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{

	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	for (FGameplayEffectWithPolicies InfiniteGE : InfiniteGameplayEffectPolicies) {
		if (bIsInfinite && InfiniteGE.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
		}
	}

	if (bDestroyOnEffectApplication && !bIsInfinite)
	{
		Destroy();
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;

	for (FGameplayEffectWithPolicy InstantGE : InstantGameplayEffectPolicies) {
		if (InstantGE.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, InstantGE.GameplayEffectClass);
		}
	}
	for (FGameplayEffectWithPolicy DurationGE : DurationGameplayEffectPolicies) {
		if (DurationGE.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, DurationGE.GameplayEffectClass);
		}
	}
	for (FGameplayEffectWithPolicies InfiniteGE : InfiniteGameplayEffectPolicies) {
		if (InfiniteGE.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGE.GameplayEffectClass);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;

	for (FGameplayEffectWithPolicy InstantGE : InstantGameplayEffectPolicies) {
		if (InstantGE.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, InstantGE.GameplayEffectClass);
		}
	}
	for (FGameplayEffectWithPolicy DurationGE : DurationGameplayEffectPolicies) {
		if (DurationGE.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, DurationGE.GameplayEffectClass);
		}
	}
	for (FGameplayEffectWithPolicies InfiniteGE : InfiniteGameplayEffectPolicies) {
		if (InfiniteGE.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGE.GameplayEffectClass);
		}
	}
	for (FGameplayEffectWithPolicies InfiniteGE : InfiniteGameplayEffectPolicies) {
		if (InfiniteGE.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
			if (!IsValid(TargetASC)) return;

			TArray<FActiveGameplayEffectHandle> HandlesToRemove;

			for (TPair<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
			{
				if (TargetASC == HandlePair.Value)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
					HandlesToRemove.Add(HandlePair.Key);
				}
			}
			for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}

}