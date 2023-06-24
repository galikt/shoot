#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class SHOOT_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:
	ASTUBasePickup();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	USphereComponent *CollisionComponent;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	UStaticMeshComponent *Mesh;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float RespawnTimer = 5.0f;

	virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;
	virtual bool GivePickupTo(APawn *Pawn);

private:
	void WasTaken();
	void Respawn();

};
