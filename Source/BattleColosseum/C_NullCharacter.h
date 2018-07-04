// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_NullCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_NullCharacter : public APawn
{
	GENERATED_BODY()
	
public:
	AC_NullCharacter();

public: // 변수
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	class UBoxComponent* Box;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UProjectileMovementComponent* Projectile;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTextRenderComponent* UserID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;

public: // 함수

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void ForceW();
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void ForceS();
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void ForceA();
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void ForceD();
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
	void JumpHigh();

	void LookUp(float Val);

	void Turn(float Val);
};


