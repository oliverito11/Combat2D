// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperZDCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


AMainPaperZDCharacter::AMainPaperZDCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AMainPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMainPaperZDCharacter::OnHitBox(UPrimitiveComponent* ComponentOverlapped, AActor* OtherActor,
									 UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bSweep, const FHitResult& HitResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit! %s"), *OtherActor->GetActorNameOrLabel())
}

void AMainPaperZDCharacter::JumpPlayer_Implementation()
{
	Super::Jump();
}
