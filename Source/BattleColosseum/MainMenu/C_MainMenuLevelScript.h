// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "C_MainMenuLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_MainMenuLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AC_MainMenuLevelScript();

	virtual void BeginPlay() override;
	
	class UC_BCGI* BCGameInstance;
};
