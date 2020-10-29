// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeActor.generated.h"

UCLASS()
class FLAPPYBIRD_API APipeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdatePipeGroupPositon(float DeltaTime);

	float RandPipeGroupZAxis();

	UFUNCTION()
	void OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpeed(float Speed);

protected:
	UPROPERTY()
	TArray<USceneComponent*> GroupsArray;

	TArray<bool> GroupsUsed;

	//�ܵ��ļ��
	float PipeGroupInterval;

	float Speed;

	int32 HeadIndex;

};
