// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PlayerPaperCharacter.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;
class UPaperFlipbook;
/**
 * 
 */
UCLASS()
class COMBAT2DGAME_API APlayerPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UCameraComponent *CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	USpringArmComponent *SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), ReplicatedUsing=OnRep_IsCurrentlyLeft)
	bool bIsCurrentlyLeft {false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UBoxComponent *AttackTrigger;
public:
	APlayerPaperCharacter();
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnHitBox(UPrimitiveComponent* ComponentOverlapped, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bSweep, const FHitResult& HitResult);

	UFUNCTION()
	void OnRep_IsCurrentlyLeft();
public:
	void SetSprite(UPaperFlipbook *SpriteToChange, bool bIsLeft, bool bLooping);
	bool GetIsCurrentlyFacingLeft() const { return this->bIsCurrentlyLeft; }

	void SetEnabledAttackTrigger(bool bEnabled);
};
