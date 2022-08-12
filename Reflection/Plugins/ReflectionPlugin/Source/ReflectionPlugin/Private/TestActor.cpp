// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestComp = CreateDefaultSubobject<UTestComponent>(TEXT("TestComp"));
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ATestActor::TestUFuncOnly(const int32& A, const int32& B)
{
	UE_LOG(LogTemp, Warning, TEXT("=== ATestActor::TestUFuncOnly ==="))
	return A + B;
}

int32 ATestActor::TestUFuncBpCallable(const FString& InStr)
{
	UE_LOG(LogTemp, Warning, TEXT("=== ATestActor::TestUFuncBpCallable === %s"), *InStr)
	return 0;
}

int32 ATestActor::TestUFuncBpNative_Implementation(const FString& InStr)
{
	UE_LOG(LogTemp, Warning, TEXT("=== ATestActor::TestUFuncBpNative_Implementation === %s"), *InStr)
	return 0;
}

