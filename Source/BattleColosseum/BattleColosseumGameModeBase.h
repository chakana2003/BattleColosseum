// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ConstructorHelpers.h"
#include "BattleColosseumGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API ABattleColosseumGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleColosseumGameModeBase();

	virtual void BeginPlay() override;
	
	
};
