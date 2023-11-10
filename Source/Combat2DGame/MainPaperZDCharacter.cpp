// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperZDCharacter.h"

#include "PaperFlipbookComponent.h"
#include "ProjectileActor.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"


AMainPaperZDCharacter::AMainPaperZDCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	NameComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Username"));
	NameComponent->SetRelativeRotation(FRotator{0, -90, 0});
	NameComponent->SetHorizontalAlignment(EHTA_Center);
	NameComponent->SetVerticalAlignment(EVRTA_TextCenter);
	NameComponent->SetWorldSize(15);
	NameComponent->SetupAttachment(RootComponent);
}

void AMainPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnDamageFinishDelegate.BindLambda([this]
	{
		GetSprite()->SetSpriteColor(FLinearColor::White);
	});
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
		LaunchCharacter(FVector{CharDir,0,1} * KnockBack, false, false);
		DamagePlayer();
	}
	
	return Damage;
}

void AMainPaperZDCharacter::DamagePlayer_Implementation()
{
	GetSprite()->SetSpriteColor(DamageColor);

	//Now RGB variables are storing the HSV values
	FLinearColor HSVDamage = DamageColor.LinearRGBToHSV();
	HSVDamage.G = HSVDamage.G < 0.99 ? HSVDamage.G + DamageIncreaseColor : HSVDamage.G;
	HSVDamage.B = HSVDamage.B > 0.01 ? HSVDamage.B - DamageIncreaseColor : HSVDamage.B;
	DamageColor = HSVDamage.HSVToLinearRGB();
	GetWorldTimerManager().SetTimer(DamageTimer, OnDamageFinishDelegate, 0.2f, false);
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
	DamageColor = FLinearColor::White;
}

void AMainPaperZDCharacter::ShootProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("SHOOT"))

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;
	
	const FVector ProjectileSpawnLocation{-ProjectileLocation.X, ProjectileLocation.Y, ProjectileLocation.Z};
	AProjectileActor *ProjectileActor = GetWorld()->SpawnActor<AProjectileActor>(ProjectileClass, GetActorLocation() + (GetSprite()->GetComponentScale().X < 0 ? ProjectileSpawnLocation : ProjectileLocation), FRotator::ZeroRotator, SpawnParameters);
	if(!ProjectileActor) return;
	
	const FVector ProjectileSpawnScale{-ProjectileActor->GetActorScale().X, ProjectileActor->GetActorScale().Y, ProjectileActor->GetActorScale().Z};
	ProjectileActor->SetActorScale3D(GetSprite()->GetComponentScale().X < 0 ? ProjectileSpawnScale : ProjectileActor->GetActorScale());
	ProjectileActor->SetShootDirection(GetSprite()->GetComponentScale().X < 0 ? -1 : 1);
}