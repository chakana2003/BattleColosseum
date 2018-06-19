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
<<<<<<< HEAD
<<<<<<< HEAD
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
=======
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
>>>>>>> parent of 37a52f7... Play ë§µ ìž…ìž¥ê¹Œì§€ êµ¬í˜„
=======
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
>>>>>>> parent of 37a52f7... Play ë§µ ìž…ìž¥ê¹Œì§€ êµ¬í˜„
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

	// º¯¼ö ÃÊ±âÈ­
	IsSprinting = false;
	SprintRate = 100.f;
	RightView = false;

	this->bUseControllerRotationPitch = false;				// ÇÃ·¹ÀÌ¾î°¡ À§¾Æ·¡·Î µ¹¾Æ°¡Áö ¾Êµµ·Ï
	SpringArm->bUsePawnControlRotation = true;				// ÄÁÆ®·Ñ·¯ÀÇ È¸Àü°ªÀ» »ç¿ëÇÏµµ·Ï
	SpringArm->bInheritPitch = true;						// Ä«¸Þ¶ó¸¸ À§¾Æ·¡·Î µ¹¾Æ°¡µµ·Ï
	SpringArm->SocketOffset = FVector(0.f, 50.f, 70.f);		// ¿À¸¥ÂÊ ¾î±úÀ§·Î ¼³Á¤
	SpringArm->TargetArmLength = 150.f;						// Ä«¸Þ¶ó °Å¸® °¡±õ°Ô ¼³Á¤
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 9.0f;
	SpringArm->CameraRotationLagSpeed = 9.0f;

<<<<<<< HEAD
<<<<<<< HEAD
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);  // hit ÀÌº¥Æ® È°¼ºÈ­(¿¾³¯ÀÌ¸§)
	GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);
=======
	Capsule->SetNotifyRigidBodyCollision(true);  // hit ÀÌº¥Æ® È°¼ºÈ­(¿¾³¯ÀÌ¸§)
	Capsule->SetCapsuleHalfHeight(88.f);
	Capsule->SetCapsuleRadius(34.f);
>>>>>>> parent of 37a52f7... Play ë§µ ìž…ìž¥ê¹Œì§€ êµ¬í˜„
=======
	Capsule->SetNotifyRigidBodyCollision(true);  // hit ÀÌº¥Æ® È°¼ºÈ­(¿¾³¯ÀÌ¸§)
	Capsule->SetCapsuleHalfHeight(88.f);
	Capsule->SetCapsuleRadius(34.f);
>>>>>>> parent of 37a52f7... Play ë§µ ìž…ìž¥ê¹Œì§€ êµ¬í˜„

	UserID->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	UserID->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	UserID->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	UserID->SetText(FText::FromString(TEXT("UserID")));
	UserID->SetIsReplicated(true);

	CharacterMovement->Activate(true);
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
<<<<<<< HEAD
<<<<<<< HEAD
	if (GetCharacterMovement()) {
		if (IsSprinting) {
			// Ä³¸¯ÅÍ ¹«ºê¸ÕÆ® ÄÄÆ÷³ÍÆ®ÀÇ Max Speed °ªÀ» Sprint_Speed·Î ¹Ù²Þ
			GetCharacterMovement()->MaxWalkSpeed = Sprint_Speed;
		}
		else {
			// Ä³¸¯ÅÍ ¹«ºê¸ÕÆ® ÄÄÆ÷³ÍÆ®ÀÇ Max Speed °ªÀ» Ori_Speed·Î ¹Ù²Þ
			GetCharacterMovement()->MaxWalkSpeed = Ori_Speed;
		}
=======
=======
>>>>>>> parent of 37a52f7... Play ë§µ ìž…ìž¥ê¹Œì§€ êµ¬í˜„
	if (IsSprinting) {
		// Ä³¸¯ÅÍ ¹«ºê¸ÕÆ® ÄÄÆ÷³ÍÆ®ÀÇ Max Speed °ªÀ» Sprint_Speed·Î ¹Ù²Þ
		CharacterMovement->MaxWalkSpeed = Sprint_Speed;
	}
	else {
		// Ä³¸¯ÅÍ ¹«ºê¸ÕÆ® ÄÄÆ÷³ÍÆ®ÀÇ Max Speed °ªÀ» Ori_Speed·Î ¹Ù²Þ
		CharacterMovement->MaxWalkSpeed = Ori_Speed;
<<<<<<< HEAD
>>>>>>> parent of 37a52f7... Play ë§µ ìž…ìž¥ê¹Œì§€ êµ¬í˜„
=======
>>>>>>> parent of 37a52f7... Play ë§µ ìž…ìž¥ê¹Œì§€ êµ¬í˜„
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

