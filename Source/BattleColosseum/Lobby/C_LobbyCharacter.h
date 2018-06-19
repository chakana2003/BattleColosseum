// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_LobbyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_LobbyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AC_LobbyCharacter();

public: // 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTextRenderComponent* UserID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;

	// RunningState, 뛰기 불리언.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code", Replicated)
		bool IsSprinting;
	//  Run Rate, 뛰기 비율.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Code")
		float SprintRate;
	// OriginSpeed, 원래 속도.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Code")
		float Ori_Speed;
	// SprintSpeed, 변한 속도. 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Code")
		float Sprint_Speed;
	// Look Over Right Shoulder, 오른쪽어깨로 보고있니. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code")
		bool RightView;

public: // 함수

	virtual void BeginPlay() override;

	// 입력 관련 행동 함수
	UFUNCTION(BlueprintCallable)
		void MoveForward(float Value);						// 앞으로 가기
	UFUNCTION(BlueprintCallable)
		void MoveRight(float Value);						// 옆으로 가기
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
		void ActiveSprint();								// 뛰기 활성화
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
		void DeActiveSprint();								// 뛰기 비활성화
	UFUNCTION()
		void SwitchView();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	void Jumpp();
	
	
};
