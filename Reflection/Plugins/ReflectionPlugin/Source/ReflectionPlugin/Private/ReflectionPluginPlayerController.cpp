// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionPluginPlayerController.h"
#include "TestActor.h"

void AReflectionPluginPlayerController::Test()
{
	for (TFieldIterator<FProperty> It(ATestActor::StaticClass()); It; ++It)
	{
		FProperty* Property = *It;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(Property->GetNameCPP()));
	}

	UE_LOG(LogTemp, Warning, TEXT("======"));

	for (TFieldIterator<UFunction> It(ATestActor::StaticClass()); It; ++It)
	{
		UFunction* Func = *It;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(Func->GetName()));
	}



	//int32 n = GUObjectArray.GetObjectArrayNum();
	//for (int32 i = 0; i < n; i++)
	//{
	//	FUObjectItem* item = GUObjectArray.IndexToObject(i);
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *(item->Object->GetFName().ToString()))
	//}
}
