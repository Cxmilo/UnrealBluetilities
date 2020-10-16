// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEditorUtilityWidget.h"

void UMyEditorUtilityWidget::Test()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("Hello World"));
}
