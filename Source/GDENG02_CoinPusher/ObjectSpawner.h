// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_COINPUSHER_API UObjectSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
