// Fill out your copyright notice in the Description page of Project Settings.

#include "C_MainMenuLevelScript.h"
#include "Kismet/GameplayStatics.h"
#include "C_BCGI.h"

AC_MainMenuLevelScript::AC_MainMenuLevelScript() {
	BCGameInstance = Cast<UC_BCGI>(UGameplayStatics::GetGameInstance(this));
}

void AC_MainMenuLevelScript::BeginPlay() {
	BCGameInstance->SaveGameCheck();
}

