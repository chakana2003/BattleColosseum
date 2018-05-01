// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Warrior.h"



// Sets default values
AC_Warrior::AC_Warrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 변수 초기화
	IsSprinting = false;
	SprintRate = 100.f;
	RightView = false;
	SexMan = true;

	// 컴포넌트 생성
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("W_Camera"));
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("W_SprintArm"));

	//컴포넌트 초기화
	GetMesh()->RelativeLocation = FVector(0.f, 0.f, -90.f);					// 캐릭터 위치 초기화
	GetMesh()->RelativeRotation = FRotator(0.f, -90.f, 0.f);					// 캐릭터 방향 초기화
	springArm->AttachToComponent((USceneComponent*)GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	cam->AttachToComponent(springArm, FAttachmentTransformRules::KeepRelativeTransform);
	this->bUseControllerRotationPitch = false;				// 플레이어가 위아래로 돌아가지 않도록
	springArm->bUsePawnControlRotation = true;				// 컨트롤러의 회전값을 사용하도록
	springArm->bInheritPitch = true;						// 카메라만 위아래로 돌아가도록
	springArm->SocketOffset = FVector(0.f, 50.f, 70.f);		// 오른쪽 어깨위로 설정
	springArm->TargetArmLength = 150.f;						// 카메라 거리 가깝게 설정
	springArm->bEnableCameraLag = true;
	springArm->bEnableCameraRotationLag = true;
	springArm->CameraLagSpeed = 9.0f;
	springArm->CameraRotationLagSpeed = 9.0f;

	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);  // hit 이벤트 활성화(옛날이름)

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
			// 캐릭터 무브먼트 컴포넌트의 Max Speed 값을 Sprint_Speed로 바꿈
			GetCharacterMovement()->MaxWalkSpeed = Sprint_Speed;

			AddMovementInput(GetActorForwardVector(), Value);
		}
		else {
			// 캐릭터 무브먼트 컴포넌트의 Max Speed 값을 Ori_Speed로 바꿈
			GetCharacterMovement()->MaxWalkSpeed = Ori_Speed;

			AddMovementInput(GetActorForwardVector(), Value);
		}
	}
}

void AC_Warrior::MoveRight(float Value)
{
	if (Value != 0.f) {
		if (IsSprinting) {
			// 캐릭터 무브먼트 컴포넌트의 Max Speed 값을 Sprint_Speed로 바꿈
			GetCharacterMovement()->MaxWalkSpeed = Sprint_Speed;

			AddMovementInput(GetActorRightVector(), Value);
		}
		else {
			// 캐릭터 무브먼트 컴포넌트의 Max Speed 값을 Ori_Speed로 바꿈
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

