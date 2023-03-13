// Fill out your copyright notice in the Description page of Project Settings.

#include "STUWeaponComponent.h"
#include "STUBaseWeapon.h"
#include "GameFramework/Character.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::Fire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->Fire();
}

bool USTUWeaponComponent::GetWeaponUIData(FWeaponUIData &data) const
{
	if (CurrentWeapon)
	{
		data = CurrentWeapon->GetWeaponUIData();
		return true;
	}

	return false;
}

bool USTUWeaponComponent::GetAmo(FWeaponAmo &Amo) const
{
	if (CurrentWeapon)
	{
		Amo = CurrentWeapon->GetAmo();
		return true;
	}

	return false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
		return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (!CurrentWeapon)
		return;

	ACharacter *character = Cast<ACharacter>(GetOwner());
	if (!character)
		return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(character->GetMesh(), AttachmentRules, WeaponAtachPointName);
	UE_LOG(LogTemp, Warning, TEXT("RUN"))
	CurrentWeapon->SetOwner(GetOwner());
}
