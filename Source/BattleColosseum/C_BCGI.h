// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_BCGI.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API UC_BCGI : public UGameInstance
{
	GENERATED_BODY()
	
public:		// 변수

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SAVEGAME;

public:		// 함수
	UC_BCGI();
};
