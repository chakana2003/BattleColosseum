// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_BaseCharacter.h"
#include "C_NullCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_NullCharacter : public AC_BaseCharacter
{
	GENERATED_BODY()
	
public:
	AC_NullCharacter();

public: // 변수
	class UBoxComponent* Box;
	class UProjectileMovementComponent* Projectile;
	class UStaticMeshComponent* StaticMesh;
	class USpringArmComponent* SpringArm;

public: // 함수
	
	
};
