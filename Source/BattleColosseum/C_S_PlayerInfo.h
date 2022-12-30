// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_S_PlayerInfo.generated.h"

USTRUCT(BlueprintType)
struct FC_S_Characters
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Sumnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<APawn> LobbyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<APawn> GameCharacter;
};


USTRUCT(BlueprintType)
struct FC_S_PlayerInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FC_S_Characters SelectCharacter;
};