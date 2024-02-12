// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinPool.h"

// Sets default values for this component's properties
UCoinPool::UCoinPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->MaxPoolSize = 20.0f;
	this->actorCopy = NULL;
	this->parent = NULL;
}


// Called when the game starts
void UCoinPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCoinPool::BeginDestroy() {
	Super::BeginDestroy();

	for (int i = 0; i < this->availableObjects.Num(); i++)
		this->availableObjects[i]->Destroy();

	for (int i = 0; i < this->usedObjects.Num(); i++)
		this->usedObjects[i]->Destroy();

	this->availableObjects.Empty();
	this->usedObjects.Empty(); 
}

// Called every frame
void UCoinPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCoinPool::Initialize() {
	if (this->actorCopy == NULL) {
		UE_LOG(LogTemp, Display, TEXT("Actor is null. Object pool uninitialized"));
		return;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Template = this->actorCopy;
	spawnParams.Owner = this->GetOwner();

	const FTransform transform = this->actorCopy->GetActorTransform();

	for (int i = 0; i < this->MaxPoolSize - 1; i++) {
		AActorPoolable* poolableObject = this->GetWorld()->SpawnActor<AActorPoolable>(this->actorCopy->GetClass(), spawnParams);
		poolableObject->SetIndex(i);
		poolableObject->OnInitialize();
		this->availableObjects.Push(poolableObject);
	}
}

bool UCoinPool::HasObjectAvailable(int requestSize) {
	UE_LOG(LogTemp, Warning, TEXT("BRO YOU HAVE %i LEFT, AND YOU'RE ASKING FOR %i"), this->availableObjects.Num(), requestSize);


	return this->availableObjects.Num() > requestSize;
}

int UCoinPool::GetMaxPoolSize() {
	return this->MaxPoolSize;
}

AActorPoolable* UCoinPool::requestPoolable() {
	if (this->HasObjectAvailable(1)) {
		AActorPoolable* object = this->availableObjects.Pop();
		object->SetIndex(this->usedObjects.Num());

		this->usedObjects.Push(object);

		object->OnActivate();
		object->SetActorTransform(this->GetOwner()->GetActorTransform());

		FVector location = this->GetOwner()->GetTransform().GetLocation();
		location.X += std::rand() % 201 - 100;

		UMaterialInstanceDynamic* newMaterial = (UMaterialInstanceDynamic*)object->GetMaterial(0);

		FLinearColor newColor;
		newColor.MakeRandomColor();

		material->SetVectorParameterValue(FName(TEXT("BaseColor")), newcolor);

		object->SetActorLocation(location);

		return object;
	}

	else {
		UE_LOG(LogTemp, Warning, TEXT("No Poolable Objects Available"));
		return NULL; 
	}
}

TArray<AActorPoolable*> UCoinPool::RequestPoolableBatch(int size) { 
	TArray<AActorPoolable*> objects;

	for (int i = 0; i < size && this->availableObjects.Num() > 0; i++)
		objects.Push(this->requestPoolable());

	return objects;
}

void UCoinPool::ReleasePoolable(AActorPoolable* poolableObj) {
	poolableObj->OnRelease();
	this->usedObjects.Remove(poolableObj);
	this->availableObjects.Push(poolableObj);
}

void UCoinPool::ReleasePoolableBatch(TArray<AActorPoolable*> objList) {
	for (int i = 0; i < objList.Num(); i++)
		this->ReleasePoolable(objList[i]);
}

void UCoinPool::ReleasePoolableBatch(int count) {

}