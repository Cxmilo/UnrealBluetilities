// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetActionUtility.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "Engine/Texture.h"
#include "Math/Color.h"



#pragma  region Rename_Assets
void UMyAssetActionUtility::RenameSelectedAssets(const FString SearchPattern, const FString ReplacePattern, const ESearchCase::Type SearchCase)
{
	//check if something needs to be done
	if (SearchPattern.IsEmpty() || SearchPattern.Equals(ReplacePattern, SearchCase))
	{
		UE_LOG(LogTemp, Error, TEXT("Please Check your Patterns!!"));
	}

	// Get the selected objects
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			FString AssetName = SelectedObject->GetName();
			if (AssetName.Contains(SearchPattern, SearchCase))
			{
				FString NewName = AssetName.Replace(*SearchPattern, *ReplacePattern, SearchCase);
				UEditorUtilityLibrary::RenameAsset(SelectedObject, NewName);
				++Counter;
			}
		}

	}
	GiveFeedback(TEXT("Renamed"), Counter);

}



#pragma endregion

#pragma region Check_POT_TWO
void UMyAssetActionUtility::CheckPowerofTwo_FromCode()
{
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			UTexture* Texture = dynamic_cast<UTexture*>(SelectedObject);

			if (ensure(Texture))
			{
				int32 Width = static_cast<int32>(Texture->GetSurfaceWidth());
				int32 Height = static_cast<int32>(Texture->GetSurfaceHeight());

				if (!IsPowerOfTwo(Width) || !IsPowerOfTwo(Height))
				{
					PrintToScreen(SelectedObject->GetPathName() + " is not a power of 2 texture",FColor::Red);
				}
				else
				{
					++Counter;
				}

			}
			else
			{
				PrintToScreen(SelectedObject->GetPathName() + "is not a texture", FColor::Red);
			}
		}
	}

	GiveFeedback("power of two", Counter);
}

#pragma endregion

#pragma region AddPrefixes

void UMyAssetActionUtility::AddPrefixes_FromCode()
{
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			const FString* Prefix = PrefixMap.Find(SelectedObject->GetClass());

			if (ensure(Prefix) && !Prefix->Equals(""))
			{
				FString Oldname = SelectedObject->GetName();
				
				if (!Oldname.StartsWith(*Prefix))
				{
					FString NewName = *Prefix + Oldname;
					UEditorUtilityLibrary::RenameAsset(SelectedObject, NewName);
					++Counter;
				}
			}
			else
			{
				PrintToScreen("Couldn't find prefix for class " + SelectedObject->GetClass()->GetName(), FColor::Red);
			}
		}
	}

	GiveFeedback("Added prefix to", Counter);
}

#pragma endregion

#pragma  region ProjectOrganizer

void UMyAssetActionUtility::CleanupFolder_From_Code(FString ParentFolder /*= FString("/Game")*/)
{
	//Check if Parent folder is in the content-folder
	if (!ParentFolder.StartsWith(TEXT("/Game")))
	{
		ParentFolder = FPaths::Combine(TEXT("/Game"),ParentFolder);
	}

	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			FString NewPath = FPaths::Combine(ParentFolder,SelectedObject->GetClass()->GetName(),SelectedObject->GetName());

			if (UEditorAssetLibrary::RenameLoadedAsset(SelectedObject, NewPath))
			{
				++Counter;
			}
			else
			{
				PrintToScreen("Couldn't move " + SelectedObject->GetPathName(),FColor::Red);
			}

		}

		GiveFeedback("Moved", Counter);
	}

}

#pragma endregion

#pragma region Duplicate_assets

void UMyAssetActionUtility::DuplicateAsset_FromCode(uint32 NumberOfDuplicates /*=1*/, bool bSave /*= true*/)
{
	TArray<FAssetData> AssetDataArray = UEditorUtilityLibrary::GetSelectedAssetData();

	uint32 Counter = 0;

	for (FAssetData AssetData : AssetDataArray )
	{
		for (uint32 i = 0; i < NumberOfDuplicates; i++)
		{
			FString NewFileName = AssetData.AssetName.ToString().AppendChar('_').Append(FString::FromInt(i));
			FString NewPath = FPaths::Combine(AssetData.PackagePath.ToString(), NewFileName);

			if (ensure(UEditorAssetLibrary::DuplicateAsset(AssetData.ObjectPath.ToString(),NewPath)))
			{
				++Counter;
				if (bSave)
				{
					UEditorAssetLibrary::SaveAsset(NewPath, false);
				}
			}
		}
	}
	GiveFeedback("Duplicate Assets", Counter);
}

#pragma endregion

#pragma region Remove_Unused_Assets

void UMyAssetActionUtility::RemoveUnusedAssets_FromCode(bool bDeleteImmediately)
{
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	TArray<UObject*> UnusedObjects = TArray<UObject*>();

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			if (UEditorAssetLibrary::FindPackageReferencersForAsset(SelectedObject->GetPathName(), true).Num() <= 0)			{
				UnusedObjects.Add(SelectedObject);
			}
		}
	}

	uint32 Counter = 0;

	for (UObject* SelectedObject : UnusedObjects )
	{
		if (bDeleteImmediately)
		{
			if (UEditorAssetLibrary::DeleteLoadedAsset(SelectedObject))
			{
				++Counter;
			}
			else
			{
				PrintToScreen("Error deleting " + SelectedObject->GetPathName(), FColor::Red);
			}
		}
		else
		{
			FString NewPath = FPaths::Combine(TEXT("/Game"), TEXT("Bin"), SelectedObject->GetName());
			if (UEditorAssetLibrary::RenameLoadedAsset(SelectedObject, NewPath))
			{
				++Counter;
			}
			else
			{
				PrintToScreen("Error moving " + SelectedObject->GetPathName(), FColor::Red);
			}
		}
	}

	GiveFeedback(bDeleteImmediately ? "Deleted" : "Moved to bin:", Counter);

}

#pragma endregion

#pragma region Helper

bool UMyAssetActionUtility::IsPowerOfTwo(int32 NumberToCheck)
{
	if (NumberToCheck == 0)
	{
		return false;
	}

	return (NumberToCheck & (NumberToCheck - 1)) == 0;
}

void UMyAssetActionUtility::PrintToScreen(FString Message, FColor Color)
{
	if (ensure(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, Color, Message);
	}
}

void UMyAssetActionUtility::GiveFeedback(FString Method, uint32 Counter)
{
	FString Message = FString("No Matching files found");
	FColor Color = Counter > 0 ? FColor::Green : FColor::Red;
	if (Counter > 0)
	{
		Message = Method.AppendChar(' ');
		Message.AppendInt(Counter);
		Message.Append(Counter == 1 ? TEXT(" file") : TEXT(" files"));

		PrintToScreen(Message, Color);
	}
}

#pragma endregion

