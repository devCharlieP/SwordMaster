// Fill out your copyright notice in the Description page of Project Settings.


#include "SM_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "SM_Character.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SM_AnimInstance.h"

ASM_PlayerController::ASM_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ASM_PlayerController::BeginPlay()
{
    // Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ASM_PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
    
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ASM_PlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ASM_PlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ASM_PlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ASM_PlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(InputActionSkillQ, ETriggerEvent::Triggered, this, &ASM_PlayerController::PlaySkillQ);
    	EnhancedInputComponent->BindAction(InputActionSkillW, ETriggerEvent::Triggered, this, &ASM_PlayerController::PlaySkillW);
    	EnhancedInputComponent->BindAction(InputActionSkillE, ETriggerEvent::Triggered, this, &ASM_PlayerController::PlaySkillE);
    	EnhancedInputComponent->BindAction(InputActionSkillR, ETriggerEvent::Triggered, this, &ASM_PlayerController::PlaySkillR);
    	EnhancedInputComponent->BindAction(InputActionSkillD, ETriggerEvent::Triggered, this, &ASM_PlayerController::PlaySkillD);
    	EnhancedInputComponent->BindAction(InputActionSkillF, ETriggerEvent::Triggered, this, &ASM_PlayerController::PlaySkillF);
	}
}

void ASM_PlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ASM_PlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ASM_PlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void ASM_PlayerController::PlaySkillByIndex(int32 SkillIndex)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
        {
            if (USM_AnimInstance* AnimInstance = Cast<USM_AnimInstance>(ControlledCharacter->GetMesh()->GetAnimInstance()))
            {
                UAnimMontage* SelectedMontage = nullptr;

                switch (SkillIndex)
                {
                case 0:
                    SelectedMontage = AnimInstance->SkillQMontage;
                    break;
                case 1:
                    SelectedMontage = AnimInstance->SkillWMontage;
                    break;
                case 2:
                    SelectedMontage = AnimInstance->SkillEMontage;
                    break;
                case 3:
                    SelectedMontage = AnimInstance->SkillRMontage;
                    break;
                case 4:
                    SelectedMontage = AnimInstance->SkillDMontage;
                    break;
                case 5:
                    SelectedMontage = AnimInstance->SkillFMontage;
                    break;
                }

                if (SelectedMontage)
                {
                    AnimInstance->PlaySkill(SelectedMontage);
                }
            }
        }
    }
}

void ASM_PlayerController::PlaySkillQ() { PlaySkillByIndex(0); }
void ASM_PlayerController::PlaySkillW() { PlaySkillByIndex(1); }
void ASM_PlayerController::PlaySkillE() { PlaySkillByIndex(2); }
void ASM_PlayerController::PlaySkillR() { PlaySkillByIndex(3); }
void ASM_PlayerController::PlaySkillD() { PlaySkillByIndex(4); }
void ASM_PlayerController::PlaySkillF() { PlaySkillByIndex(5); }