// Fill out your copyright notice in the Description page of Project Settings.

#include "C_PlayPC.h"
#include "Kismet/GameplayStatics.h"
#include "C_SaveGame.h"
#include "UnrealNetwork.h"


void AC_PlayPC::Load() {
	SaveGameRef = Cast<UC_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameRef->SaveGameName, 0));
	if (SaveGameRef) {
		MyInfo = SaveGameRef->MyInfo;
	}
}

void AC_PlayPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_PlayPC, MyInfo);
}
