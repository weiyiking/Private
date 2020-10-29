// Fill out your copyright notice in the Description page of Project Settings.

#include "LandActor.h"
#include <Components/ActorComponent.h>
#include "FBGameMode.h"
#include <Kismet/GameplayStatics.h>
#include <Components/StaticMeshComponent.h>
#include "BirdPawn.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ALandActor::ALandActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshRenderComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//设置堆叠碰撞关系
	MeshRenderComp->SetCollisionProfileName(TEXT("OverlapAll"));
	//绑定回调
	MeshRenderComp->OnComponentBeginOverlap.AddDynamic(this, &ALandActor::OnComponentBeginOverlapEvent);

	SetRootComponent(MeshRenderComp);
}

void ALandActor::SetSpeed(float Speed)
{
	if (MeshRenderComp)
	{
		//设置修改材质中的参数值
		//参数1：参数名称
		//参数2：修改值
		MeshRenderComp->SetScalarParameterValueOnMaterials(TEXT("Speed"), Speed);
	}
}

// Called when the game starts or when spawned
void ALandActor::BeginPlay()
{
	Super::BeginPlay();

	//获取GameMode
	if (AFBGameMode* Gm = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		Gm->SetLandActor(this);//主动将
	}
}

void ALandActor::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ABirdPawn>(OtherActor))
	{
		if (AFBGameMode* Gm = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			Gm->ChangeGameState(EGameState::EGS_GameOver);
		}
	}
}

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

