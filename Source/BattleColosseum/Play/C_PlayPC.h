// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_S_PlayerInfo.h"
#include "C_SaveGame.h"
#include "C_PlayPC.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_PlayPC : public APlayerController
{
	GENERATED_BODY()
	
public: // 변수
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated)
	FC_S_PlayerInfo MyInfo;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UC_SaveGame* SaveGameRef;

public: // 함수

	void Load();
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void PassCharacterToServer(FC_S_PlayerInfo NewInfo);
};
