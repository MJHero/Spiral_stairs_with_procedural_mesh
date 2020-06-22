// Copyright 1998-2020 MUJI tech, Inc. All Rights Reserved.
#include "common.h"

FStairsConfig::FStairsConfig()
	:transform(), height(200), angle(360), stair_board_width(30), stair_board_thinkness(8), half_size(80), inner_size(10), stair_number(20) { }

mesh::mesh() : Positions(), indics(), Normals(), UV() { }

/*...........................
.........c ------ b+c........
......../|        /|.........
......./ |       / |.........
.....a+c ---- a+b+c|.........
......|  O -----|- b.........
......| /       | /..........
......|/        |/...........
......a ------ a+b...........
.............................*/
mesh GenerateTools::GetABoard(const FVector &a, const FVector &b, const FVector &c)
{

	FVector O(0);

	FVector a_ = a, b_ = b;
	if (FVector::DotProduct(c, FVector::CrossProduct(a, b)) < 0)
	{
		a_ = b;
		b_ = a;
	}
	
	mesh temp;
	CalculateFaceIndicsNormalUV(b_ + c,	c,	a_ + c,	temp.Positions, temp.indics, temp.Normals, temp.UV);// top
	CalculateFaceIndicsNormalUV(a_,		O,	b_,		temp.Positions, temp.indics, temp.Normals, temp.UV);// button
	CalculateFaceIndicsNormalUV(c,		O,	a_,		temp.Positions, temp.indics, temp.Normals, temp.UV);// left
	CalculateFaceIndicsNormalUV(a_ +b_, b_,	b_ + c,	temp.Positions, temp.indics, temp.Normals, temp.UV);// right
	CalculateFaceIndicsNormalUV(a_ + c,	a_,	a_ + b_,temp.Positions, temp.indics, temp.Normals, temp.UV);// front
	CalculateFaceIndicsNormalUV(b_,		O,	c,		temp.Positions, temp.indics, temp.Normals, temp.UV);// back
	return temp;
}

/*......................
.... a ------- a+c .....
.... |          | ......
.... |          | ......
.... |          | ......
.... b -------- c ......
......................*/
void GenerateTools::CalculateFaceIndicsNormalUV(
	const FVector& a,
	const FVector& b,
	const FVector& c,
	TArray<FVector>& Positions,
	TArray<int32>& indics,
	TArray<FVector>&Normals,
	TArray<FVector2D> &UV)
{
	FVector ac = a + c - b;
	indics.Append({ Positions.Num() + 0,Positions.Num() + 1,Positions.Num() + 2,
		Positions.Num() + 3,Positions.Num() + 4,Positions.Num() + 5 });
	Positions.Append({ b,a,ac,b,ac,c });

	FVector A = a - b;
	FVector C = c - b;
	{
		FVector normal = FVector::CrossProduct(C, A).GetSafeNormal();
		Normals.Emplace(normal);
		Normals.Emplace(normal);
		Normals.Emplace(normal);
		Normals.Emplace(normal);
		Normals.Emplace(normal);
		Normals.Emplace(normal);
	}
	
	FVector u_axis = C.GetSafeNormal();
	FVector v_axis = FVector::CrossProduct(FVector::CrossProduct(C,A),C).GetSafeNormal();

	FVector2D uv_a(FVector::DotProduct(A, u_axis)/100.f, FVector::DotProduct(A, v_axis)/100.f);
	FVector2D uv_c(FVector::DotProduct(C, u_axis)/100.f, FVector::DotProduct(C, v_axis)/100.f);

	float angle = 0;
	float temp = 0;
	temp = uv_a.X*FMath::Cos(angle) - uv_a.Y*FMath::Sin(angle);
	uv_a.Y = uv_a.X*FMath::Sin(angle) + uv_a.Y*FMath::Cos(angle);
	uv_a.X = temp;
	temp = uv_c.X*FMath::Cos(angle) - uv_c.Y*FMath::Sin(angle);
	uv_c.Y = uv_c.X*FMath::Sin(angle) + uv_c.Y*FMath::Cos(angle);
	uv_c.X = temp;

	UV.Emplace(0, 0);
	UV.Emplace(uv_a);
	UV.Emplace(uv_a + uv_c);
	UV.Emplace(0, 0);
	UV.Emplace(uv_a + uv_c);
	UV.Emplace(uv_c);
}

