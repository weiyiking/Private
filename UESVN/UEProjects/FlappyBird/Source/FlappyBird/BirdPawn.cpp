// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdPawn.h"
#include <PaperFlipbookComponent.h>
#include <ConstructorHelpers.h>
#include <PaperFlipbook.h>
#include <Camera/CameraComponent.h>
#include <Curves/CurveFloat.h>
#include <Sound/SoundWave.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ABirdPawn::ABirdPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��Ҫ�ȸ�С���һ����
	//CreateDefaultSubobject��������һ�������
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	BirdRender = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BirdRenderComp"));
	//�������������
	BirdRender->SetupAttachment(RootComponent);
	//������Ķ����ʲ�
	ConstructorHelpers::FObjectFinder<UPaperFlipbook> BirdSource(TEXT("PaperFlipbook'/Game/FlappyBird/Flipbooks/Birds/FB_Bird_Red.FB_Bird_Red'"));
	//���ü��صĶ����ʲ����ʲ����
	BirdRender->SetFlipbook(BirdSource.Object);

	//����һ��������
	MainCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCameraComp"));
	//�������������ϵ���ŵ�����
	MainCameraComp->SetupAttachment(RootComponent);
	//���������ת
	MainCameraComp->SetRelativeRotation(FRotator(0, -90, 0));
	//���� �����������ƶ�����Y���ƶ�
	MainCameraComp->SetRelativeLocation(FVector(0, 50, 0));
	//��������ӿ�ģʽ
	MainCameraComp->SetProjectionMode(ECameraProjectionMode::Orthographic);
	//��������ӿڳߴ�
	MainCameraComp->SetOrthoWidth(1000.f);

}

// Called when the game starts or when spawned
void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();
	LockBirdPhysicState();

	//�������������ʲ�
	BirdFloatCurve = LoadObject<UCurveFloat>(nullptr, TEXT("CurveFloat'/Game/FlappyBird/Data/CUR_BirdFloat.CUR_BirdFloat'"));

	if (BirdFloatCurve)//��ָ�벻Ϊnullʱ��ִ��if�ڵ��߼�
	{
		//ͨ��������ʱ��ֵ��ȡ��������
		float Value = BirdFloatCurve->GetFloatValue(1);
		UE_LOG(LogTemp, Log, TEXT("Load Success  %f"), Value);
	}
	if (!BirdFloatCurve)//��ָ��Ϊnullʱ��ִ��if�ڵ��߼�
	{
		UE_LOG(LogTemp, Log, TEXT("Load Error"));
	}
	//���������ļ�
	FlySound = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/FlappyBird/Sounds/fly.fly'"));
	DropSound = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/FlappyBird/Sounds/dash.dash'"));
	DeadSound = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/FlappyBird/Sounds/dead.dead'"));
}

void ABirdPawn::OnDoFly()
{
	if (CurrentState != EBirdState::EBS_Fly)
	{
		return;
	}

	//Ϊ�˽���������ù�ϵ������������֮ǰ�Ƚ�����ƶ��ٶ�ȥ��
	BirdRender->SetPhysicsLinearVelocity(FVector::ZeroVector);//�޸��ٶ�Ϊ0
	//����һ������������������
	BirdRender->AddImpulse(FVector::UpVector * 400, NAME_None, true);
	//��������
	UGameplayStatics::PlaySound2D(this, FlySound);
}

void ABirdPawn::LockBirdPhysicState()
{
	//���������Ĳ�����ϵ
	
	//��ȡ����bodyʵ��
	FBodyInstance* Body = BirdRender->GetBodyInstance();
	if (Body)
	{
		//������ת
		Body->bLockXRotation = true;
		Body->bLockZRotation = true;
		//����λ��
		Body->bLockYTranslation = true;
		//����Լ����
		Body->CreateDOFLock();
	}
}

void ABirdPawn::UpdateFace(float DeltaTime)
{
	if (CurrentState == EBirdState::EBS_Wait || CurrentState == EBirdState::EBS_Dead)
	{
		return;
	}

	//��ȡZ���ƫ��ֵ
	float offsetZ = BirdRender->GetPhysicsLinearVelocity().Z;
	//Լ��һ��Pitch��ֵ��Χ
	float Pitch = FMath::Clamp(offsetZ * DeltaTime * 10.f, -70.f, 70.f);
	BirdRender->SetRelativeRotation(FRotator(Pitch, 0, 0));
}

void ABirdPawn::UpdateBirdFloat(float DeltaTime)
{
	if (CurrentState != EBirdState::EBS_Wait)//���С���Ǵ��ڵȴ�״̬�Ͳ�Ҫִ��������߼�
	{
		return;
	}
	if (!BirdFloatCurve || !BirdRender)//�������ص�������ԴΪ�գ�˵�������ʧ���ˣ��Ͳ���Ҫִ�к�����߼�
	{
		return;
	}
	//�ۼ�ʱ��
	BirdFloatTimeTick += DeltaTime;
	//����Ƿ񳬹����������ݵ�����һ��λ��
	//��ȡ���ߵ�ʱ��ֵ��Χ
	float Min, Max;
	BirdFloatCurve->GetTimeRange(Min, Max);//��ȡ���������ϵ���Сʱ���Ǻ����ʱ����
	if (BirdFloatTimeTick > Max)
	{
		BirdFloatTimeTick = Min;
	}
	//��ȡ�����ϵ�����ֵ
	float Value = BirdFloatCurve->GetFloatValue(BirdFloatTimeTick);
	//�޸��������λ��
	BirdRender->SetRelativeLocation(FVector(0, 0, Value));
	
}

// Called every frame
void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateFace(DeltaTime);
	UpdateBirdFloat(DeltaTime);
}

//��װ�û�������������������ֻ��Pawn�У�Pawn�����������У�������û�У���
// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//������������߼�
	//�ĸ�����  1���������¼�����   2��������Ӧ��ʽ   3���ص�֪ͨ����   4���ص�֪ͨ����
	PlayerInputComponent->BindAction(TEXT("DoFly"), IE_Pressed, this, &ABirdPawn::OnDoFly);
}

void ABirdPawn::ChangeBirdState(EBirdState State)
{
	switch (State)
	{
	case EBirdState::EBS_Wait:
		break;
	case EBirdState::EBS_Fly:
		//����С�������
		BirdRender->SetSimulatePhysics(true);
		break;
	case EBirdState::EBS_Drop:
		UGameplayStatics::PlaySound2D(this, DropSound);
		break;
	case EBirdState::EBS_Dead:
		BirdRender->SetSimulatePhysics(false);//�����ص�����ģ��
		UGameplayStatics::PlaySound2D(this, DeadSound);
		break;
	default:
		break;
	}
	CurrentState = State;
}
