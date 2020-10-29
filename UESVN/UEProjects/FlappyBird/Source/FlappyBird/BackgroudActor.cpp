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
	//ֱ�Ӵ������
	BgRenderComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BgRenderComp"));
	//ֱ�ӽ�������Ⱦ�������Ϊ�����
	SetRootComponent(BgRenderComp);
	//����ͼƬ�ķ���
	ConstructorHelpers::FObjectFinder<UPaperSprite> BgSprite(TEXT("PaperSprite'/Game/FlappyBird/Textures/BG/bg_day_Sprite.bg_day_Sprite'"));
	//���þ���ͼƬ���������
	BgRenderComp->SetSprite(BgSprite.Object);
}

// Called when the game starts or when spawned
void ABackgroudActor::BeginPlay()
{
	Super::BeginPlay();
	RandBgSprite();
	//��ȡGameMode
	if (AFBGameMode* Gm = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		Gm->SetBgActor(this);//������
	}
}

// Called every frame
void ABackgroudActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABackgroudActor::RandBgSprite()
{
	//�����Ժ󣬸���һ�������������ò�ͬ�ı�������
	//��ȡ�����
	//FMath::RandBool();
	//��μ��ؾ����ʲ�
	//����1����������ݵ��ʲ�����ҪΪ�˼�����Ѱ�ٶȣ�
	//����2���ʲ����ƣ������������ʲ�·������ֱ�Ӻ��Ժ���Ĳ�����
	UPaperSprite* Sprite = LoadObject<UPaperSprite>(nullptr, FMath::RandBool()? TEXT("PaperSprite'/Game/FlappyBird/Textures/BG/bg_day_Sprite.bg_day_Sprite'") : TEXT("PaperSprite'/Game/FlappyBird/Textures/BG/bg_night_Sprite.bg_night_Sprite'"));//ר�����������ʲ��ࣨ�ʲ��ࣩ
	BgRenderComp->SetSprite(Sprite);
}

