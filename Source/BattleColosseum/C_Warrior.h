// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include "C_Warrior.generated.h"


UCLASS()
class BATTLECOLOSSEUM_API AC_Warrior : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Warrior();

protected:
	// 컴포넌트
	class USpringArmComponent* springArm;
	class UCameraComponent* cam;

	// 변수들
	bool IsSprinting;									// 뛰기 불리언
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintRate;									// 뛰기 비율
	float Ori_Speed;									// 원래 속도
	float Sprint_Speed;									// 변한 속도
	bool RightView;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SexMan;										// 성별(기본값 : 남자)
	class USkeletalMesh* ManMesh;
	class USkeletalMesh* WomanMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 함수들
		// 입력 관련 행동 함수
	void MoveForward(float Value);						// 앞으로 가기
	void MoveRight(float Value);						// 옆으로 가기
	void ActiveSprint();								// 뛰기 활성화
	void DeActiveSprint();								// 뛰기 비활성화
	void SwitchView();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
