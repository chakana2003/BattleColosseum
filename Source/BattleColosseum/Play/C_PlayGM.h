// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/TriggerBox.h"
#include "Play/King/C_KingPawn.h"
#include "Play/Warrior/C_WarriorCharacter.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AC_WarriorCharacter*> Warriors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AC_KingPawn* King;

	class ATriggerBox* SpawnBox;

	TArray<ATriggerBox*> StartBoxes;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FTimerHandle StartTimeHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle CountdownTimeH;

public: // 함수

	AC_PlayGM();
	
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void SpawnCharacter_WaitTime(APlayerController* PC, TSubclassOf<APawn> Character);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;

	virtual void PostSeamlessTravel() override;

	virtual void HandleSeamlessTravelPlayer(AController *& C) override;

	virtual void SwapPlayerControllers(APlayerController * OldPC, APlayerController * NewPC) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void CallSpawn();

	UFUNCTION()
	void StartTimer();

	void YesSpawn();

	UFUNCTION(Server, reliable, WithValidation)
	void RealStartGame();

	TArray<int> SetSpawnLocation();

	UFUNCTION(BlueprintImplementableEvent)
	void SendCurrentPC(APlayerController* Player);

	UFUNCTION(BlueprintImplementableEvent)
	void SendWarriorFromCode(APlayerController* Player);

	UFUNCTION(BlueprintImplementableEvent)
	void BeginStartTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void PopStartTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void EndStartTimer();
};
