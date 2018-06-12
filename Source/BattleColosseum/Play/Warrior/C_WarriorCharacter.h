// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_BaseCharacter.h"
#include "C_WarriorCharacter.generated.h"

UCLASS()
class BATTLECOLOSSEUM_API AC_WarriorCharacter : public AC_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_WarriorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:  // 변수
	class UCharacterMovementComponent* Movement;
	class UCapsuleComponent* Capsule;

public:  // 함수
	
};
