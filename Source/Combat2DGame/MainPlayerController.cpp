// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainPaperZDCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Net/UnrealNetwork.h"


AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void AMainPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AMainPlayerController, PlayerPaperCharacter);
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

		EnhancedInputComponent->BindAction(ShowMenuAction, ETriggerEvent::Started, this, &AMainPlayerController::ShowMenu);
		
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainPlayerController::Attack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AMainPlayerController::StopAttack);

		EnhancedInputComponent->BindAction(BowAction, ETriggerEvent::Started, this, &AMainPlayerController::ChargeBow);
		EnhancedInputComponent->BindAction(BowAction, ETriggerEvent::Completed, this, &AMainPlayerController::ShootBow);
	}
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent() || PlayerPaperCharacter->GetIsInCombo() || bShowMouseCursor) return;
	PlayerPaperCharacter->GetMovementComponent()->AddInputVector(Value.Get<FVector>());
	PlayerPaperCharacter->RotateCharacter(Value.Get<FVector>().X < 0);
}

void AMainPlayerController::Jump(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent()) return;
	PlayerPaperCharacter->JumpPlayer();
}

void AMainPlayerController::StopJumping(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent()) return;
	PlayerPaperCharacter->StopPlayerJumping();
}

void AMainPlayerController::Attack(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter) return;
	PlayerPaperCharacter->Attack();
}

void AMainPlayerController::StopAttack(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter) return;
	PlayerPaperCharacter->StopAttack();
}

void AMainPlayerController::ChargeBow(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter) return;
	PlayerPaperCharacter->ChargeBow();
}

void AMainPlayerController::ShootBow(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter) return;
	PlayerPaperCharacter->ShootBow();
}
