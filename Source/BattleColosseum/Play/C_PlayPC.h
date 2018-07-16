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

	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void Load();
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void PassCharacterToServer(FC_S_PlayerInfo NewInfo);

	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void PossessingPawn(APawn* TargetPawn);

	void StartGame();

	UFUNCTION(BlueprintCallable, Client, reliable, WithValidation)
	void CopyInfo(FC_S_PlayerInfo NewInfo);

	UFUNCTION(BlueprintCallable, Client, reliable, WithValidation)
	void BeginPlayerController();

	// 게임 시작 시 워리어 초기설정할 블루프린트를 호출할 함수.
	UFUNCTION(BlueprintImplementableEvent)
	void SendWarriorFromCode();
	// 게임 시작 시 킹 초기설정할 블루프린트를 호출할 함수.
	UFUNCTION(BlueprintImplementableEvent)
	void SendKingFromCode();

	// if PC is King, return true, or not false. or fail, write log.
	UFUNCTION(BlueprintCallable)
	bool IsKing();
};