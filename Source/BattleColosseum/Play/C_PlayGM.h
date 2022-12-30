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
	
public: // ����
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
	
	// NULL ĳ���� ������ �ð�.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	float NullCharTime;
	// Lobbyĳ���͸� �����ϰ� ������ �ð�.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	float LobbyCharTime;

	// ��Ÿ�� �ð����� Ÿ��.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	float BurningTime;
	// ���� ��Ÿ�� �˶��� �ֱ������ �ð�.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	float WarningTime;

	// ��Ÿ�� Ÿ�� �̺�Ʈ �ڵ鷯
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle BurningTimeHandle;
	// ���� ��Ÿ�⸦ ��ٸ��� Ÿ�� �̺�Ʈ �ڵ鷯
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle WarningTimeHandle;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	TArray<AC_BurningArea*> BurningAreas;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int BurningOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WorldTime;

	// �ߵ����� �������� ������ �����ϴ� ����.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PipeLine)
	bool JoinPossible;

	// ���� ���� ���ѵ� ������ �����ϴ� ����.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<int> KingOrder;

public: // �Լ�

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
	void SpawnLobbyCharacter();		// �κ� ĳ���� ���� �Լ�.

	UFUNCTION(Server, reliable, WithValidation)
	void RealStartGame();	// ���� ����ĳ���� ���� �Լ�. 

	TArray<int> SetSpawnLocation();

	UFUNCTION(BlueprintImplementableEvent)
	void SendCurrentPC(APlayerController* Player);

	// ���� ���� �� ������ �ʱ⼳���� �������Ʈ�� ȣ���� �Լ�.
	UFUNCTION(BlueprintImplementableEvent)
	void SendWarriorFromCode(APlayerController* Player);
	// ���� ���� �� ŷ �ʱ⼳���� �������Ʈ�� ȣ���� �Լ�.
	UFUNCTION(BlueprintImplementableEvent)
	void SendKingFromCode(APlayerController* Player);

	UFUNCTION(BlueprintImplementableEvent)
	void BeginStartTimer();					// ī��Ʈ�ٿ� ����

	UFUNCTION(BlueprintImplementableEvent)
	void PopStartTimer();					// ī��Ʈ�ٿ� ȣ��

	UFUNCTION(BlueprintImplementableEvent)
	void EndStartTimer();					// ī��Ʈ�ٿ� ����

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);

	UFUNCTION(BlueprintCallable)
	void GameTime();							// �ΰ��� ó�� �Լ�.

	void PreBurning();

	UFUNCTION(BlueprintCallable)
	void StartBurning();						// ��Ÿ�� ������.

	UFUNCTION(BlueprintImplementableEvent)
	void BroadBurningAreaToAll(FName AreaNumb);		// ��Ÿ�� �����ϴ� �����ִϸ��̼� ����� ���� �Լ�.

	UFUNCTION(BlueprintCallable)
	void CreateBurningArray();
	
	UFUNCTION(BlueprintImplementableEvent)
	void LaunchFireArrow();
};
