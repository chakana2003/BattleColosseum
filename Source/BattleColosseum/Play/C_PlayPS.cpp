// Fill out your copyright notice in the Description page of Project Settings.

#include "C_PlayPS.h"
#include "UnrealNetwork.h"


bool AC_PlayPS::CopyInfo_Validate(FC_S_PlayerInfo TableInfo) {
	return true;
}
void AC_PlayPS::CopyInfo_Implementation(FC_S_PlayerInfo TableInfo)
{
	MyInfo = TableInfo;
}

void AC_PlayPS::GetLifetimeReplicationProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_PlayPS, MyInfo);
}
