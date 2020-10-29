// Fill out your copyright notice in the Description page of Project Settings.

#include "PipeActor.h"
#include <PaperSprite.h>
#include <ConstructorHelpers.h>
#include <PaperSpriteComponent.h>
#include <Kismet/GameplayStatics.h>
#include "FBGameMode.h"
#include <GameFramework/GameMode.h>
#include "BirdPawn.h"
#include "FBGameState.h"

// Sets default values
APipeActor::APipeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PipeGroupInterval = 180.f;

	//����һ�¸����
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	//�Ȱ��������ӵ��ʲ����ؽ���
	ConstructorHelpers::FObjectFinder<UPaperSprite> UpSpriteObj(TEXT("PaperSprite'/Game/FlappyBird/Textures/Pipe/pipe_down_Sprite.pipe_down_Sprite'"));
	ConstructorHelpers::FObjectFinder<UPaperSprite> DownSpriteObj(TEXT("PaperSprite'/Game/FlappyBird/Textures/Pipe/pipe_up_Sprite.pipe_up_Sprite'"));

	for (int32 i=0; i<3; i++)
	{
		USceneComponent* PipeGroup = CreateDefaultSubobject<USceneComponent>(*FString::Printf(TEXT("PipeGroup_%d"), i));
		//�����������ӵ���Ⱦ���
		UPaperSpriteComponent* UpRender = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("PipeRenderUp_%d"), i));
		UPaperSpriteComponent* DownRender = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("PipeRenderDown_%d"), i));
		//���þ���ͼƬ
		UpRender->SetSprite(UpSpriteObj.Object);
		DownRender->SetSprite(DownSpriteObj.Object);
		//���������㼶��ϵ
		UpRender->SetupAttachment(PipeGroup);
		DownRender->SetupAttachment(PipeGroup);

		//�޸Ĺܵ�����ײԤ�裬Ϊ����С���ܴ���ȥ
		UpRender->SetCollisionProfileName(TEXT("OverlapAll"));
		DownRender->SetCollisionProfileName(TEXT("OverlapAll"));

		//����ײ֪ͨ����
		UpRender->OnComponentBeginOverlap.AddDynamic(this, &APipeActor::OnComponentBeginOverlapEvent);
		DownRender->OnComponentBeginOverlap.AddDynamic(this, &APipeActor::OnComponentBeginOverlapEvent);

		UpRender->SetRelativeLocation(FVector(0, 0, 220.f));
		DownRender->SetRelativeLocation(FVector(0, 0, -220.f));
		//���ܵ������õ��������
		PipeGroup->SetupAttachment(RootComponent);
		//�����ܵ���λ��
		PipeGroup->SetRelativeLocation(FVector(230 + i * PipeGroupInterval, 0, RandPipeGroupZAxis()));
		//���ܵ�����ӵ�����������
		GroupsArray.Add(PipeGroup);
		GroupsUsed.Add(false);

	}
}

// Called when the game starts or when spawned
void APipeActor::BeginPlay()
{
	Super::BeginPlay();
	//��ȡGameMode
	if (AFBGameMode* Gm = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		Gm->SetPipeGroupActor(this);//������
	}
}

void APipeActor::UpdatePipeGroupPositon(float DeltaTime)
{
	//Num������ȡ�����е�Ԫ�ظ���
	//for (int32 i=0; i<GroupsArray.Num(); i++)
	//{
	//	GroupsArray[i]->AddRelativeLocation(FVector::ForwardVector*-1 * Speed * DeltaTime);
	//	//���ӷ�����
	//	float X = GroupsArray[i]->GetRelativeTransform().GetLocation().X;
	//	if (X < -50 && !GroupsUsed[i])
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("add score!!!!!!!!!!!!!!!!!"));
	//		GroupsUsed[i] = true;
	//	}
	//	
	//	//���ܵ��Ƿ񳬳���Ļ
	//	//��λ�ȡ�������Խڵ��λ��X��ֵ
	//	if (X < -175.f)
	//	{
	//		//��������Ļ�Ĺܵ���ŵ����е�ĩβ
	//		float X = GroupsArray[i - 1 < 0 ? GroupsArray.Num()- 1 : i - 1]->GetRelativeTransform().GetLocation().X + PipeGroupInterval;
	//		//�������ó�����Ļ�Ĺܵ�λ��
	//		GroupsArray[i]->SetRelativeLocation(FVector(X, 0, RandPipeGroupZAxis()));
	//		GroupsUsed[i] = false;
	//	}
	//}

	for (int32 i = 0; i < GroupsArray.Num(); i++)
	{
		GroupsArray[i]->AddRelativeLocation(FVector::ForwardVector*-1 * Speed * DeltaTime);
	}

	//���ӷ�����
	float X = GroupsArray[HeadIndex]->GetRelativeTransform().GetLocation().X;
	if (!GroupsUsed[HeadIndex] && X < -50)
	{
		GroupsUsed[HeadIndex] = true;
		//��λ�ȡ��GameState
		if (AFBGameState* Gs = Cast<AFBGameState>(UGameplayStatics::GetGameState(this)))
		{
			Gs->AddScore(1);
		}
	}

	//���ܵ��Ƿ񳬳���Ļ
	//��λ�ȡ�������Խڵ��λ��X��ֵ
	if (X < -175.f)
	{
		//��������Ļ�Ĺܵ���ŵ����е�ĩβ
		float X = GroupsArray[HeadIndex - 1 < 0 ? GroupsArray.Num() - 1 : HeadIndex - 1]->GetRelativeTransform().GetLocation().X + PipeGroupInterval;
		//�������ó�����Ļ�Ĺܵ�λ��
		GroupsArray[HeadIndex]->SetRelativeLocation(FVector(X, 0, RandPipeGroupZAxis()));
		GroupsUsed[HeadIndex] = false;

		if (++HeadIndex >= GroupsArray.Num())
		{
			HeadIndex = 0;
		}
	}
}

//������¹ܵ����Z��ֵ
float APipeActor::RandPipeGroupZAxis()
{
	return FMath::RandRange(-100.f, 180.f);
}

void APipeActor::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ABirdPawn>(OtherActor))//���ײ�����ӵ��ֵ��ǲ�����
	{
		if (AFBGameMode* Gm = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(this)))//��ȡGameModeָ��
		{
			Gm->ChangeGameState(EGameState::EGS_Drop);//�޸����״̬��׹��״̬
		}
	}
}

// Called every frame
void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePipeGroupPositon(DeltaTime);
}

void APipeActor::SetSpeed(float Speed)
{
	this->Speed = Speed;
}

