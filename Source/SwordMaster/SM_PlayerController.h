// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SwordMaster.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "SM_PlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class SWORDMASTER_API ASM_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASM_PlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	void PlaySkill(UAnimMontage* SkillMontage);

private:
	FVector CachedDestination;

	float FollowTime; // For how long it has been pressed

	void PlaySkillByIndex(int32 SkillIndex);

	UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<class UInputAction> InputActionSkillQ;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<class UInputAction> InputActionSkillW;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<class UInputAction> InputActionSkillE;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<class UInputAction> InputActionSkillR;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<class UInputAction> InputActionSkillD;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<class UInputAction> InputActionSkillF;

    void PlaySkillQ();
    void PlaySkillW();
    void PlaySkillE();
    void PlaySkillR();
    void PlaySkillD();
    void PlaySkillF();

};
