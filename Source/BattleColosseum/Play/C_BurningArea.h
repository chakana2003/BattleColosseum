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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	int Strong;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	bool IsBurning;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	int MyOrder;
public:		// 함수
	AC_BurningArea();

	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void SetActivate();

	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void MoreStrog();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
};
