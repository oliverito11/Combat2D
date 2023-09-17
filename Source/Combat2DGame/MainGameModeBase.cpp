// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"

#include "MainPlayerController.h"

void AMainGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	AMainPlayerController *PC = Cast<AMainPlayerController>(NewPlayer);
	if(!PC) return;
	UE_LOG(LogTemp, Warning, TEXT("New player just joined!"))
	PlayerJoined(PC);
}
