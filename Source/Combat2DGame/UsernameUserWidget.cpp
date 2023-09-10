// Fill out your copyright notice in the Description page of Project Settings.


#include "UsernameUserWidget.h"

#include "Components/TextBlock.h"

void UUsernameUserWidget::SetPlayerName(FText PlayerName)
{
	TxtUsername->SetText(PlayerName);
}
