// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/TriggerBox.h"
#include "Play/King/C_KingPawn.h"
#include "Play/Warrior/C_WarriorCharacter.h"
#include "Play/C_BurningArea.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ATriggerBox*> StartBoxes;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FTimerHandle StartTimeHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle CountdownTimeHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle GameTimeHandle;
	
	// NULL 캐릭터 상태인 시간.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	float NullCharTime;
	// Lobby캐릭터를 생성하고 나서의 시간.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	float LobbyCharTime;

	// 불타는 시간까지 타임.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	float BurningTime;
	// 다음 불타기 알람을 주기까지의 시간.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	float WarningTime;

	// 불타는 타임 이벤트 핸들러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle BurningTimeHandle;
	// 다음 불타기를 기다리는 타임 이벤트 핸들러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle WarningTimeHandle;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	TArray<AC_BurningArea*> BurningAreas;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int BurningOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WorldTime;

	// 중도참여 가능한지 안한지 제어하는 변수.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	bool JoinPossible;

	// 왕이 정한 제한될 구역을 저장하는 변수.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<int> KingOrder;

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
	void CountdownTimer();

	UFUNCTION(BlueprintCallable)
	void SpawnLobbyCharacter();		// 로비 캐릭터 생성 함수.

	UFUNCTION(Server, reliable, WithValidation)
	void RealStartGame();	// 실제 게임캐릭터 생성 함수. 

	TArray<int> SetSpawnLocation();

	UFUNCTION(BlueprintImplementableEvent)
	void SendCurrentPC(APlayerController* Player);

	// 게임 시작 시 워리어 초기설정할 블루프린트를 호출할 함수.
	UFUNCTION(BlueprintImplementableEvent)
	void SendWarriorFromCode(APlayerController* Player);
	// 게임 시작 시 킹 초기설정할 블루프린트를 호출할 함수.
	UFUNCTION(BlueprintImplementableEvent)
	void SendKingFromCode(APlayerController* Player);

	UFUNCTION(BlueprintImplementableEvent)
	void BeginStartTimer();					// 카운트다운 시작

	UFUNCTION(BlueprintImplementableEvent)
	void PopStartTimer();					// 카운트다운 호출

	UFUNCTION(BlueprintImplementableEvent)
	void EndStartTimer();					// 카운트다운 종료

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);

	UFUNCTION(BlueprintCallable)
	void GameTime();							// 인게임 처리 함수.

	void PreBurning();

	UFUNCTION(BlueprintCallable)
	void StartBurning();						// 불타기 시작함.

	UFUNCTION(BlueprintImplementableEvent)
	void BroadBurningAreaToAll(FName AreaNumb);		// 불타기 시작하는 위젯애니메이션 재생을 위한 함수.

	UFUNCTION(BlueprintCallable)
	void CreateBurningArray();
	
	UFUNCTION(BlueprintImplementableEvent)
	void LaunchFireArrow();
};
