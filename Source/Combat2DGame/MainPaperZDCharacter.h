// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "MainPaperZDCharacter.generated.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool bIsInCombo {false};
	
public:
	AMainPaperZDCharacter();
	virtual void BeginPlay() override;
	void OnHitBox(UPrimitiveComponent* ComponentOverlapped, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	              int OtherBodyIndex, bool bSweep, const FHitResult& HitResult);

	UFUNCTION(BlueprintNativeEvent)
	void JumpPlayer();

	bool GetIsInCombo() const { return bIsInCombo; }
};
