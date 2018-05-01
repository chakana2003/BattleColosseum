// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "Classes/Components/CapsuleComponent.h"
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
	// 컴포넌트.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code")
	class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code")
	class UCameraComponent* cam;

	// 변수들.

	// RunningState, 뛰기 불리언.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code")
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
	// if set true, Be Man, Nor Be Woman.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	bool SexMan;										
	// 성별(기본값 : 남자).
	class USkeletalMesh* ManMesh;
	class USkeletalMesh* WomanMesh;

	// Called when the game starts or when spawned.
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
