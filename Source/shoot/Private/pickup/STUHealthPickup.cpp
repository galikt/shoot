// Fill out your copyright notice in the Description page of Project Settings.


#include "pickup/STUHealthPickup.h"

bool ASTUHealthPickup::GivePickupTo(APawn *Pawn)
{
	if (Pawn)
	{
		return true;
	}

	return false;
}
