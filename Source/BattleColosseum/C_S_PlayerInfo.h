// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_S_PlayerInfo.generated.h"

USTRUCT(BlueprintType)
struct FC_S_Characters {
	GENERATED_USTRUCT_BODY()

	FC_S_Characters();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Sumnail;
};


USTRUCT(BlueprintType)
struct FC_S_PlayerInfo {
	GENERATED_USTRUCT_BODY()

	FC_S_PlayerInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FC_S_Characters SelectCharacter;
};