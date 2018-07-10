// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PainCausingVolume.h"
#include "C_BurningArea.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_BurningArea : public APainCausingVolume
{
	GENERATED_BODY()
	
public:		// 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = FromCode)
	int Strong;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = FromCode)
	int MyOrder;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = FromCode)
	bool MoveComplete;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FromCode)
	float MoveingRate = 100.f;
public:		// 함수
	AC_BurningArea();

	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void SetActivate();

	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void MoreStrog();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
