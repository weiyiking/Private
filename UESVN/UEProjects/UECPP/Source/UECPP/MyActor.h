// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UECPP_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;


	virtual void EndPlay(const EEndPlayReason::Type Type) override;


	UFUNCTION()
	void DoHello();
	
	UFUNCTION(BlueprintNativeEvent)
	void Fun();
	void Fun_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	int32 Fun1();
	int32 Fun1_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 Fun2();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 Fun3() const;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY()
	class UInputComponent* InputComp;
	
	//OK
	UPROPERTY(BlueprintReadOnly, Category="UECPP|A")
	int32 MyNum;
	//No
	UPROPERTY(BlueprintReadWrite, Category="UECPP")
	int32 MyNum1;

};
