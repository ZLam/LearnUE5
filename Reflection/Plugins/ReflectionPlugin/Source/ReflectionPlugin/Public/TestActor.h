// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestComponent.h"
#include "TestActor.generated.h"

UCLASS()
class REFLECTIONPLUGIN_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	float TestVal = 123.666f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTestComponent* TestComp;

	UFUNCTION()
	int32 TestUFuncOnly(const int32& A, const int32& B);

	UFUNCTION(BlueprintCallable)
	int32 TestUFuncBpCallable(const FString& InStr);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	int32 TestUFuncBpImpl(const FString& InStr);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 TestUFuncBpNative(const FString& InStr);
};
