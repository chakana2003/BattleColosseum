// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_S_PlayerInfo.h"
#include "C_SaveGame.h"
#include "C_LobbyPC.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_LobbyPC : public APlayerController
{
	GENERATED_BODY()
	
public: // 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FC_S_PlayerInfo MyInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UC_SaveGame* SaveGameRef;

public: // 함수
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
};
