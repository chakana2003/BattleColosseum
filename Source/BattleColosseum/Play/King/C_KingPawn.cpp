// Fill out your copyright notice in the Description page of Project Settings.

#include "C_KingPawn.h"


// Sets default values
AC_KingPawn::AC_KingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

