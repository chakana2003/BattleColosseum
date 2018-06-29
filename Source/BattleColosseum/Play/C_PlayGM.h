// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/TriggerBox.h"
#include "C_PlayGM.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_PlayGM : public AGameModeBase
{
	GENERATED_BODY()
	
public: // 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	TArray<APlayerController*> ConnectedPlayerControllers;

	ATriggerBox* SpawnBox;

public: // 함수

	AC_PlayGM();
	
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void SpawnCharacter_WaitTime(APlayerController* PC, TSubclassOf<APawn> Character);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;

	virtual void PostSeamlessTravel() override;

	virtual void HandleSeamlessTravelPlayer(AController *& C) override;

	virtual void SwapPlayerControllers(APlayerController * OldPC, APlayerController * NewPC) override;

	UFUNCTION(BlueprintCallable)
	void CallSpawn();

};
