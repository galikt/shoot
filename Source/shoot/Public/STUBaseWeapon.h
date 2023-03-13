// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOT_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	ASTUBaseWeapon();

	virtual void Fire();
	inline const FWeaponUIData &GetWeaponUIData() const;
	inline const FWeaponAmo &GetAmo() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent *WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MazzleSocketName = "MazzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float TraceMaxDistantion = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FWeaponAmo Amo;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector &Position, FRotator &Rotation) const;
	FVector GetMazzlreWorldLocation() const;
	bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;
	float GetMazzleHitAngle(const FHitResult &Hit) const;
	void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);
	void MakeShot();
	void MakeDamage(const FHitResult &HitResult);
};

const FWeaponUIData &ASTUBaseWeapon::GetWeaponUIData() const
{
	return UIData;
}

const FWeaponAmo &ASTUBaseWeapon::GetAmo() const
{
	return Amo;
}
