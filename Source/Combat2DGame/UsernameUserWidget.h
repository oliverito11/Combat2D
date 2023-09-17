// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UsernameUserWidget.generated.h"

class UTextBlock;
UCLASS()
class COMBAT2DGAME_API UUsernameUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget, AllowPrivateAccess), BlueprintReadWrite)
	UTextBlock *TxtUsername;

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FText PlayerName);
	FText GetPlayerName() const {return TxtUsername->GetText(); }
};
