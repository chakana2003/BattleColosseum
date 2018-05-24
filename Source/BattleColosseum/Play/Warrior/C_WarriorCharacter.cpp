// Fill out your copyright notice in the Description page of Project Settings.

#include "C_WarriorCharacter.h"


// Sets default values
AC_WarriorCharacter::AC_WarriorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_WarriorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_WarriorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_WarriorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

