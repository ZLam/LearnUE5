// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestComp = CreateDefaultSubobject<UTestComponent>(TEXT("TestComp"));
	TestCompBp = CreateDefaultSubobject<UTestComponent>(TEXT("TestCompBp"));
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

int ATestActor::TestUFuncOnly(const FString& InStr)
{
	UE_LOG(LogTemp, Warning, TEXT("=== ATestActor::TestUFuncOnly === %s"), *InStr)
	return 0;
}

int ATestActor::TestUFuncBpCallable(const FString& InStr)
{
	FString tStr = TEXT("TestUFuncBpCallable call TestUFuncOnly");
	this->ProcessEvent(this->FindFunction(TEXT("TestUFuncOnly")), &tStr);

	UE_LOG(LogTemp, Warning, TEXT("=== ATestActor::TestUFuncBpCallable === %s"), *InStr)
	return 0;
}

int ATestActor::TestUFuncBpNative_Implementation(const FString& InStr)
{
	UE_LOG(LogTemp, Warning, TEXT("=== ATestActor::TestUFuncBpNative_Implementation === %s"), *InStr)
	return 0;
}

