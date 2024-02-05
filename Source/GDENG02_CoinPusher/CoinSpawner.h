// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinSpawner.generated.h"

UCLASS()
class GDENG02_COINPUSHER_API ACoinSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere) AActor* m_ActorCopy;
	UPROPERTY(EditAnywhere) int m_SpawnLimit;

	float m_Ticks;
	float m_DestroyTicks;

	float INTERVAL;
	float DELETE_INTERVAL;

	TArray<AActor*> m_SpawnedObjects;

	void DeleteAll();
};
