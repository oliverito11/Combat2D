// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaperCharacter.h"
#include "PlayerPaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"


APlayerPaperCharacter::APlayerPaperCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	AttackTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Attack trigger"));
	AttackTrigger->SetupAttachment(GetSprite());
}

void APlayerPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	AttackTrigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &APlayerPaperCharacter::OnHitBox);
}

void APlayerPaperCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS(APlayerPaperCharacter, bIsCurrentlyLeft, SharedParams);
}

void APlayerPaperCharacter::OnHitBox(UPrimitiveComponent* ComponentOverlapped, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bSweep, const FHitResult& HitResult)
{
	if(AttackTrigger->bHiddenInGame) return;
	UE_LOG(LogTemp, Warning, TEXT("Hit! %s"), *OtherActor->GetActorNameOrLabel())
}

void APlayerPaperCharacter::OnRep_IsCurrentlyLeft()
{
	
}

void APlayerPaperCharacter::SetSprite(UPaperFlipbook *SpriteToChange, bool bIsLeft, bool bLooping)
{
	OnRep_IsCurrentlyLeft();
	bIsCurrentlyLeft = bIsLeft;
	GetSprite()->SetRelativeScale3D(bIsLeft ? FVector{-1, 1, 1} : FVector::One());
	GetSprite()->SetFlipbook(SpriteToChange);
	GetSprite()->SetLooping(bLooping);
}

void APlayerPaperCharacter::SetEnabledAttackTrigger(bool bEnabled)
{
	AttackTrigger->SetHiddenInGame(!bEnabled);
}
