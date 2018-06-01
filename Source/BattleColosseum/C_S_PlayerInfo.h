// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_S_PlayerInfo.generated.h"

USTRUCT(BlueprintType)
struct FC_S_Characters {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	class ACharacter* Character;

	UPROPERTY()
	class UTexture2D* Sumnail;
};


USTRUCT(BlueprintType)
struct FC_S_PlayerInfo {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FText Name;

	UPROPERTY()
	class UTexture2D* Icon;

	UPROPERTY()
	FText status;

	UPROPERTY()
	FC_S_Characters SelectCharacter;
};