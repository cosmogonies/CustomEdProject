#include "HelperLib.h"


TArray<FString> UHelperLib::GetAnimalTypeArray()
{
	TArray<FString> AnimalTypeArray;
	
	AnimalTypeArray.Add("Mammals");
	AnimalTypeArray.Add("Fishes");
	AnimalTypeArray.Add("Insects");
	
	return AnimalTypeArray;
}


TArray<FString> UHelperLib::GetAnimalArrayFromType(FString AnimalType)
{
		TArray<FString> Result = {};
		if( AnimalType=="Mammals")
			Result = {"Cat","Dog","Horse"};
		if( AnimalType=="Fishes")
			Result = {"Lamprey","Shark","Tuna"};
		if( AnimalType=="Insects")
			Result = {"Ant", "Bee","Fly"};
		return Result;
}



