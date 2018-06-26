// Fill out your copyright notice in the Description page of Project Settings.

#include "C_SpawnBox.h"
#include "Components/BoxComponent.h"

// Sets default values
AC_SpawnBox::AC_SpawnBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCompo = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxCompo;

	BoxCompo->SetBoxExtent(FVector(2500.f, 2500.f, 100.f));

}

// Called when the game starts or when spawned
void AC_SpawnBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_SpawnBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

