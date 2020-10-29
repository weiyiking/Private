// Fill out your copyright notice in the Description page of Project Settings.

#include "BackgroudActor.h"
#include <PaperSpriteComponent.h>
#include <ConstructorHelpers.h>
#include <PaperSprite.h>
#include "FBGameMode.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABackgroudActor::ABackgroudActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//直接创建组件
	BgRenderComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BgRenderComp"));
	//直接将背景渲染组件设置为根组件
	SetRootComponent(BgRenderComp);
	//加载图片的方法
	ConstructorHelpers::FObjectFinder<UPaperSprite> BgSprite(TEXT("PaperSprite'/Game/FlappyBird/Textures/BG/bg_day_Sprite.bg_day_Sprite'"));
	//设置精灵图片到精灵组件
	BgRenderComp->SetSprite(BgSprite.Object);
}

// Called when the game starts or when spawned
void ABackgroudActor::BeginPlay()
{
	Super::BeginPlay();
	RandBgSprite();
	//获取GameMode
	if (AFBGameMode* Gm = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		Gm->SetBgActor(this);//主动将
	}
}

// Called every frame
void ABackgroudActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABackgroudActor::RandBgSprite()
{
	//启动以后，根据一个随机结果，设置不同的背景精灵
	//获取随机数
	//FMath::RandBool();
	//如何加载精灵资产
	//参数1：相关联数据的资产（主要为了减少搜寻速度）
	//参数2：资产名称（如果填入虚幻资产路径可以直接忽略后面的参数）
	UPaperSprite* Sprite = LoadObject<UPaperSprite>(nullptr, FMath::RandBool()? TEXT("PaperSprite'/Game/FlappyBird/Textures/BG/bg_day_Sprite.bg_day_Sprite'") : TEXT("PaperSprite'/Game/FlappyBird/Textures/BG/bg_night_Sprite.bg_night_Sprite'"));//专门用来加载资产类（资产类）
	BgRenderComp->SetSprite(Sprite);
}

