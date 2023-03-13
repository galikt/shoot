// Fill out your copyright notice in the Description page of Project Settings.


#include "STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFrameWork/Character.h"
#include "GameFrameWork/Controller.h"
#include "STUBulletDamageType.h"

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void ASTUBaseWeapon::MakeShot()
{
	if (!GetWorld())
		return;

	FVector TraceStart;
	FVector TraceEnd;
	GetTraceData(TraceStart, TraceEnd);

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		if (GetMazzleHitAngle(HitResult) < FMath::Cos(90.0f))
		{
			DrawDebugLine(GetWorld(), GetMazzlreWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0.0f, 1.0f);
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 4, FColor::Yellow, false, 3.0f);

			MakeDamage(HitResult);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMazzlreWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0.0f, 1.0f);
	}
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
		return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector &Position, FRotator &Rotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller)
		return false;

	Controller->GetPlayerViewPoint(Position, Rotation);
	return true;
}

FVector ASTUBaseWeapon::GetMazzlreWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MazzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
		return false;

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistantion;

	return true;
}

float ASTUBaseWeapon::GetMazzleHitAngle(const FHitResult &Hit) const
{
	FVector Trace = GetMazzlreWorldLocation() - Hit.ImpactPoint;
	Trace.Normalize();

	const FTransform MazzleSocket = WeaponMesh->GetSocketTransform(MazzleSocketName);
	return FVector::DotProduct(MazzleSocket.GetRotation().GetForwardVector(), Trace);
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector &TraceStart, const FVector &TraceEnd)
{
	FCollisionQueryParams ColisionParams;
	ColisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, ColisionParams);
}

void ASTUBaseWeapon::Fire()
{
	if (Amo.Bullets > 0)
	{
		MakeShot();
		Amo.Bullets -= 1;
	}
}

void ASTUBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	auto Target = HitResult.GetActor();
	if (Target)
	{
		Target->TakeDamage(Damage, FDamageEvent(USTUBulletDamageType::StaticClass()), GetPlayerController(), this);
	}
}
