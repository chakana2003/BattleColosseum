// Fill out your copyright notice in the Description page of Project Settings.

#include "C_S_PlayerInfo.h"

FC_S_Characters::FC_S_Characters()
{
	Character = nullptr;
	Sumnail = nullptr;
}


FC_S_PlayerInfo::FC_S_PlayerInfo()
{
	Name = FText::FromString(TEXT("None"));
	Icon = nullptr;
	status = FText::FromString(TEXT("None"));
}
