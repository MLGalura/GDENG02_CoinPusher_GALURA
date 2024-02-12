// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinSpawner.h"

// Sets default values
ACoinSpawner::ACoinSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize values in constructor
	this->m_ActorCopy = NULL;
	this->m_SpawnLimit = 20.0f;

	this->m_Ticks = 0.0f;
	this->m_DestroyTicks = 0.0f;

	this->INTERVAL = 1.0f;
	this->DELETE_INTERVAL = 10.0f;

	//this->m_ActorCopy->SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoinSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->m_Ticks += DeltaTime;
	this->m_DestroyTicks += DeltaTime;

	if (this->m_Ticks > this->INTERVAL) {
		this->m_Ticks = 0.0f;

		//Spawns an object m_ActorCopy for each INTERVAL seconds.
		if (this->m_ActorCopy != NULL && this->m_SpawnedObjects.Num() < this->m_SpawnLimit) {
			FActorSpawnParameters spawnParams;	
			spawnParams.Template = this->m_ActorCopy;
			spawnParams.Owner = this->GetOwner();

			FVector spawnLoc = this->GetOwner()->GetActorLocation();
			FRotator spawnRot = this->GetOwner()->GetActorRotation();

			AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->m_ActorCopy->GetClass(), spawnParams);
			//change color
			//myActor->material

			myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
			myActor->SetActorHiddenInGame(false);

			myActor->SetActorLocation(spawnLoc);
			myActor->SetActorRotation(spawnRot);

			this->m_SpawnedObjects.Add(myActor);
		}

		else
			UE_LOG(LogTemp, Display, TEXT("Null Actor Detected. Initialize actor in serialized field."));
	}

	if (this->m_DestroyTicks > this->DELETE_INTERVAL) {
		this->m_DestroyTicks = 0.0f;
	}
}

