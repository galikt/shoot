// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "pickup/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOT_API ASTUAmmoPickup : public ASTUBasePickup
{
	GENERATED_BODY()

protected:
	virtual bool GivePickupTo(APawn *Pawn) override;
};
