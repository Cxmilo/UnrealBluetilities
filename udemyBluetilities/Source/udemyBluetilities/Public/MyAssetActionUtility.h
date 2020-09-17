// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "Engine/Blueprint.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialFunctionInterface.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundWave.h"
#include "Engine/Texture.h"
#include "Engine/Texture2D.h"
#include "Blueprint/UserWidget.h"
#include "Animation/MorphTarget.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyAssetActionUtility.generated.h"

/**
 * 
 */
UCLASS()
class UDEMYBLUETILITIES_API UMyAssetActionUtility : public UAssetActionUtility
{
	GENERATED_BODY()
	
public:

	/**
	 * Rename the selected assets
	 *@param SearchPattern - the patter to search for
	 *@param ReplacePattern - the pattern to replace with
	 *@param SearchCase - should the case be ignored?
	 */

	UFUNCTION(CallInEditor)
	void RenameSelectedAssets(const FString SearchPattern, const FString ReplacePattern,const ESearchCase::Type SearchCase);

	/**
	*Check if a texture2d is a power of two resolution	
	*/
	
	UFUNCTION(CallInEditor)
	void CheckPowerofTwo_FromCode();

	/**
	*Check if the selected assets has the correct prefixes
	*/

	UFUNCTION(CallInEditor)
	void AddPrefixes_FromCode();



private:

	const TMap<UClass*, FString> PrefixMap = {
		{UBlueprint::StaticClass(),TEXT("BP_")},
		{UStaticMesh::StaticClass(), TEXT("SM_")},
		{UMaterial::StaticClass(), TEXT("M_")},
		{UMaterialInstance::StaticClass(), TEXT("MI_")},
		{UMaterialFunctionInterface::StaticClass(), TEXT("MF_")},
		{UParticleSystem::StaticClass(), TEXT("PS_")},
		{USoundCue::StaticClass(), TEXT("SC_")},
		{USoundWave::StaticClass(), TEXT("S_")},
		{UTexture::StaticClass(), TEXT("T_")},
		{UTexture2D::StaticClass(), TEXT("T_")},
		{UUserWidget::StaticClass(), TEXT("UW_")},
		{UMorphTarget::StaticClass(), TEXT("MT_")},
		{USkeletalMeshComponent::StaticClass(), TEXT("MT_")}

	};


	UFUNCTION()
	bool IsPowerOfTwo(int32 NumberToCheck);

	/**
	 * Prints a message to the screen
	 @param Message - the message to print
	 @param Color - the color to use for the Message
	 */

	UFUNCTION()
	void PrintToScreen(FString Message, FColor Color);

	/**
	 * Give Feedback to the user
	 *@param Method - the Method that was used
	 *@param Counter - how many objects were affected
	 */

	UFUNCTION()
	void GiveFeedback(FString Method, uint32 Counter);

};
