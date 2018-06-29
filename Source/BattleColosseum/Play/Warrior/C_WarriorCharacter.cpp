// Fill out your copyright notice in the Description page of Project Settings.

#include "C_WarriorCharacter.h"
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


AC_WarriorCharacter::AC_WarriorCharacter() {
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	UserID = CreateDefaultSubobject<UTextRenderComponent>(TEXT("UserID"));

	SpringArm->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	UserID->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	bReplicates = true;

	// 변수 초기화
	IsSprinting = false;
	SprintRate = 2.f;
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

	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);  // hit 이벤트 활성화(옛날이름)
	GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);

	UserID->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	UserID->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	UserID->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	UserID->SetText(FText::FromString(TEXT("UserID")));
	UserID->SetIsReplicated(true);
	UserID->SetVisibility(false);

	FPostProcessSettings NewProcessSetting;
	NewProcessSetting.DepthOfFieldMethod = EDepthOfFieldMethod::DOFM_Gaussian;
	NewProcessSetting.DepthOfFieldFocalDistance = 100.f;
	NewProcessSetting.DepthOfFieldFocalRegion = 80000.f;
	NewProcessSetting.bOverride_DepthOfFieldFocalDistance = true;
	NewProcessSetting.bOverride_DepthOfFieldFocalRegion = true;
	NewProcessSetting.bOverride_DepthOfFieldMethod = true;
	NewProcessSetting.bOverride_DepthOfFieldFarBlurSize = true;
	NewProcessSetting.DepthOfFieldFarBlurSize = 2.f;

	Camera->PostProcessSettings = NewProcessSetting;
}

void AC_WarriorCharacter::BeginPlay()
{
	Super::BeginPlay();

	Ori_Speed = 400.f;
	Sprint_Speed = Ori_Speed * SprintRate;
}

void AC_WarriorCharacter::MoveForward(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorForwardVector(), Value);
	}
	UpdateFSpeed(Value);
}

void AC_WarriorCharacter::MoveRight(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorRightVector(), Value);
	}
	UpdateRSpeed(Value);
}

bool AC_WarriorCharacter::ActiveSprint_Validate() {
	return true;
}

void AC_WarriorCharacter::ActiveSprint_Implementation() {
	if (!IsSprinting)
		IsSprinting = true;
}

bool AC_WarriorCharacter::DeActiveSprint_Validate() {
	return true;
}

void AC_WarriorCharacter::DeActiveSprint_Implementation() {
	if (IsSprinting)
		IsSprinting = false;
}

void AC_WarriorCharacter::SwitchView()
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

void AC_WarriorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsSprinting) {
		// 캐릭터 무브먼트 컴포넌트의 Max Speed 값을 Sprint_Speed로 바꿈
		GetCharacterMovement()->MaxWalkSpeed = Sprint_Speed;
	}
	else {
		// 캐릭터 무브먼트 컴포넌트의 Max Speed 값을 Ori_Speed로 바꿈
		GetCharacterMovement()->MaxWalkSpeed = Ori_Speed;
	}

}

void AC_WarriorCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("K_MoveForward", this, &AC_WarriorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("K_MoveRight", this, &AC_WarriorCharacter::MoveRight);
	PlayerInputComponent->BindAxis("K_LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("K_Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("K_Jump", IE_Pressed, this, &AC_WarriorCharacter::Jumpp);

	PlayerInputComponent->BindAction("K_Sprint", IE_Pressed, this, &AC_WarriorCharacter::ActiveSprint);
	PlayerInputComponent->BindAction("K_Sprint", IE_Released, this, &AC_WarriorCharacter::DeActiveSprint);

	PlayerInputComponent->BindAction("K_SwitchView", IE_Pressed, this, &AC_WarriorCharacter::SwitchView);
}

void AC_WarriorCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AC_WarriorCharacter, IsSprinting);
	DOREPLIFETIME(AC_WarriorCharacter, FSpeed);
	DOREPLIFETIME(AC_WarriorCharacter, RSpeed);
}

void AC_WarriorCharacter::Jumpp() {
	Jump();
}

bool AC_WarriorCharacter::UpdateFSpeed_Validate(float NewSpeed) {
	return true;
}
void AC_WarriorCharacter::UpdateFSpeed_Implementation(float NewSpeed) {
	FSpeed = NewSpeed;
}

bool AC_WarriorCharacter::UpdateRSpeed_Validate(float NewSpeed) {
	return true;
}
void AC_WarriorCharacter::UpdateRSpeed_Implementation(float NewSpeed) {
	RSpeed = NewSpeed;
}