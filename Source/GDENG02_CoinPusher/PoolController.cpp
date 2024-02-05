// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolController.h"

// Sets default values for this component's properties
UPoolController::UPoolController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->coinsToSpawn = 50.0f;
	this->ticks = 0.0f;
	this->spawned = 0;
}


// Called when the game starts
void UPoolController::BeginPlay()
{
	Super::BeginPlay();
	
	this->coinPool->GetComponentByClass<UCoinPool>()->Initialize();
	//this->coinPool->GetComponentByClass<UCoinPool>()->RequestPoolableBatch(this->coinsToSpawn);
}


// Called every frame
void UPoolController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->ticks += DeltaTime;

	if (this->ticks >= 0.5f) {
		if (this->spawned < this->coinsToSpawn) {
			this->coinPool->GetComponentByClass<UCoinPool>()->RequestPoolableBatch(5);
			this->spawned += 5;
		}
	}
}

