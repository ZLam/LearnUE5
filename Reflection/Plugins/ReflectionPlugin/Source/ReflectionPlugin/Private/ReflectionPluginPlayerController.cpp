// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionPluginPlayerController.h"
#include "TestActor.h"
#include "Kismet/GameplayStatics.h"

void AReflectionPluginPlayerController::Test()
{
	AActor* TmpActor = UGameplayStatics::GetActorOfClass(this, ATestActor::StaticClass());

	if (TmpActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), ((Cast<ATestActor>(TmpActor))->TestVal));
		for (TFieldIterator<FProperty> It(ATestActor::StaticClass()); It; ++It)
		{
			FProperty* Property = *It;
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *(Property->GetNameCPP()));
			if (Property->GetNameCPP() == "TestVal")
			{
				auto v = Property->ContainerPtrToValuePtr<float>(TmpActor);
				UE_LOG(LogTemp, Warning, TEXT("%f"), *v);
				*v = 678.123f;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("%f"), ((Cast<ATestActor>(TmpActor))->TestVal));

		UE_LOG(LogTemp, Warning, TEXT("====="));

		for (TFieldIterator<UFunction> It(ATestActor::StaticClass()); It; ++It)
		{
			UFunction* Func = *It;
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *(Func->GetName()));
			if (Func->GetName() == "TestUFuncOnly")
			{
				struct InParams
				{
					int32 A;
					int32 B;
					int32 Ret;
				};
				InParams inParams{ 11, 22 };
				TmpActor->ProcessEvent(Func, &inParams);
				UE_LOG(LogTemp, Warning, TEXT("%d"), inParams.Ret);
			}
		}
	}



	//int32 n = GUObjectArray.GetObjectArrayNum();
	//for (int32 i = 0; i < n; i++)
	//{
	//	FUObjectItem* item = GUObjectArray.IndexToObject(i);
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *(item->Object->GetFName().ToString()))
	//}
}
