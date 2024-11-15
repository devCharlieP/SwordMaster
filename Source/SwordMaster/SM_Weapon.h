// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SwordMaster.h"
#include "GameFramework/Actor.h"
#include "SM_Weapon.generated.h"

UCLASS()
class SWORDMASTER_API ASM_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASM_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

};