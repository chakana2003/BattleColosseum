// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	class AC_SpawnBox* SpawnBox;

public: // 함수

	AC_PlayGM();
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC);

	virtual void HandleSeamlessTravelPlayer(AController*& C);

	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void SpawnCharacter_WaitTime(APlayerController* PC, TSubclassOf<APawn> Character);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
};
