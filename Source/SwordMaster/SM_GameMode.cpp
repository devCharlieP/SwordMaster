// Fill out your copyright notice in the Description page of Project Settings.


#include "SM_GameMode.h"
#include "SM_PlayerController.h"
#include "SM_Character.h"
#include "UObject/ConstructorHelpers.h"

ASM_GameMode::ASM_GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SwordMaster/Blueprints/BP_SM_Character"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/SwordMaster/Blueprints/BP_SM_PlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}