// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
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


private:

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
