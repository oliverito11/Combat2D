// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

class UBoxComponent;
class UPaperFlipbookComponent;

UCLASS()
class COMBAT2DGAME_API AProjectileActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent *BoxTrigger;

	UPROPERTY(EditDefaultsOnly)
	UPaperFlipbookComponent *ProjectileMesh;

	UPROPERTY(EditAnywhere)
	float ProjectileDamage {20};

	UPROPERTY(EditAnywhere)
	float ShootDirection {1};

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed {5};

public:	
	// Sets default values for this actor's properties
	AProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetShootDirection(float ShootDir) { ShootDirection = ShootDir; }
};
