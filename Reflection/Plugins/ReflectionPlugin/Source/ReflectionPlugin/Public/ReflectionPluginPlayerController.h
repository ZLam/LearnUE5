// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ReflectionPluginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class REFLECTIONPLUGIN_API AReflectionPluginPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Test();
};
