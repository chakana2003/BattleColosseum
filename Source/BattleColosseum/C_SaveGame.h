// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "C_S_PlayerInfo.h"
#include "C_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API UC_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UC_SaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SaveGameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FC_S_PlayerInfo MyInfo;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
