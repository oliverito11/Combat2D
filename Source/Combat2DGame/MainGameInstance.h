// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

class AMainPlayerPlayerState;
UCLASS()
class COMBAT2DGAME_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	TMap<bool, FText> Players;

public:
	UFUNCTION(BlueprintCallable)
	void AddPlayer(FText Player);

	UFUNCTION(BlueprintCallable)
	FText GetPlayerName() const;
};
