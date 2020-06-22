// Copyright 1998-2020 MUJI tech, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "common.h"
#include "manager.generated.h"

UCLASS()
class CUSOMMADE_API Amanager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Amanager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void generate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<FVector> calc_size(float angle, const FVector &size);
	void rotate_vectorXY(FVector &target, float angle);
	void generate_staticmesh(int32 index, const FVector& location, UStaticMesh* mesh);

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStairsConfig config;

private:
	class UProceduralMeshComponent*dynamic_mesh;
	TArray<class UStaticMeshComponent*> static_mesh;
};
