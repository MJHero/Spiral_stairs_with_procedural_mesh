// Copyright 1998-2020 MUJI tech, Inc. All Rights Reserved.

#include "manager.h"
#include "common.h"
#include "ProceduralMeshComponent.h"

// Sets default values
Amanager::Amanager()
{
	dynamic_mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("procmesh"));
 
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Amanager::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<FVector> Amanager::calc_size(float angle, const FVector &size)
{
	TArray<FVector> temp = { FVector(size.X,0,0),FVector(0,size.Y,0),FVector(0,0,size.Z) };

	rotate_vectorXY(temp[0],angle);
	rotate_vectorXY(temp[1],angle);
	return temp;
}

void Amanager::rotate_vectorXY(FVector &target, float angle)
{
	float temp1 = target.X*FMath::Cos(angle) - target.Y*FMath::Sin(angle);
	target.Y = target.X*FMath::Sin(angle) + target.Y*FMath::Cos(angle);
	target.X = temp1;
}

// Called every frame
void Amanager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Amanager::generate()
{

	float delta_angle = config.angle / config.stair_number;
	float delta_height = config.height / config.stair_number;
	float stair_length = config.half_size - config.inner_size;

	FVector temp_size;
	float temp_angle = 0;
	float DtoA = -PI/180;

	TArray<FColor> VC;
	TArray<FProcMeshTangent> TG;
	dynamic_mesh->ClearAllMeshSections();
	for (int32 i = 0; i <= config.stair_number; i++)
	{
		// calculate base mess
		temp_angle = i * delta_angle * DtoA;
		temp_size = { config.stair_board_width, stair_length, config.stair_board_thinkness };
		TArray<FVector> axis = calc_size(temp_angle, temp_size);
		mesh board = GenerateTools::GetABoard(axis[0], axis[1], axis[2]);

		// update transform
		temp_size = {config.stair_board_width*-0.5f, config.inner_size, delta_height*i };
		rotate_vectorXY(temp_size, temp_angle);
		for (auto & p : board.Positions)
		{
			p += temp_size;
		}

		dynamic_mesh->CreateMeshSection(i, board.Positions, board.indics, board.Normals, board.UV, VC, TG, false);

		temp_size = { 0,config.half_size,temp_size.Z };
		rotate_vectorXY(temp_size, temp_angle);
		generate_staticmesh(i, temp_size, config.mesh);
	}
	// clearn mesh component
	if (config.stair_number + 1 < static_mesh.Num())
	{
		for (int i = config.stair_number + 1; i < static_mesh.Num(); i++)
		{
			static_mesh[i]->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			static_mesh[i]->DestroyComponent();
		}
		if (config.stair_number == 0)
		{
			static_mesh[0]->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			static_mesh[0]->DestroyComponent();
			static_mesh.Empty();
		}
		else
		{
			static_mesh.SetNum(config.stair_number + 1, false);
		}
	}
}

void Amanager::generate_staticmesh(int32 index, const FVector& location, UStaticMesh* mesh)
{
	if (!mesh || static_mesh.Num() < index)return;
	if (static_mesh.Num() == index)
	{
		UStaticMeshComponent* temp = NewObject<UStaticMeshComponent>(this);
		temp->RegisterComponent();
		temp->SetStaticMesh(mesh);
		temp->AttachToComponent(dynamic_mesh,FAttachmentTransformRules::KeepRelativeTransform);
		static_mesh.Add(temp);
	}
	else if(static_mesh[index]->GetStaticMesh()!=mesh)
	{
		static_mesh[index]->SetStaticMesh(mesh);
	}
	static_mesh[index]->SetRelativeLocation(location);
}

