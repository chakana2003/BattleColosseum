// Fill out your copyright notice in the Description page of Project Settings.

#include "C_LobbyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "UnrealNetwork.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"


AC_LobbyCharacter::AC_LobbyCharacter() {
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovement"));
	UserID = CreateDefaultSubobject<UTextRenderComponent>(TEXT("UserID"));

	RootComponent = Capsule;
	SkeletalMesh->SetupAttachment(Capsule);
	SpringArm->AttachToComponent((USceneComponent*)Capsule, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	UserID->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform);

	SkeletalMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	bReplicates = true;

	// 변수 초기화
	IsSprinting = false;
	SprintRate = 100.f;
	RightView = false;

	this->bUseControllerRotationPitch = false;				// 플레이어가 위아래로 돌아가지 않도록
	SpringArm->bUsePawnControlRotation = true;				// 컨트롤러의 회전값을 사용하도록
	SpringArm->bInheritPitch = true;						// 카메라만 위아래로 돌아가도록
	SpringArm->SocketOffset = FVector(0.f, 50.f, 70.f);		// 오른쪽 어깨위로 설정
	SpringArm->TargetArmLength = 150.f;						// 카메라 거리 가깝게 설정
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 9.0f;
	SpringArm->CameraRotationLagSpeed = 9.0f;

	Capsule->SetNotifyRigidBodyCollision(true);  // hit 이벤트 활성화(옛날이름)
	Capsule->SetCapsuleHalfHeight(88.f);
	Capsule->SetCapsuleRadius(34.f);

	UserID->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	UserID->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	UserID->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	UserID->SetText(TEXT("USER ID"));
}

void AC_LobbyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Ori_Speed = 400.f;
	Sprint_Speed = Ori_Speed * SprintRate;
}

void AC_LobbyCharacter::MoveForward(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AC_LobbyCharacter::MoveRight(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorRightVector(), Value);
	}
}

bool AC_LobbyCharacter::ActiveSprint_Validate() {
	return true;
}

void AC_LobbyCharacter::ActiveSprint_Implementation() {
	if (!IsSprinting)
		IsSprinting = true;
}

bool AC_LobbyCharacter::DeActiveSprint_Validate() {
	return true;
}

void AC_LobbyCharacter::DeActiveSprint_Implementation() {
	if (IsSprinting)
		IsSprinting = false;
}

void AC_LobbyCharacter::SwitchView()
{
	if (RightView) {
		RightView = false;
		SpringArm->SocketOffset = FVector(0.f, -50.f, 70.f);
	}
	else {
		RightView = true;
		SpringArm->SocketOffset = FVector(0.f, 50.f, 70.f);
	}
}

void AC_LobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsSprinting) {
		// 캐릭터 무브먼트 컴포넌트의 Max Speed 값을 Sprint_Speed로 바꿈
		CharacterMovement->MaxWalkSpeed = Sprint_Speed;
	}
	else {
		// 캐릭터 무브먼트 컴포넌트의 Max Speed 값을 Ori_Speed로 바꿈
		CharacterMovement->MaxWalkSpeed = Ori_Speed;
	}
}

void AC_LobbyCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("K_MoveForward", this, &AC_LobbyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("K_MoveRight", this, &AC_LobbyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("K_LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("K_Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("K_Jump", IE_Pressed, this, &AC_LobbyCharacter::Jumpp);

	PlayerInputComponent->BindAction("K_Sprint", IE_Pressed, this, &AC_LobbyCharacter::ActiveSprint);
	PlayerInputComponent->BindAction("K_Sprint", IE_Released, this, &AC_LobbyCharacter::DeActiveSprint);

	PlayerInputComponent->BindAction("K_SwitchView", IE_Pressed, this, &AC_LobbyCharacter::SwitchView);
}

void AC_LobbyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AC_LobbyCharacter, IsSprinting);
}

void AC_LobbyCharacter::Jumpp() {
	CharacterMovement->DoJump(true);
}

