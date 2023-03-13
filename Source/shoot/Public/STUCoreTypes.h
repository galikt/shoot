#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "STUCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "UI")
	UTexture2D *MainIcon;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "UI")
	UTexture2D *CrossHairIcon;
};

USTRUCT(BlueprintType)
struct FWeaponAmo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "UI")
	int Bullets = 0;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "UI")
	int Clips = 0;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "UI")
	bool Infinity = false;
};
