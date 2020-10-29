// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "UECPPGameModeBase.h"
#include <Components/InputComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	//APlayerController
	////动态的创建一个U类的组件
	//InputComp = NewObject<UInputComponent>(this);
	////这个动作是让你的组件注册下他的逻辑
	//InputComp->RegisterComponent();
	//
	//InputComp->BindAction(TEXT("Hello"), IE_Pressed, this, &AMyActor::DoHello);
	//
	//APlayerController*Pc = UGameplayStatics::GetPlayerController(this, 0);

	//创建一个回调动作
	//参数1：动作ID
	//参数2：动作UID（唯一）
	//参数3：回调的函数名字（函数必须是没有返回类型，没有参数并且添加UFUNCITON标记的）
	//参数4:通知的对象
	/*FLatentActionInfo Info(60, 10, TEXT("DoHello"), this);

	UKismetSystemLibrary::Delay(this, 1, Info);

	UE_LOG(LogTemp, Log, TEXT("SSSAAAA"));*/

	//Fun();

	Fun();

}

void AMyActor::Destroyed()
{
	Super::Destroyed();

	//打个日志
	UE_LOG(LogTemp, Log, TEXT("Delete"));
}

void AMyActor::EndPlay(const EEndPlayReason::Type Type)
{
	Super::EndPlay(Type);

	switch (Type)
	{
	case EEndPlayReason::Destroyed:
		UE_LOG(ZLog, Log, TEXT("中文"));
		break;
	case EEndPlayReason::EndPlayInEditor:

		break;
	case EEndPlayReason::LevelTransition:

		break;
	default:
		break;
	}


}

void AMyActor::DoHello()
{
	UE_LOG(LogTemp, Log, TEXT("Hello"));
}



void AMyActor::Fun_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("我在C++里"));
}

int32 AMyActor::Fun1_Implementation()
{
	return 0;
}

int32 AMyActor::Fun2()
{
	return 0;
}

int32 AMyActor::Fun3() const
{
	return 0;
}


// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

