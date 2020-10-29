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

	//构建一下根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	//先把两个管子的资产加载进来
	ConstructorHelpers::FObjectFinder<UPaperSprite> UpSpriteObj(TEXT("PaperSprite'/Game/FlappyBird/Textures/Pipe/pipe_down_Sprite.pipe_down_Sprite'"));
	ConstructorHelpers::FObjectFinder<UPaperSprite> DownSpriteObj(TEXT("PaperSprite'/Game/FlappyBird/Textures/Pipe/pipe_up_Sprite.pipe_up_Sprite'"));

	for (int32 i=0; i<3; i++)
	{
		USceneComponent* PipeGroup = CreateDefaultSubobject<USceneComponent>(*FString::Printf(TEXT("PipeGroup_%d"), i));
		//创建两根管子的渲染组件
		UPaperSpriteComponent* UpRender = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("PipeRenderUp_%d"), i));
		UPaperSpriteComponent* DownRender = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("PipeRenderDown_%d"), i));
		//设置精灵图片
		UpRender->SetSprite(UpSpriteObj.Object);
		DownRender->SetSprite(DownSpriteObj.Object);
		//设置依附层级关系
		UpRender->SetupAttachment(PipeGroup);
		DownRender->SetupAttachment(PipeGroup);

		//修改管道的碰撞预设，为了让小鸟能传过去
		UpRender->SetCollisionProfileName(TEXT("OverlapAll"));
		DownRender->SetCollisionProfileName(TEXT("OverlapAll"));

		//绑定碰撞通知代理
		UpRender->OnComponentBeginOverlap.AddDynamic(this, &APipeActor::OnComponentBeginOverlapEvent);
		DownRender->OnComponentBeginOverlap.AddDynamic(this, &APipeActor::OnComponentBeginOverlapEvent);

		UpRender->SetRelativeLocation(FVector(0, 0, 220.f));
		DownRender->SetRelativeLocation(FVector(0, 0, -220.f));
		//将管道组设置到根组件上
		PipeGroup->SetupAttachment(RootComponent);
		//调整管道组位置
		PipeGroup->SetRelativeLocation(FVector(230 + i * PipeGroupInterval, 0, RandPipeGroupZAxis()));
		//将管道组件加到容器数组中
		GroupsArray.Add(PipeGroup);
		GroupsUsed.Add(false);

	}
}

// Called when the game starts or when spawned
void APipeActor::BeginPlay()
{
	Super::BeginPlay();
	//获取GameMode
	if (AFBGameMode* Gm = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		Gm->SetPipeGroupActor(this);//主动将
	}
}

void APipeActor::UpdatePipeGroupPositon(float DeltaTime)
{
	//Num函数获取容器中的元素个数
	//for (int32 i=0; i<GroupsArray.Num(); i++)
	//{
	//	GroupsArray[i]->AddRelativeLocation(FVector::ForwardVector*-1 * Speed * DeltaTime);
	//	//检查加分问题
	//	float X = GroupsArray[i]->GetRelativeTransform().GetLocation().X;
	//	if (X < -50 && !GroupsUsed[i])
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("add score!!!!!!!!!!!!!!!!!"));
	//		GroupsUsed[i] = true;
	//	}
	//	
	//	//检查管道是否超出屏幕
	//	//如何获取组件的相对节点的位置X轴值
	//	if (X < -175.f)
	//	{
	//		//将超出屏幕的管道组放到队列的末尾
	//		float X = GroupsArray[i - 1 < 0 ? GroupsArray.Num()- 1 : i - 1]->GetRelativeTransform().GetLocation().X + PipeGroupInterval;
	//		//重新设置超出屏幕的管道位置
	//		GroupsArray[i]->SetRelativeLocation(FVector(X, 0, RandPipeGroupZAxis()));
	//		GroupsUsed[i] = false;
	//	}
	//}

	for (int32 i = 0; i < GroupsArray.Num(); i++)
	{
		GroupsArray[i]->AddRelativeLocation(FVector::ForwardVector*-1 * Speed * DeltaTime);
	}

	//检查加分问题
	float X = GroupsArray[HeadIndex]->GetRelativeTransform().GetLocation().X;
	if (!GroupsUsed[HeadIndex] && X < -50)
	{
		GroupsUsed[HeadIndex] = true;
		//如何获取到GameState
		if (AFBGameState* Gs = Cast<AFBGameState>(UGameplayStatics::GetGameState(this)))
		{
			Gs->AddScore(1);
		}
	}

	//检查管道是否超出屏幕
	//如何获取组件的相对节点的位置X轴值
	if (X < -175.f)
	{
		//将超出屏幕的管道组放到队列的末尾
		float X = GroupsArray[HeadIndex - 1 < 0 ? GroupsArray.Num() - 1 : HeadIndex - 1]->GetRelativeTransform().GetLocation().X + PipeGroupInterval;
		//重新设置超出屏幕的管道位置
		GroupsArray[HeadIndex]->SetRelativeLocation(FVector(X, 0, RandPipeGroupZAxis()));
		GroupsUsed[HeadIndex] = false;

		if (++HeadIndex >= GroupsArray.Num())
		{
			HeadIndex = 0;
		}
	}
}

//随机以下管道组的Z轴值
float APipeActor::RandPipeGroupZAxis()
{
	return FMath::RandRange(-100.f, 180.f);
}

void APipeActor::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ABirdPawn>(OtherActor))//检查撞倒管子的兄弟是不是鸟
	{
		if (AFBGameMode* Gm = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(this)))//获取GameMode指针
		{
			Gm->ChangeGameState(EGameState::EGS_Drop);//修改鸟的状态到坠落状态
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

