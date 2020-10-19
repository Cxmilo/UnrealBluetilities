// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEditorUtilityWidget.h"
#include "EditorLevelLibrary.h"
#include "EditorAssetLibrary.h"


#pragma region OrganizeWorldOutliner
void UMyEditorUtilityWidget::OrganizeWorldOutliner()
{
	TArray<AActor*> AllActors = UEditorLevelLibrary::GetAllLevelActors();
	for (AActor* Actor : AllActors)
	{
		if (ensure(Actor))
		{
			const FName* FolderName = FolderMap.Find(Actor->GetClass());
			if (ensure(FolderName))
			{
				Actor->SetFolderPath(*FolderName);
			}
		}
	}
}
#pragma endregion


#pragma region DeleteNullSMActors
void UMyEditorUtilityWidget::DeleteNullSMActors()
{
	TArray<AActor*> AllActors = UEditorLevelLibrary::GetAllLevelActors();
	for (AActor* Actor : AllActors)
	{
		if (ensure(Actor))
		{
			AStaticMeshActor* StaticMeshActor = dynamic_cast<AStaticMeshActor*>(Actor);
			if (ensure(StaticMeshActor))
			{
				UStaticMeshComponent* StaticMeshComponet = StaticMeshActor->GetStaticMeshComponent();
				if (ensure(StaticMeshComponet) && nullptr == StaticMeshComponet->GetStaticMesh())
				{
					Actor->Destroy();
				}
			}
		}
	}
}
#pragma endregion


#pragma region SetTextureParameters

void UMyEditorUtilityWidget::SetTextureParameter()
{
	TArray<FString> AssetsInPath = UEditorAssetLibrary::ListAssets(FolderPath, bRecursive, false);
	
	for (FString AssetPath : AssetsInPath)
	{
		for (FString Pattern : LinearColorPattern)
		{
			if (AssetPath.Contains(Pattern))
			{
				UObject* Object = UEditorAssetLibrary::LoadAsset(AssetPath);
				if (!ensure(Object))
				{
					return;
				}

				UTexture2D* Texture = dynamic_cast<UTexture2D*>(Object);
				if (ensure(Texture))
				{
					Texture->SRGB = bSetRGB;
					Texture->CompressionSettings = Compression;
				}
			}
		}
	}
}
#pragma endregion


#pragma region SearchAndReplace
void UMyEditorUtilityWidget::SearchAndReplace()
{
	TArray<FString> AssetsInPath = UEditorAssetLibrary::ListAssets(FolderPath, bRecursive, false);
	
	for (FString AssetPath : AssetsInPath)
	{
		FString FileName = FPaths::GetCleanFilename(AssetPath);
		if (FileName.Contains(SearchPattern, SearchCase))
		{
			FString NewAssetName = FileName.Replace(*SearchPattern, *ReplacePattern, SearchCase);
			FString NewAssetPath = FPaths::Combine(FPaths::GetPath(AssetPath), NewAssetName);
			UEditorAssetLibrary::RenameAsset(AssetPath, NewAssetPath);
		}

	}
}
#pragma endregion







