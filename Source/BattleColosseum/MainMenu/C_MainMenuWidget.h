// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API UC_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 변수들

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText Status;										// 상태 TEXT
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText RoomCount;									// Room 갯수 TEXT

public:

	
	
};
