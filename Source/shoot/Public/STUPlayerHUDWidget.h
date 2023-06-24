// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

UCLASS()
class SHOOT_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData &data);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponAmo(FWeaponAmo &Amo);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsAllive();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsSpectator();

	template<typename T>
	T* GetComponent();
};

template <typename T> inline
T *USTUPlayerHUDWidget::GetComponent()
{
	const APawn *Player = GetOwningPlayerPawn();
	if (!Player)
		return nullptr;

	UActorComponent *Component = Player->GetComponentByClass(T::StaticClass());
	return Cast<T>(Component);
}
