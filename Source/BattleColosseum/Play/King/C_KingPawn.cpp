// Fill out your copyright notice in the Description page of Project Settings.

#include "C_KingPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AC_KingPawn::AC_KingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene= CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	Camera->SetupAttachment(Scene);
	CastArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("CastArrow"));

	CastArrow->SetupAttachment(Camera);
	
	// 생성자에서는 Controller 가 없기 때문에 NULL 을 반환해서 크러쉬 발생 - 에디터 강제종료
	//rot=FRotator(0, Controller->GetControlRotation().Yaw, 0);

	// 도수코드로 할 행동을 작성 요망

	// 예를들어

	// Arrow 컴포넌트를 카메라에 부착

	// Arrow 컴포넌트를 Yaw 로 90도 회전

	// Camera 를 root 로 설정

	// BoxCollision 의 Extend 를 30,50,10 으로 설정

	// 과 같이 도수코드로 작성해놓으면 내가 설정해줄께 설정하는거 한번 보면 감 올꺼야
	
}

// Called when the game starts or when spawned
void AC_KingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_KingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_KingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("K_MoveForward"), this, &AC_KingPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("K_Turn"), this, &AC_KingPawn::Turn);
	PlayerInputComponent->BindAxis(TEXT("K_MoveRight"), this, &AC_KingPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("K_LookUp"), this, &AC_KingPawn::Lookup);
	PlayerInputComponent->BindAxis(TEXT("K_ZoomIn"), this, &AC_KingPawn::ZoomIn);
}

void AC_KingPawn::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AC_KingPawn::Lookup(float Value)
{
	AddControllerPitchInput(Value);
}

void AC_KingPawn::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);

}

void AC_KingPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
void AC_KingPawn::ZoomIn(float Value)
{
	
}
