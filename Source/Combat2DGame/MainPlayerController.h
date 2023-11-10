#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class AMainPaperZDCharacter;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

DECLARE_DELEGATE(FTimerDelegate)

UCLASS()
class COMBAT2DGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess), Replicated)
	AMainPaperZDCharacter *PlayerPaperCharacter;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShowMenuAction;

	/** Bow attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	float DashSpeed {400};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess), Replicated)
	bool bCanDash {false};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	FTimerHandle DashTimer;

	FTimerDelegate TimerDelegate;

public:
	AMainPlayerController();
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void StopAttack(const FInputActionValue& Value);
	void ChargeBow(const FInputActionValue& Value);
	void ShootBow(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void LaunchPlayer(AMainPaperZDCharacter *PlayerToLaunch);
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ShowMenu();

	void SetCanDash(bool bDash) { bCanDash = bDash; }
};
