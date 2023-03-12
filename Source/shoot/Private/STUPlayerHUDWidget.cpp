// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerHUDWidget.h"
#include "STUHealthComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
		return 0.0f;

	const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USTUHealthComponent>(Component);

	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}
