// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"

#include "MainPaperZDCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxTrigger->SetupAttachment(ProjectileMesh);
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AProjectileActor::OnOverlapBegin);
	SetLifeSpan(5);
}

void AProjectileActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(auto Player = Cast<AMainPaperZDCharacter>(OtherActor) && GetOwner() != OtherActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Hit a player"))
		Destroy();
	}
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorForwardVector() * ShootDirection;
	SetActorLocation(GetActorLocation() + NewLocation * ProjectileSpeed * DeltaTime);
}

