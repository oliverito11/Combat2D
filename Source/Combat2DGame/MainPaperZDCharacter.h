// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "MainPaperZDCharacter.generated.h"

class UTextRenderComponent;
class AProjectileActor;
class UUsernameUserWidget;
class UWidgetComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class COMBAT2DGAME_API AMainPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent *SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* AttackTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess), Replicated)
	bool bIsInCombo {false};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess), Replicated)
	float KnockBack {0};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UTextRenderComponent *NameComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget))
	FVector ProjectileLocation;
	
public:
	AMainPaperZDCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;
public:
	UFUNCTION(BlueprintImplementableEvent)
	void JumpPlayer();

	UFUNCTION(BlueprintImplementableEvent)
	void StopPlayerJumping();

	UFUNCTION(BlueprintImplementableEvent)
	void Attack();
	
	UFUNCTION(BlueprintImplementableEvent)
    void StopAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void ChargeBow();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShootBow();
	
	UFUNCTION(Server, Reliable)
	void RotateCharacter(bool bIsLeft);
	
	bool GetIsInCombo() const { return bIsInCombo; }

	UFUNCTION(BlueprintCallable)
	void ResetKnockBack();
	
	UFUNCTION(BlueprintCallable)
	void ShootProjectile();
};
