// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerPlayerState.h"

#include "Net/UnrealNetwork.h"

void AMainPlayerPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerPlayerState, PlayerName);
}
