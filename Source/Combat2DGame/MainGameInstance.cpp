// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::AddPlayer(FText Player)
{
	Players.Add(false, Player);
}

FText UMainGameInstance::GetPlayerName() const
{
	for (auto Player : Players)
	{
		if (Player.Key) continue;
		Player.Key = true;
		return Player.Value;
	}

	return FText::FromString("NotFound");
}
