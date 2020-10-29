// Fill out your copyright notice in the Description page of Project Settings.

#include "FBGameMode.h"
#include "BirdPawn.h"
#include "PipeActor.h"
#include <Kismet/GameplayStatics.h>
#include "LandActor.h"
#include "BackgroudActor.h"
#include "FBGameState.h"
#include "FBHUD.h"

AFBGameMode::AFBGameMode()
{
	//������Ϸ��Ĭ�������
	DefaultPawnClass = ABirdPawn::StaticClass();
	//����һ����Ϸ��״̬��
	GameStateClass = AFBGameState::StaticClass();
	//������Ϸ��HUD��
	HUDClass = AFBHUD::StaticClass();
}

void AFBGameMode::BeginPlay()
{
	Super::BeginPlay();

	////A ����  B��
	//TArray<AActor*> Array;
	////ȥ����һ�³����еı���Actor
	////����1������������   ��Ҫ��;�Ǹ��ߺ��������ڵ��������ĸ�������һ����֤���ݣ���Ҫ��������ѯ��Χ�ģ�
	////����2����Ҫ��Ѱ�Ķ��������
	////����3����Ѱ��������б�����
	//UGameplayStatics::GetAllActorsOfClass(this, APipeActor::StaticClass(), Array);

	//for (int32 i=0; i<Array.Num(); i++)
	//{
	//	//��ָ̬��ת��
	//	//����
	//	APipeActor* Pipe = Cast<APipeActor>(Array[i]);//Cast��һ����ȫָ��ת���������������Ĳ���ָ����Ŀ��ģ�壨Ҳ���Ǽ�������������ͣ����߱�����ת��ʱ�����ṩת�����ָ�룬���򷵻ؿ�
	//	if (Pipe)
	//	{
	//		PipeGroupActor = Pipe;
	//	}
	//	else
	//	{

	//	}
	//}
	////��������
	//Array.Reset();

	//UGameplayStatics::GetAllActorsOfClass(this, ALandActor::StaticClass(), Array);

	//NULL;
	//0;
	//nullptr;//C++11������ �������ָ�����Ϳ�


	BirdPawn = Cast<ABirdPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AFBGameMode::Fun()
{
	if (PipeGroupActor)
	{
		PipeGroupActor->SetSpeed(60);
	}
	if (LandActor)
	{
		LandActor->SetSpeed(0.1f);
	}
	if (BgActor)
	{
		BgActor->RandBgSprite();
	}
	if (BirdPawn)
	{
		BirdPawn->ChangeBirdState(EBirdState::EBS_Fly);
	}
}

void AFBGameMode::ChangeBirdDrop()
{
	if (PipeGroupActor)
	{
		PipeGroupActor->SetSpeed(0);
	}
	if (LandActor)
	{
		LandActor->SetSpeed(0.f);
	}
	if (BirdPawn)
	{
		BirdPawn->ChangeBirdState(EBirdState::EBS_Drop);
	}
}

void AFBGameMode::ChangeGameOver()
{
	if (PipeGroupActor)
	{
		PipeGroupActor->SetSpeed(0);
	}
	if (LandActor)
	{
		LandActor->SetSpeed(0.f);
	}
	if (BirdPawn)
	{
		BirdPawn->ChangeBirdState(EBirdState::EBS_Dead);
	}

}

void AFBGameMode::ChangeGameState(EGameState State)
{
	if (State == CurrentState)//�������Ҫ���õ�״̬�����ǵ�ǰ״̬��������ִ��������߼�
	{
		return;
	}

	switch (State)
	{
	case EGameState::EGS_Logo:
		break;
	case EGameState::EGS_Menu:
		break;
	case EGameState::EGS_Gaming:
		break;
	case EGameState::EGS_Drop:
		ChangeBirdDrop();
		break;
	case EGameState::EGS_GameOver:
		ChangeGameOver();
		break;
	default:
		break;
	}
	//���ⲿ����״̬�������ø���ǰ״̬����
	CurrentState = State;

}