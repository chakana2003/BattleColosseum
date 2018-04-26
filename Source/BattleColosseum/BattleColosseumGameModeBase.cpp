// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleColosseumGameModeBase.h"




ABattleColosseumGameModeBase::ABattleColosseumGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Script/BattleColosseum.C_Warrior"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ABattleColosseumGameModeBase::BeginPlay()
{
}
