// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackgroudActor.generated.h"

class UPaperSpriteComponent;

UCLASS()
class FLAPPYBIRD_API ABackgroudActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackgroudActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RandBgSprite();


protected:
	UPROPERTY()
	UPaperSpriteComponent* BgRenderComp;
};
