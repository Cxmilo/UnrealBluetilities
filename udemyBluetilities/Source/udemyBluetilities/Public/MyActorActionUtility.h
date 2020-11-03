// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorActionUtility.h"
#include "MyActorActionUtility.generated.h"

namespace ForwardDeclare { class UMaterialInterface; }

/**
 * 
 */
UCLASS()
class UDEMYBLUETILITIES_API UMyActorActionUtility : public UActorActionUtility
{
	GENERATED_BODY()

public:

	UFUNCTION(CallInEditor)
	void ChangeMaterial_FromCode(UMaterialInterface* NewMaterial);

	
};
