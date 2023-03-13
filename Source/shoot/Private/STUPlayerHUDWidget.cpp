// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerHUDWidget.h"
#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"
#include "STUBaseWeapon.h"

float USTUPlayerHUDWidget::GetHealthPercent()
{
	const auto HealthComponent = GetComponent<USTUHealthComponent>();
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData &data)
{
	const auto WeaponComponent = GetComponent<USTUWeaponComponent>();
	if (!WeaponComponent)
		return false;
	
	return WeaponComponent->GetWeaponUIData(data);
}

bool USTUPlayerHUDWidget::GetWeaponAmo(FWeaponAmo &Amo)
{
	const auto WeaponComponent = GetComponent<USTUWeaponComponent>();
	if (!WeaponComponent)
		return false;

	return WeaponComponent->GetAmo(Amo);
}
