// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOT_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUWeaponComponent();

	void Fire();
	bool GetWeaponUIData(FWeaponUIData &data) const;
	bool GetAmo(FWeaponAmo &Amo) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAtachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

protected:
	void SpawnWeapon();

	UPROPERTY()
	ASTUBaseWeapon *CurrentWeapon = nullptr;
};
