// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "C_S_PlayerInfo.h"
#include "C_PlayPS.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_PlayPS : public APlayerState
{
	GENERATED_BODY()
	
public:		// 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FC_S_PlayerInfo MyInfo;

public:		// 함수
	UFUNCTION(BlueprintCallable, Client, reliable, WithValidation)
	void CopyInfo(FC_S_PlayerInfo TableInfo);

	void GetLifetimeReplicationProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
};
