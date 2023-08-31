#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class APlayerPaperCharacter;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UPaperFlipbook;
UCLASS()
class COMBAT2DGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	APlayerPaperCharacter *PlayerPaperCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	/** MappingContext */
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	/** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *RunFB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *IdleFB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *JumpFB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *FallFB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *Attack1FB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *Attack2FB;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *Attack3FB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *AirAttack1FB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	UPaperFlipbook *AirAttack2FB;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess), Replicated)
	bool bIsAttacking {false};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess), Replicated)
	bool bCanAttackAgain {true};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess), Replicated)
	int32 AttackCount {0};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess), Replicated)
	int32 MaxAttackCount {3};

	UPROPERTY(BlueprintReadOnly, Category="Sprites", meta=(AllowPrivateAccess))
	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess), Replicated)
	float ResetAttackTime {.2};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	int32 CanAttackAgainFrame {18};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	int32 EnableHitBoxFrame {12};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sprites", meta=(AllowPrivateAccess))
	int32 DisableHitBoxFrame {18};

protected:
	AMainPlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);
	void SetNewAttack(UPaperFlipbook* Attack1Fb);
	void Attack(const FInputActionValue& Value);

	UFUNCTION()
	void FinishAttack();

	void HandleSprites();
	void HandleAirSprites();
	void HandleGroundSprites();

	UFUNCTION()
	void ResetAttack();
};
