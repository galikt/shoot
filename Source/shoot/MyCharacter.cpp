// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Arm = CreateDefaultSubobject<USpringArmComponent>("Arm");
    Arm->SetupAttachment(GetRootComponent());
    Arm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(Arm);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
    PlayerInputComponent->BindAxis("TurnAround", this, &AMyCharacter::TurnAround);
}

void AMyCharacter::MoveForward(float value)
{
    AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::MoveRight(float value)
{
    AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::LookUp(float value)
{
    AddControllerPitchInput(value);
}

void AMyCharacter::TurnAround(float value)
{
    AddControllerYawInput(value);
}

