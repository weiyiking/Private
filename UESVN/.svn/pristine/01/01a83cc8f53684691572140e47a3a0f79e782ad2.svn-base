// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FBGameMode.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8
{
	EGS_Logo,
	EGS_Menu,
	EGS_Gaming,
	EGS_Drop,
	EGS_GameOver,
};



class ABirdPawn;
class APipeActor;
class ALandActor;
class ABackgroudActor;

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AFBGameMode : public AGameModeBase
{
	GENERATED_BODY()
		AFBGameMode();


protected:


	virtual void BeginPlay() override;
	
	UFUNCTION(Exec)
	void Fun();

	void ChangeBirdDrop();

	void ChangeGameOver();

public:

	void SetPipeGroupActor(APipeActor* PipeGroupActor) { this->PipeGroupActor = PipeGroupActor; }
	void SetLandActor(ALandActor* LandActor) { this->LandActor = LandActor; }
	void SetBgActor(ABackgroudActor* BgActor) { this->BgActor = BgActor; }


	void ChangeGameState(EGameState State);

protected:
	UPROPERTY()
	ABirdPawn* BirdPawn;
	UPROPERTY()
	APipeActor* PipeGroupActor;
	UPROPERTY()
	ALandActor* LandActor;
	UPROPERTY()
	ABackgroudActor* BgActor;

	EGameState CurrentState;
	
};




