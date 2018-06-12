// Fill out your copyright notice in the Description page of Project Settings.

#include "C_NullCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ConstructorHelpers.h"


AC_NullCharacter::AC_NullCharacter() {
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Sphere(TEXT("StaticMesh'/Game/Meshes/Cube.Cube'"));


	RootComponent = Box;
	StaticMesh->AttachToComponent(Box, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->AttachToComponent(StaticMesh,FAttachmentTransformRules::KeepRelativeTransform);
	Camera->AttachToComponent(SpringArm,FAttachmentTransformRules::KeepRelativeTransform);

	Projectile->bRotationFollowsVelocity = false;
	Projectile->bShouldBounce = true;
	Projectile->InitialSpeed = 100.f;
	Projectile->bBounceAngleAffectsFriction = true;

	Box->SetCollisionProfileName(TEXT("BlockAll"));
	Box->SetSimulatePhysics(true);
	Box->SetBoxExtent(FVector(15.f));

	if (SM_Sphere.Succeeded()) {
		StaticMesh->SetStaticMesh(SM_Sphere.Object);
	}
	StaticMesh->SetRelativeScale3D(FVector(0.2f));

	SpringArm->TargetArmLength = 100.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bDoCollisionTest = true;

}
