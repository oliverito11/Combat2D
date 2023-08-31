// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "PlayerPaperCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Net/UnrealNetwork.h"

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

	PlayerPaperCharacter = Cast<APlayerPaperCharacter>(GetCharacter());
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
	HandleSprites();
}

void AMainPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS(AMainPlayerController, bIsAttacking, SharedParams)
	DOREPLIFETIME_WITH_PARAMS(AMainPlayerController, bCanAttackAgain, SharedParams)
	DOREPLIFETIME_WITH_PARAMS(AMainPlayerController, AttackCount, SharedParams)
	DOREPLIFETIME_WITH_PARAMS(AMainPlayerController, MaxAttackCount, SharedParams)
	DOREPLIFETIME_WITH_PARAMS(AMainPlayerController, ResetAttackTime, SharedParams)
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent() || bIsAttacking) return;
	PlayerPaperCharacter->GetMovementComponent()->AddInputVector(Value.Get<FVector>());
}

void AMainPlayerController::Jump(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent() || bIsAttacking) return;
	PlayerPaperCharacter->Jump();
}

void AMainPlayerController::StopJumping(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent()) return;
	PlayerPaperCharacter->StopJumping();
}

void AMainPlayerController::SetNewAttack(UPaperFlipbook* Attack)
{
	PlayerPaperCharacter->SetSprite(Attack, PlayerPaperCharacter->GetIsCurrentlyFacingLeft(), false);
	if(GetWorldTimerManager().IsTimerActive(AttackTimer))
	{
		GetWorldTimerManager().ClearTimer(AttackTimer);
	}
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainPlayerController::ResetAttack, ResetAttackTime, false);
}

void AMainPlayerController::Attack(const FInputActionValue& Value)
{
	if(!PlayerPaperCharacter || !PlayerPaperCharacter->GetMovementComponent() || !bCanAttackAgain) return;
	if(++AttackCount > MaxAttackCount)
	{
		AttackCount = 1;
	}
	bIsAttacking = true;
	bCanAttackAgain = false;
	
	switch (AttackCount)
	{
	case 1:
			SetNewAttack(PlayerPaperCharacter->GetMovementComponent()->IsFalling() ? AirAttack1FB : Attack1FB);
			break;
		case 2:
			SetNewAttack(PlayerPaperCharacter->GetMovementComponent()->IsFalling() ? AirAttack2FB : Attack2FB);
			break;
		case 3:
			SetNewAttack(Attack3FB);
			break;
		default: ;
	}
	PlayerPaperCharacter->GetSprite()->OnFinishedPlaying.AddUniqueDynamic(this, &AMainPlayerController::FinishAttack);
}

void AMainPlayerController::FinishAttack()
{
	bIsAttacking = false;
	
	PlayerPaperCharacter->SetSprite(IdleFB, PlayerPaperCharacter->GetIsCurrentlyFacingLeft(), true);
	if(!PlayerPaperCharacter->GetSprite()->IsPlaying())
	{
		PlayerPaperCharacter->GetSprite()->Play();
	}
}

void AMainPlayerController::HandleSprites()
{
	if(!PlayerPaperCharacter) return;

	//Attacks
	if(bIsAttacking)
	{
		if(PlayerPaperCharacter->GetSprite()->GetPlaybackPositionInFrames() == EnableHitBoxFrame)
		{
			PlayerPaperCharacter->SetEnabledAttackTrigger(true);
		}
		if (PlayerPaperCharacter->GetSprite()->GetPlaybackPositionInFrames() == DisableHitBoxFrame)
		{
			PlayerPaperCharacter->SetEnabledAttackTrigger(false);
		}
		if(PlayerPaperCharacter->GetSprite()->GetPlaybackPositionInFrames() == CanAttackAgainFrame)
		{
			bCanAttackAgain = true;
		}
		return;
	}
	
	//Air movement
	HandleAirSprites();

	//Ground movement
	HandleGroundSprites();
}

void AMainPlayerController::HandleAirSprites()
{
	if(!PlayerPaperCharacter->GetMovementComponent()->IsFalling()) return;

	//Falling
	if(PlayerPaperCharacter->GetMovementComponent()->Velocity.Z < 0.f)
	{
		PlayerPaperCharacter->SetSprite(FallFB, PlayerPaperCharacter->GetIsCurrentlyFacingLeft(), true);
	}
	//Jumping
	else if(PlayerPaperCharacter->GetMovementComponent()->Velocity.Z > 0.f)
	{
		PlayerPaperCharacter->SetSprite(JumpFB, PlayerPaperCharacter->GetIsCurrentlyFacingLeft(), false);
	}
}

void AMainPlayerController::HandleGroundSprites()
{
	if(PlayerPaperCharacter->GetMovementComponent()->IsFalling()) return;
	//Moving
	if(FMath::Abs(PlayerPaperCharacter->GetMovementComponent()->Velocity.X) > 110.f)
	{
		PlayerPaperCharacter->SetSprite(RunFB, PlayerPaperCharacter->GetMovementComponent()->Velocity.X < 0, true);
	}
	//Idle
	else
	{
		PlayerPaperCharacter->SetSprite(IdleFB, PlayerPaperCharacter->GetIsCurrentlyFacingLeft(), true);
	}
}

void AMainPlayerController::ResetAttack()
{
	AttackCount = 1;
	bCanAttackAgain = true;
}
