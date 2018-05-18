// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleColosseumGameModeBase.h"
#include "C_Warrior.h"

ABattleColosseumGameModeBase::ABattleColosseumGameModeBase()
{
	DefaultPawnClass = AC_Warrior::StaticClass();
}

void ABattleColosseumGameModeBase::BeginPlay()
{
}
