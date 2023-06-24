#include "pickup/STUBasePickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(pawn))
	{
		WasTaken();
	}
}

bool ASTUBasePickup::GivePickupTo(APawn *Pawn)
{
	return false;
}

void ASTUBasePickup::WasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer,this, &ASTUBasePickup::Respawn, RespawnTimer);
}

void ASTUBasePickup::Respawn()
{
	GetRootComponent()->SetVisibility(true, true);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
