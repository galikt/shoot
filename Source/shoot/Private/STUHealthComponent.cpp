// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthComponent.h"
#include "GameFrameWork/Actor.h"

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor *owner = GetOwner();
	if (owner)
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
	}
 }

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatedBy, AActor *DamageCauser)
{
	if (Damage <= 0.0f || IsDead())
		return;

	SetHealth(FMath::Clamp(Health - Damage, 0.0f, MaxHealth));

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (Heal.AutoHeal)
	{
		StartHeal();
	}
}

void USTUHealthComponent::StartHeal()
{
	AActor *owner = GetOwner();
	if (owner)
	{
		owner->GetWorldTimerManager().SetTimer(Heal.DelayTimer, this, &USTUHealthComponent::OnTimerModifierHeal, Heal.HealUpdateTime, true, Heal.HealDelay);
	};
}

void USTUHealthComponent::OnTimerModifierHeal()
{
	AActor *owner = GetOwner();
	if (owner)
	{
		if (IsDead() || (Health == MaxHealth))
		{
			owner->GetWorldTimerManager().ClearTimer(Heal.DelayTimer);
		}
		else
		{
			SetHealth(FMath::Min(Health += Heal.HealModifier, MaxHealth));
		}
	}
}
