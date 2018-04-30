// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Door.h"


// Sets default values
AC_Door::AC_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 변수 초기화
	Speed = 0.f;
	IsOpen = false;
	ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMesh(TEXT("StaticMesh'/Game/Meshes/Archtects/SM_Door.SM_Door'"));

	// 컴포넌트 생성
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	StaticDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	BoxTrig = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));


	// 컴포넌트 설정
	RootComponent = Collision;
	StaticDoor->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);
	BoxTrig->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);
	StaticDoor->SetStaticMesh(DoorMesh.Object);
	Collision->SetBoxExtent(FVector(40.f, 10.f, 110.f));
	StaticDoor->SetRelativeLocation(FVector(40.f, 0.f, -110.f));
	BoxTrig->SetBoxExtent(FVector(150.f, 150.f, 150.f));
	BoxTrig->OnComponentBeginOverlap.AddDynamic(this, &AC_Door::BoxTrigBeginOverlap);
	BoxTrig->OnComponentEndOverlap.AddDynamic(this, &AC_Door::BoxTrigEndOverlap);
}

// Called when the game starts or when spawned
void AC_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Door::DoorOpen()
{
	IsOpen = true;
	Speed = 0.f;
}

void AC_Door::DoorClose()
{
	IsOpen = false;
	Speed = 0.f;
}

void AC_Door::BoxTrigBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	DoorOpen();
}

void AC_Door::BoxTrigEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	DoorClose();
}

// Called every frame
void AC_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Speed < 1.f) {
		if (IsOpen) {
			StaticDoor->SetRelativeRotation(FRotator(0.f, FMath::Lerp(0.f, 90.f, Speed),0.f));
			Speed += 0.01f;
		}
		else {
			StaticDoor->SetRelativeRotation(FRotator(0.f, FMath::Lerp(90.f, 0.f, Speed),0.f));
			Speed += 0.01f;
		}
	}
}

