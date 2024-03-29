// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "ActorPoolable.generated.h"

UCLASS()
class GDENG02_COINPUSHER_API AActorPoolable : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorPoolable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnInitialize();					//Initializes the property of the object
	virtual void OnRelease();						//Throws this event when this object has been released back into the pool
	virtual void OnActivate();						//Throws this event when this object has been activated from the pool

	void SetIndex(int i);
	int GetIndex();

private:
	int m_Index;

};
