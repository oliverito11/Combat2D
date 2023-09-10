// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerPlayerState.generated.h"

UCLASS()
class COMBAT2DGAME_API AMainPlayerPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetNewPlayerName(FString NewName);
};
