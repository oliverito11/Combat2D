// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

#include "Net/UnrealNetwork.h"

void UMainGameInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMainGameInstance, PlayerName);
}
