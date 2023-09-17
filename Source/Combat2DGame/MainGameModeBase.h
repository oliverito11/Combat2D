// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

class AMainPlayerController;
UCLASS()
class COMBAT2DGAME_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	AMainPlayerController *PlayerController;
public:
	virtual void OnPostLogin(AController* NewPlayer) override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerJoined(AMainPlayerController *NewPlayerController);
};
