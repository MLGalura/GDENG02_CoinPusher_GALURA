// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPoolable.h"
#include "CoinPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_COINPUSHER_API UCoinPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoinPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize();
	bool HasObjectAvailable(int requestSize);
	int GetMaxPoolSize();

	UFUNCTION(BlueprintCallable) AActorPoolable* requestPoolable();
	TArray<AActorPoolable*> RequestPoolableBatch(int size);

	UFUNCTION(BlueprintCallable) void ReleasePoolable(AActorPoolable* poolableObj);
	void ReleasePoolableBatch(TArray<AActorPoolable*> objList);
	void ReleasePoolableBatch(int count);

private:
	UPROPERTY(EditAnywhere) int MaxPoolSize;
	UPROPERTY(EditAnywhere) AActorPoolable* actorCopy;
	UPROPERTY(EditAnywhere) AActor* parent;

	TArray<AActorPoolable*> availableObjects;
	TArray<AActorPoolable*> usedObjects;
};
