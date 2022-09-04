// Fill out your copyright notice in the Description page of Project Settings.

#include "TextFileHandler.h"
#include "EscapeInSpace.h"
#include "Misc/Paths.h"

 bool UTextFileHandler::FileSaveString(FString SaveTextB, FString FileNameB)
 {
	 return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::ProjectDir() + FileNameB));
 }

 bool UTextFileHandler::FileLoadString(FString FileNameA, FString& SaveTextA)
 {
	 return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::ProjectDir() + FileNameA));
 }
