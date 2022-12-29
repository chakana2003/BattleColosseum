// Fill out your copyright notice in the Description page of Project Settings.

#include "C_NullCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/TextRenderComponent.h"
#include "Lobby/C_LobbyPC.h"


AC_NullCharacter::AC_NullCharacter() {
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Sphere(TEXT("StaticMesh'/Game/Meshes/SM_Cube.SM_Cube'"));

	RootComponent = Box;
	StaticMesh->AttachToComponent(Box, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->AttachToComponent(StaticMesh,FAttachmentTransformRules::KeepRelativeTransform);
	Camera->AttachToComponent(SpringArm,FAttachmentTransformRules::KeepRelativeTransform);

	Projectile->bRotationFollowsVelocity = false;
	Projectile->bShouldBounce = true;
	Projectile->InitialSpeed = 0.f;
	Projectile->bBounceAngleAffectsFriction = true;
	Projectile->bInitialVelocityInLocalSpace = false;
	Projectile->ProjectileGravityScale = 0.3f;
	Projectile->Bounciness = 0.98f;
	Projectile->Friction = 0.1f;
	Projectile->bForceSubStepping = true;
	Projectile->MaxSimulationTimeStep = 0.02f;
	Projectile->MaxSimulationIterations = 10;
	Projectile->SetIsReplicated(true);
	Projectile->BounceVelocityStopSimulatingThreshold = 0.5f;

	Box->SetCollisionProfileName(TEXT("BlockAll"));
	Box->SetSimulatePhysics(true);
	Box->SetBoxExtent(FVector(25.f));

	if (SM_Sphere.Succeeded()) {
		StaticMesh->SetStaticMesh(SM_Sphere.Object);
	}
	StaticMesh->SetRelativeScale3D(FVector(0.5f));

	SpringArm->TargetArmLength = 500.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bDoCollisionTest = true;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->ProbeSize = 0.1f;
	SpringArm->CameraLagSpeed = 20.f;
	SpringArm->CameraRotationLagSpeed = 20.f;
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
}

void AC_NullCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("K_ImpactW", IE_Pressed, this, &AC_NullCharacter::ForceW);
	PlayerInputComponent->BindAction("K_ImpactS", IE_Pressed, this, &AC_NullCharacter::ForceS);
	PlayerInputComponent->BindAction("K_ImpactA", IE_Pressed, this, &AC_NullCharacter::ForceA);
	PlayerInputComponent->BindAction("K_ImpactD", IE_Pressed, this, &AC_NullCharacter::ForceD);
	PlayerInputComponent->BindAction("K_Jump", IE_Pressed, this, &AC_NullCharacter::JumpHigh);

	// PlayerInputComponent->BindAxis("K_LookUp", this, &AC_NullCharacter::LookUp);
	PlayerInputComponent->BindAxis("K_Turn", this, &AC_NullCharacter::Turn);
}

void AC_NullCharacter::LookUp(float Val) {
	SpringArm->AddRelativeRotation(FRotator(Val, 0.f, 0.f));
}

void AC_NullCharacter::Turn(float Val) {
	SpringArm->AddRelativeRotation(FRotator(0.f, Val, 0.f));
}

bool AC_NullCharacter::ForceW_Validate() {
	return true;
}

void AC_NullCharacter::ForceW_Implementation() {
	StaticMesh->AddImpulseAtLocation(FVector(20000.f, 0.f, 0.f), GetActorLocation());
}

bool AC_NullCharacter::ForceS_Validate() {
	return true;
}
void AC_NullCharacter::ForceS_Implementation() {
	StaticMesh->AddImpulseAtLocation(FVector(-20000.f, 0.f, 0.f), GetActorLocation());
}

bool AC_NullCharacter::ForceA_Validate() {
	return true;
}
void AC_NullCharacter::ForceA_Implementation() {
	StaticMesh->AddImpulseAtLocation(FVector(0.f, -20000.f, 0.f), GetActorLocation());
}

bool AC_NullCharacter::ForceD_Validate() {
	return true;
}
void AC_NullCharacter::ForceD_Implementation() {
	StaticMesh->AddImpulseAtLocation(FVector(0.f, 20000.f, 0.f), GetActorLocation());
}

bool AC_NullCharacter::JumpHigh_Validate() {
	return true;
}
void AC_NullCharacter::JumpHigh_Implementation() {
	StaticMesh->AddImpulseAtLocation(FVector(0.f, 0.f, 100000.f), GetActorLocation());
}