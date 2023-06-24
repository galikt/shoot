// Fill out your copyright notice in the Description page of Project Settings.


#include "pickup/STUAmmoPickup.h"

bool ASTUAmmoPickup::GivePickupTo(APawn *Pawn)
{
	if (Pawn)
	{
		return true;
	}

	return false;
}
