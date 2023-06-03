// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPawn.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABoardPawn::ABoardPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(StaticMesh);
	CameraBoom->TargetArmLength = 300.f;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	MoveRate = 100;
}

// Called when the game starts or when spawned
void ABoardPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoardPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoardPawn::Client_MoveLeftRight_Implementation(float Value) {
	FVector Location = this->GetActorLocation();
	FVector RightVector = this->GetActorTransform().GetUnitAxis(EAxis::X);

	this->SetActorLocation(Location + RightVector * Value * MoveRate, true);
}

void ABoardPawn::Multicast_MoveLeftRight_Implementation(float Value) {
	Client_MoveLeftRight(Value);
}

void ABoardPawn::Server_MoveLeftRight_Implementation(float Value) {
	Multicast_MoveLeftRight(Value);
}