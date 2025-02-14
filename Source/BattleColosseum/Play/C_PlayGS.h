// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_PlayGS.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_PlayGS : public AGameStateBase
{
	GENERATED_BODY()

public: // 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = TimeIncrese)
	float ms;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	int sec;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	int min;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	int hour;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	bool PreStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	bool DoesStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_LeftTime)
	float LeftStartTime;

	// 지역 제한을 확인하는 bool
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	bool WaitForDeleteArea;

public: // 함수
	AC_PlayGS();

	virtual void Tick(float DeltaSeconds) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
	void OnRep_LeftTime();

	UFUNCTION()
	void TimeIncrese();

	virtual void BeginPlay() override;

};
