// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float)

USTRUCT(BlueprintType)
struct FHeal
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoHeal = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AutoHeal"))
	float HealModifier = 1.0f;

	FTimerHandle DelayTimer;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOT_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	inline float GetHealth() const;
	inline void SetHealth(float value);

	UFUNCTION(BlueprintCallable)
	inline bool IsDead() const;

	FOnDeath OnDeath;
	FOnHealthChange OnHealthChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHeal Heal;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MaxHealth{100.0f};

private:
	float Health{0};

	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser);

	void StartHeal();

	void OnTimerModifierHeal();
};

float USTUHealthComponent::GetHealth() const
{
	return Health;
}

void USTUHealthComponent::SetHealth(float value)
{
	Health = value;
	OnHealthChange.Broadcast(Health);
}

bool USTUHealthComponent::IsDead() const
{
	return FMath::IsNearlyZero(Health);
}