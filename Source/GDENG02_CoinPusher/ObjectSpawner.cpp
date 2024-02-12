// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"

// Sets default values for this component's properties
UObjectSpawner::UObjectSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Initialize values in constructor
	this->m_ActorCopy = NULL;
	this->m_SpawnLimit = 20.0f;

	this->m_Ticks = 0.0f;
	this->m_DestroyTicks = 0.0f;

	this->INTERVAL = 1.0f;
	this->DELETE_INTERVAL = 10.0f;
}


// Called when the game starts
void UObjectSpawner::BeginPlay()
{
	Super::BeginPlay();

	this->m_ActorCopy->SetActorHiddenInGame(true);
}


// Called every frame
void UObjectSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

