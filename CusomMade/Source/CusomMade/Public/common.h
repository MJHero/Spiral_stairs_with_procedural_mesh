// Copyright 1998-2020 MUJI tech, Inc. All Rights Reserved.
#pragma once

#include "common.generated.h"

struct mesh
{
	mesh();

	TArray<FVector> Positions;
	TArray<int32> indics;
	TArray<FVector> Normals;
	TArray<FVector2D> UV;
};

USTRUCT(BlueprintType)
struct CUSOMMADE_API FStairsConfig
{
	GENERATED_USTRUCT_BODY()

	FStairsConfig();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "stairs paramter")
	FTransform transform;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = 0, ClampMin = 0, UIMax = 1000, ClampMax = 1000), Category = "stairs paramter")
		float height;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = 0, ClampMin = 0, UIMax = 720, ClampMax = 720), Category = "stairs paramter")
		float angle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = 0, ClampMin = 0, UIMax = 1000, ClampMax = 1000), Category = "stairs paramter")
		float stair_board_width;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = 0, ClampMin = 0, UIMax = 50, ClampMax = 50), Category = "stairs paramter")
		float stair_board_thinkness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = 0, ClampMin = 0, UIMax = 500, ClampMax = 500), Category = "stairs paramter")
		float half_size;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = 0, ClampMin = 0, UIMax = 400, ClampMax = 400), Category = "stairs paramter")
		float inner_size;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = 0, ClampMin = 0, UIMax = 100, ClampMax = 100), Category = "stairs paramter")
		int stair_number;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "stairs paramter")
	class UStaticMesh* mesh;
};

struct GenerateTools 
{
	GenerateTools() {};

	static mesh GetABoard(const FVector &a, const FVector &b, const FVector &c);
private:
	static void CalculateFaceIndicsNormalUV(const FVector& a, const FVector& b, const FVector& c, TArray<FVector>& Positions, TArray<int32>& indics, TArray<FVector>&Normals, TArray<FVector2D> &UV);
};

