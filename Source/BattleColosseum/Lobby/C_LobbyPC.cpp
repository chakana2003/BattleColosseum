// Fill out your copyright notice in the Description page of Project Settings.

#include "C_LobbyPC.h"
#include "UnrealNetwork.h"

void AC_LobbyPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AC_LobbyPC, MyInfo);
}
