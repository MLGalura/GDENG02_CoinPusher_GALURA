// Fill out your copyright notice in the Description page of Project Settings.


#include "PusherMovement.h"

// Sets default values for this component's properties
UPusherMovement::UPusherMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->isMovingBack = true;
	this->ticks = 0.0f;
}


// Called when the game starts
void UPusherMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPusherMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->ticks += DeltaTime;

	if (this->ticks >= 1.5f) {
		this->ticks = 0.0f;
		this->isMovingBack = !this->isMovingBack;
	}

	if (this->isMovingBack) {
		FVector location = this->GetOwner()->GetTransform().GetLocation();
		location.Y += DeltaTime * 30.0f;
		this->GetOwner()->SetActorLocation(location);
	}

	else {
		FVector location = this->GetOwner()->GetTransform().GetLocation();
		location.Y -= DeltaTime * 30.0f;
		this->GetOwner()->SetActorLocation(location);
	}
}

