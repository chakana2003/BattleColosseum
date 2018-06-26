// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SpawnBox.generated.h"

UCLASS()
class BATTLECOLOSSEUM_API AC_SpawnBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_SpawnBox();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* BoxCompo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
