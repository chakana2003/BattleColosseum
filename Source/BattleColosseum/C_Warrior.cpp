// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Warrior.h"



// Sets default values
AC_Warrior::AC_Warrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���� �ʱ�ȭ
	IsSprinting = false;
	SprintRate = 100.f;
	RightView = false;
	SexMan = true;

	// ������Ʈ ����
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("W_Camera"));
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("W_SprintArm"));

	//������Ʈ �ʱ�ȭ
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));					// ĳ���� ��ġ �ʱ�ȭ
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));					// ĳ���� ���� �ʱ�ȭ
	springArm->AttachToComponent((USceneComponent*)GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	cam->AttachToComponent(springArm, FAttachmentTransformRules::KeepRelativeTransform);
	this->bUseControllerRotationPitch = false;				// �÷��̾ ���Ʒ��� ���ư��� �ʵ���
	springArm->bUsePawnControlRotation = true;				// ��Ʈ�ѷ��� ȸ������ ����ϵ���
	springArm->bInheritPitch = true;						// ī�޶� ���Ʒ��� ���ư�����
	springArm->SocketOffset = FVector(0.f, 50.f, 70.f);		// ������ ������� ����
	springArm->TargetArmLength = 150.f;						// ī�޶� �Ÿ� ������ ����
	springArm->bEnableCameraLag = true;
	springArm->bEnableCameraRotationLag = true;
	springArm->CameraLagSpeed = 9.0f;
	springArm->CameraRotationLagSpeed = 9.0f;

	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);  // hit �̺�Ʈ Ȱ��ȭ(�����̸�)

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_Man(TEXT("/Game/Meshes/Characters/Male/ColoM.ColoM"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_Woman(TEXT("/Game/Meshes/Characters/Female/ColoW.ColoW"));
	
	ManMesh = SM_Man.Object;
	WomanMesh = SM_Woman.Object;
}

// Called when the game starts or when spawned
void AC_Warrior::BeginPlay()
{
	Super::BeginPlay();
	
	Ori_Speed = 400.f;
	Sprint_Speed = Ori_Speed * SprintRate;
	SwitchView();
	if (SexMan) {
		GetMesh()->SetSkeletalMesh(ManMesh);
	}
	else {
		GetMesh()->SetSkeletalMesh(WomanMesh);
	}
}

void AC_Warrior::MoveForward(float Value)
{
	if (Value != 0.f) {
		if (IsSprinting) {
			// ĳ���� �����Ʈ ������Ʈ�� Max Speed ���� Sprint_Speed�� �ٲ�
			GetCharacterMovement()->MaxWalkSpeed = Sprint_Speed;

			AddMovementInput(GetActorForwardVector(), Value);
		}
		else {
			// ĳ���� �����Ʈ ������Ʈ�� Max Speed ���� Ori_Speed�� �ٲ�
			GetCharacterMovement()->MaxWalkSpeed = Ori_Speed;

			AddMovementInput(GetActorForwardVector(), Value);
		}
	}
}

void AC_Warrior::MoveRight(float Value)
{
	if (Value != 0.f) {
		if (IsSprinting) {
			// ĳ���� �����Ʈ ������Ʈ�� Max Speed ���� Sprint_Speed�� �ٲ�
			GetCharacterMovement()->MaxWalkSpeed = Sprint_Speed;

			AddMovementInput(GetActorRightVector(), Value);
		}
		else {
			// ĳ���� �����Ʈ ������Ʈ�� Max Speed ���� Ori_Speed�� �ٲ�
			GetCharacterMovement()->MaxWalkSpeed = Ori_Speed;

			AddMovementInput(GetActorRightVector(), Value);
		}
	}
}

void AC_Warrior::ActiveSprint()
{
	if (!IsSprinting)
		IsSprinting = true;
}

void AC_Warrior::DeActiveSprint()
{
	if (IsSprinting)
		IsSprinting = false;
}

void AC_Warrior::SwitchView()
{
	if (RightView) {
		RightView = false;
		springArm->SocketOffset = FVector(0.f, -50.f, 70.f);
	}
	else {
		RightView = true;
		springArm->SocketOffset = FVector(0.f, 50.f, 70.f);
	}
}

// Called every frame
void AC_Warrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("K_MoveForward", this, &AC_Warrior::MoveForward);
	PlayerInputComponent->BindAxis("K_MoveRight", this, &AC_Warrior::MoveRight);
	PlayerInputComponent->BindAxis("K_LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("K_TurnRight", this, &ACharacter::AddControllerYawInput);
	
	PlayerInputComponent->BindAction("K_Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("K_Sprint", IE_Pressed, this, &AC_Warrior::ActiveSprint);
	PlayerInputComponent->BindAction("K_Sprint", IE_Released, this, &AC_Warrior::DeActiveSprint);

	PlayerInputComponent->BindAction("K_SwitchView", IE_Pressed, this, &AC_Warrior::SwitchView);
}

