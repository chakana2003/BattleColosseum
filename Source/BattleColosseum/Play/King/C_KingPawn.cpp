// Fill out your copyright notice in the Description page of Project Settings.

#include "C_KingPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AC_KingPawn::AC_KingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene= CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	Camera->SetupAttachment(Scene);
	//CastArrow= CreateDefaultSubobject<UArrowComponent>(TEXT("CastArrow"));

	//CastArrow->SetupAttachment(Camera);
	
	//rot=FRotator(0, Controller->GetControlRotation().Yaw, 0);
	
	//GetActorForwardVector();
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
//	AddMovementInput(ForwordDirection, Value);

}

void AC_KingPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
void AC_KingPawn::ZoomIn(float Value)
{
	
}
