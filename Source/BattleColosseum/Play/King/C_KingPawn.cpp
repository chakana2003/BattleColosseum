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
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CastArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("CastArrow"));
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	Scene->SetupAttachment(RootComponent);
	Camera->SetupAttachment(Scene);
	PrimaryActorTick.bCanEverTick = true;
	CastArrow->SetupAttachment(Camera);
	FloatingMovement->MaxSpeed = 300000;
	Tags.Add(TEXT("King"));
	
	// 생성자에서는 Controller 가 없기 때문에 NULL 을 반환해서 크러쉬 발생 - 에디터 강제종료

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
	PlayerInputComponent->BindAxis(TEXT("K_MoveForward"), this, &AC_KingPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("K_Turn"), this, &AC_KingPawn::Turn);
	PlayerInputComponent->BindAxis(TEXT("K_MoveRight"), this, &AC_KingPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("K_LookUp"), this, &AC_KingPawn::Lookup);
	PlayerInputComponent->BindAxis(TEXT("K_ZoomIn"), this, &AC_KingPawn::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("K_KingSpeedMode"), IE_Pressed, this, &AC_KingPawn::SpeedMoveMode);
	PlayerInputComponent->BindAction(TEXT("K_KingSpeedMode"), IE_Released, this, &AC_KingPawn::ReturnSpeedMoveMode);
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
	AddMovementInput(FVector(GetActorForwardVector().X, GetActorForwardVector().Y,0), Value);
	
}

void AC_KingPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
void AC_KingPawn::ZoomIn(float Value)
{
	ZoomVector = (FVector(GetActorForwardVector().X, GetActorForwardVector().Y, -0.5)*Value * 1200);
	AddActorWorldOffset(ZoomVector);
}

void AC_KingPawn::SpeedMoveMode()
{
	FloatingMovement->MaxSpeed = FloatingMovement->MaxSpeed * 2;
}

void AC_KingPawn::ReturnSpeedMoveMode()
{
	FloatingMovement->MaxSpeed = FloatingMovement->MaxSpeed / 2;
}
