// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperZDCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"


AMainPaperZDCharacter::AMainPaperZDCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	UsernameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Username Widget"));
	UsernameWidget->SetupAttachment(RootComponent);
}

void AMainPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPaperZDCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPaperZDCharacter, bIsInCombo);
}

float AMainPaperZDCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(AMainPaperZDCharacter *OtherChar = Cast<AMainPaperZDCharacter>(DamageCauser))
	{
		KnockBack += Damage;
		float CharDir = GetActorLocation().Length() > OtherChar->GetActorLocation().Length() ? 1 : -1;
		LaunchCharacter(FVector{CharDir,0,1} * KnockBack, true, true);
	}
	
	return Damage;
}

void AMainPaperZDCharacter::RotateCharacter_Implementation(bool bIsLeft)
{
	if(HasAuthority())
	{
		GetSprite()->SetRelativeScale3D(bIsLeft ? FVector{-1,1,1} : FVector::One());
	}
}


void AMainPaperZDCharacter::ResetKnockBack()
{
	KnockBack = 0;
}
