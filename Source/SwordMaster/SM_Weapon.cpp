// Fill out your copyright notice in the Description page of Project Settings.


#include "SM_Weapon.h"

// Sets default values
ASM_Weapon::ASM_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));

	if(SM_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SM_WEAPON.Object);
	}
}

// Called when the game starts or when spawned
void ASM_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

