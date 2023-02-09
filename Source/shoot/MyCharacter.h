// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class ASTUBaseWeapon;

UCLASS()
class SHOOT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USTUHealthComponent *HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTextRenderComponent *HealthTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent *Arm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Accel = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage *DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamageVelocity{900.0f, 1200.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamage{10.0f, 100.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool ShiftKey = false;

	void MoveForward(float value);
	void MoveRight(float value);
	void OnShiftKey();
	void OffShiftKey();
	void OnDeath();
	void OnHealthChange(float value);
	void SpawnWeapon();

	UFUNCTION()
	void OnGroundedLanded(const FHitResult& Hit);
};
