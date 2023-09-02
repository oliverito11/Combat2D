// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainPaperZDCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerPaperCharacter = Cast<AMainPaperZDCharacter>(GetCharacter());
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this, &AMainPlayerController::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started,this, &AMainPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMainPlayerController::StopJumping);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainPlayerController::Attack);
	}
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent() || PlayerPaperCharacter->GetIsInCombo()) return;
	PlayerPaperCharacter->GetMovementComponent()->AddInputVector(Value.Get<FVector>());
	ChangeSpriteDirection(Value.Get<FVector>().X < 0);
}

void AMainPlayerController::Jump(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent()) return;
	PlayerPaperCharacter->JumpPlayer();
}

void AMainPlayerController::StopJumping(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent()) return;
	PlayerPaperCharacter->StopJumping();
}
