// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_LobbyGM.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_LobbyGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MoveWorld(FString LevelName);
	
};
