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

public: // º¯¼ö
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
<<<<<<< HEAD
<<<<<<< HEAD
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;
=======
>>>>>>> parent of 37a52f7... Play ë§µ ìž…ìž¥ê¹Œì§€ êµ¬í˜„
=======
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Cam;
>>>>>>> 37a52f78132bbfa08e7339e6a5f52f3fc407f624

public: // ÇÔ¼ö

	virtual void BeginPlay() override;
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
};
