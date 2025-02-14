// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_MainMenuPC.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_MainMenuPC : public APlayerController
{
	GENERATED_BODY()

public:
	class TArray<ACameraActor*> Cameras;

	int CamOrder;

	float loopFloat;

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecond) override;
};
